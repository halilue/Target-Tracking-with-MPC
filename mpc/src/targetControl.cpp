// Libraries
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sstream>
#include <cmath>
#include <math.h>
#include <tf/tf.h>
#include <tf2/LinearMath/Quaternion.h>
#include <iostream>
#include <ros/console.h>
#include <visualization_msgs/Marker.h>

ros::Publisher velocityPub;
ros::Publisher positionPub;
ros::Publisher markerPub;

geometry_msgs::Twist velocity;
nav_msgs::Odometry nextWaypoint;
nav_msgs::Odometry targetPosition;
tf2::Quaternion goalQuaternion;

double qX, qY, qZ, qW;
double roll, pitch, yaw;
double r, p, y;
double phi1Arg, phi2Arg, psi1Arg, psi2Arg;
int duration = 30;
int length = 20;
int galopDistance = 50;

// Functions
void positionCallback(const nav_msgs::Odometry::ConstPtr & positionMsg);
void toGoal(nav_msgs::Odometry nextWaypoint, double distanceTolerance);
void rotation();
void trajectory(int length, int galopDistance);
void path(int duration, int length);
double distance(double x1, double y1, double x2, double y2);


/** Main - Function **/
int main (int argc, char ** argv)
{
        // Initiate new ROS node
        ros::init(argc, argv, "targetNode");
        ros::NodeHandle n;

        // Publisher and Subscriber
        velocityPub = n.advertise<geometry_msgs::Twist>("/cmd_vel",10);

		//positionSub = n.subscribe("/odom", 10, positionCallback);


	ros::Rate loopRate(3);

	/** Trajectory **/
	do{
			trajectory(length, galopDistance);
			
	}while(ros::ok());
	
	ros::spinOnce();
	loopRate.sleep();

	/** goalQuaternion.setRPY(r, p, y);
	goalQuaternion = goalQuaternion.normalize();
	nextWaypoint.pose.pose.orientation.x = goalQuaternion.x();
	nextWaypoint.pose.pose.orientation.y = goalQuaternion.y();
	nextWaypoint.pose.pose.orientation.z = goalQuaternion.z();
	nextWaypoint.pose.pose.orientation.w = goalQuaternion.w();**/

}

// Subscriber - Function
void positionCallback(const nav_msgs::Odometry::ConstPtr & positionMsg)
{
	// x-y coordinates
        targetPosition.pose.pose.position.x = positionMsg->pose.pose.position.x;
        targetPosition.pose.pose.position.y = positionMsg->pose.pose.position.y;
		targetPosition.pose.pose.position.z = positionMsg->pose.pose.position.z;
	
	// quaternion
	tf::Quaternion q(
			positionMsg->pose.pose.orientation.x,
			positionMsg->pose.pose.orientation.y,
			positionMsg->pose.pose.orientation.z,
			positionMsg->pose.pose.orientation.w);
	tf::Matrix3x3 m(q);

	// euler
	m.getRPY(roll, pitch, yaw);

}

// Distance - Function
double distance(double x1, double y1, double x2, double y2)
{
        return sqrt(pow((x1-x2),2)+pow((y1-y2),2));
}

// Rotation - Function 
void rotation()
{
	velocity.angular.z = 5;
	double angle = 0.0;
	double startingTime = ros::Time::now().toSec();
	ros::Rate loopRate(10);
	do{
		velocityPub.publish(velocity);
		double actualTime = ros::Time::now().toSec();
        	   
		angle = 10 * (actualTime-startingTime);
		ros::spinOnce();
		loopRate.sleep();
	}while(angle <0.785398);
	velocity.angular.z = 0;
	velocityPub.publish(velocity);
}

// Move to Goal - Function
void toGoal(nav_msgs::Odometry nextWaypoint, double distanceTolerance)
{
	nextWaypoint.pose.pose.position.x = 0;
	nextWaypoint.pose.pose.position.y = 0;

	ros::Rate loopRate(10);
	do{
                //Proportional Controller
		//linear velocity in the x-axis
                velocity.linear.x = distance(targetPosition.pose.pose.position.x, targetPosition.pose.pose.position.y, nextWaypoint.pose.pose.position.x, nextWaypoint.pose.pose.position.y);
                velocity.linear.y = 0;
                velocity.linear.z = 0;

		// angular velocity in the z-axis
                velocity.angular.x = 0;
                velocity.angular.y = 0;
                velocity.angular.z = 4*(atan2(nextWaypoint.pose.pose.position.y-targetPosition.pose.pose.position.y, nextWaypoint.pose.pose.position.x - targetPosition.pose.pose.position.x)-yaw);

		velocityPub.publish(velocity);
        
		ros::spinOnce();
		loopRate.sleep();
	}while(distance(targetPosition.pose.pose.position.x, targetPosition.pose.pose.position.y, nextWaypoint.pose.pose.position.x, nextWaypoint.pose.pose.position.y) > distanceTolerance);

	velocity.linear.x = 0;
    velocity.angular.z = 0;
    
	velocityPub.publish(velocity);
} 

/** Horse-Movements **/
// walk
void walk(int length)
{

    double currentPosition = 0;
    double startingTime = ros::Time::now().toSec();

    ros::Rate loopRate(3);

	velocity.linear.x = 1.7777; // walking velocity in m/s

	do{
		velocityPub.publish(velocity);
		// publish DATA

		double actualTime = ros::Time::now().toSec();
                currentPosition = 1.7777 * (actualTime-startingTime);
                
		ros::spinOnce();
		loopRate.sleep();
	}while(currentPosition < length);

	velocity.linear.x = 0;
	velocityPub.publish(velocity);
}

// trot 
void trot(int length)
{
	double currentPosition = 0;
    double startingTime = ros::Time::now().toSec();

    ros::Rate loopRate(3);

    velocity.linear.x = 4.4444; // troting velocity in m/s
    
	do{
        velocityPub.publish(velocity);
		double actualTime = ros::Time::now().toSec();
		double deltaT = actualTime-startingTime;

        currentPosition = 4.4444 * pow(deltaT,2);

		ros::spinOnce();
		loopRate.sleep();
        }while(currentPosition < length);

        velocity.linear.x = 0;
        velocityPub.publish(velocity);
}

// canter
void canter(int length)
{
	double currentPosition = 0;
    double startingTime = ros::Time::now().toSec();

    ros::Rate loopRate(3);

	velocity.linear.x = 5.9722; // canter velocity in m/s
    do{
        velocityPub.publish(velocity);
           	
		double actualTime = ros::Time::now().toSec();
        currentPosition = 5.9722 * (actualTime-startingTime);

		ros::spinOnce();

		loopRate.sleep();
    }while(currentPosition < length);

    velocity.linear.x = 0;
    velocityPub.publish(velocity);
}

// galop
void galop(int galopDistance)
{
	double currentPosition = 0;
	double startingTime = ros::Time::now().toSec();

	ros::Rate loopRate(3);
    velocity.linear.x = 12.2222; // galop velocity in m/s
    
	do{
        velocityPub.publish(velocity);
		
		double actualTime = ros::Time::now().toSec();
		currentPosition = 12.2222 * (actualTime-startingTime);
                
		ros::spinOnce();
		loopRate.sleep();
    }while(currentPosition < galopDistance);

    velocity.linear.x = 0;
    velocityPub.publish(velocity);
}

// trajectory
void trajectory(int length, int galopDistance)
{
	walk(length);
	rotation();
	trot(length);
	rotation();
	canter(length);
	rotation();
	galop(galopDistance);
	rotation();
	canter(length);
	rotation();
	trot(length);
	rotation();
}

// Move to Goal - Function
void path(int duration, int length)
{
	double currentPosition = 0;
    ros::Time startingTime = ros::Time::now();
	double startTime = ros::Time::now().toSec();
	ros::Duration endingTime(duration);

	ros::Rate loopRate(10);
	while(ros::Time::now() - startingTime < endingTime) {

		// Linear velocity in the x-axis
		do{
			double actualTime = ros::Time::now().toSec();
			velocity.linear.x = 4.4444;
			currentPosition = velocity.linear.x * (actualTime-startTime);
			velocityPub.publish(velocity);
		}while(currentPosition < length);
	    
		// Curve
		ros::Time startingTimeS = ros::Time::now();
		ros::Duration endingTimeS(1);

        do{
			velocity.angular.z = 4;
			velocityPub.publish(velocity);
		}while(ros::Time::now() - startingTimeS < endingTimeS);
		
		do{
			double actualTime = ros::Time::now().toSec();
			velocity.linear.x = 4.4444;
			currentPosition = velocity.linear.x * (actualTime-startTime);
			velocityPub.publish(velocity);
		}while(currentPosition < length);
	    
		// Curve
		ros::Time startingTimeT = ros::Time::now();
		ros::Duration endingTimeT(1);
        do{
			velocity.angular.z = -4;
			velocityPub.publish(velocity);
		}while(ros::Time::now() - startingTimeT < endingTimeT);

		velocityPub.publish(velocity);
        
		ros::spinOnce();
		loopRate.sleep();
	};

	velocity.linear.x = 0;
    velocity.angular.z = 0;
    
	velocityPub.publish(velocity);
} 

// Libraries
#include <ros/ros.h>
#include <ros/console.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/TwistWithCovarianceStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <trajectory_msgs/MultiDOFJointTrajectory.h>
#include <tf/tf.h>
#include <tf2/LinearMath/Quaternion.h>
#include <cmath>
#include <math.h>
#include "../include/mpcData.h"

/** Variables **/
// Constants
double pi = 3.14159265359;

// Animal
nav_msgs::Odometry animalPosition;
nav_msgs::Odometry animalVelocity;
nav_msgs::Odometry distance;
double rollAnimal, pitchAnimal, yawAnimal;

// UAV
nav_msgs::Odometry uavPosition;
nav_msgs::Odometry uavVelocity;
geometry_msgs::PoseStamped wayPoint;
double height = 5;
double threshold = 1;
double yaw;
double rollUAV, pitchUAV, yawUAV;
tf2::Quaternion goalQuaternion;

// Publisher 
ros::Publisher wayPointPub;

// Subscriber
ros::Subscriber animalPositionSub;
ros::Subscriber animalVelocitySub;
ros::Subscriber uavPositionSub;
ros::Subscriber uavVelocitySub;

// Variables
Eigen::Matrix<double, 6, 21> desiredState = Eigen::Matrix<double, 6, 21>::Zero();
Eigen::Matrix<double, 6, 1> initialState = Eigen::Matrix<double, 6, 1>::Zero();
Eigen::Matrix<double, 9, 21> trajectory = Eigen::Matrix<double, 9, 21>::Zero();

// Functions
void mpc();

// Callback Functions
void animalPositionCallback(const nav_msgs::Odometry::ConstPtr & msg)
{
    animalPosition.pose.pose.position.x = msg->pose.pose.position.x;
    animalPosition.pose.pose.position.y = msg->pose.pose.position.y;
    animalPosition.pose.pose.position.z = msg->pose.pose.position.z;
    
    tf::Quaternion qAnimal(
			msg->pose.pose.orientation.x,
			msg->pose.pose.orientation.y,
			msg->pose.pose.orientation.z,
			msg->pose.pose.orientation.w);
	tf::Matrix3x3 m(qAnimal);

	// euler
	m.getRPY(rollAnimal, pitchAnimal, yawAnimal);
}

void animalVelocityCallback(const nav_msgs::Odometry::ConstPtr & msg)
{
    animalVelocity.twist.twist.linear.x = msg->twist.twist.linear.x;
    animalVelocity.twist.twist.linear.y = msg->twist.twist.linear.y;
    animalVelocity.twist.twist.linear.z = msg->twist.twist.linear.z;
}

void uavPositionCallback(const nav_msgs::Odometry::ConstPtr & msg)
{
    uavPosition.pose.pose.position.x = msg->pose.pose.position.x;
    uavPosition.pose.pose.position.y = msg->pose.pose.position.y;
    uavPosition.pose.pose.position.z = msg->pose.pose.position.z;    

    tf::Quaternion qUAV(
			msg->pose.pose.orientation.x,
			msg->pose.pose.orientation.y,
			msg->pose.pose.orientation.z,
			msg->pose.pose.orientation.w);
	tf::Matrix3x3 m(qUAV);

	// euler
	m.getRPY(rollUAV, pitchUAV, yawUAV);
}

void uavVelocityCallback(const nav_msgs::Odometry::ConstPtr & msg)
{
    uavVelocity.twist.twist.linear.x = msg->twist.twist.linear.x;
    uavVelocity.twist.twist.linear.y = msg->twist.twist.linear.y;
    uavVelocity.twist.twist.linear.z = msg->twist.twist.linear.z;
}

/** Loading data to MPC **/
void load_data(double sampleTime, Eigen::Matrix<double, 6, 1> initialState, Eigen::Matrix<double, 6, 21>desiredState)
{
    /** Load Parameters into mpc **/
    // System Matrix A
    params.A[0] = 1;
    params.A[1] = sampleTime;
    params.A[2] = 1;
    params.A[3] = 1;
    params.A[4] = sampleTime;
    params.A[5] = 1;
    params.A[6] = 1;
    params.A[7] = sampleTime;
    params.A[8] = 1;

    // Control Matrix B 
    params.B[0] = 0.5*sampleTime*sampleTime;
    params.B[1] = sampleTime;
    params.B[2] = 0.5*sampleTime*sampleTime;
    params.B[3] = sampleTime;
    params.B[4] = 0.5*sampleTime*sampleTime;
    params.B[5] = sampleTime;  

    // State Cost-Function
    params.Q[0] = 1000;
    params.Q[1] = 1000;
    params.Q[2] = 1000;
    params.Q[3] = 1000;
    params.Q[4] = 50;
    params.Q[5] = 50;

    params.P[0] = 1000;
    params.P[1] = 1000;
    params.P[2] = 1000;
    params.P[3] = 1000;
    params.P[4] = 1000;
    params.P[5] = 800;

    // Desired State
    for(int i=0; i<6; i++){
        params.xD_1[i] = desiredState(i,1);
    }

    for(int i=0; i<6; i++){
        params.xD_2[i] = desiredState(i,2);
    }

    for(int i=0; i<6; i++){
        params.xD_3[i] = desiredState(i,3);
    }

    for(int i=0; i<6; i++){
        params.xD_4[i] = desiredState(i,4);
    }

    for(int i=0; i<6; i++){
        params.xD_5[i] = desiredState(i,5);
    }

    for(int i=0; i<6; i++){
        params.xD_6[i] = desiredState(i,6);
    }

    for(int i=0; i<6; i++){
        params.xD_7[i] = desiredState(i,7);
    }

    for(int i=0; i<6; i++){
        params.xD_8[i] = desiredState(i,8);
    }

    for(int i=0; i<6; i++){
        params.xD_9[i] = desiredState(i,9);
    }

    for(int i=0; i<6; i++){
        params.xD_10[i] = desiredState(i,10);
    }

    for(int i=0; i<6; i++){
        params.xD_11[i] = desiredState(i,11);
    }

    for(int i=0; i<6; i++){
        params.xD_12[i] = desiredState(i,12);
    }

    for(int i=0; i<6; i++){
        params.xD_13[i] = desiredState(i,13);
    }

    for(int i=0; i<6; i++){
        params.xD_14[i] = desiredState(i,14);
    }

    for(int i=0; i<6; i++){
        params.xD_15[i] = desiredState(i,15);
    }

    for(int i=0; i<6; i++){
        params.xD_16[i] = desiredState(i,16);
    }

    for(int i=0; i<6; i++){
        params.xD_17[i] = desiredState(i,17);
    }

    for(int i=0; i<6; i++){
        params.xD_18[i] = desiredState(i,18);
    }

    for(int i=0; i<6; i++){
        params.xD_19[i] = desiredState(i,19);
    }

    for(int i=0; i<6; i++){
        params.xD_20[i] = desiredState(i,20);
    }

    // Initial state
    for(int i=0;i<6;i++){
        params.x_0[i] = initialState(i);
    }
}

// CVXGEN Output 
Eigen::Matrix<double, 9, 21> use_solution(Vars vars)
{
	Eigen::Matrix<double, 9, 21> solution = Eigen::Matrix<double, 9, 21>::Zero();
      
    // State Output         
    for(int i = 0; i<6; i++)
	{
		solution(i,1) = vars.x_1[i];
	}

	for(int i = 0; i<6; i++)
	{
        solution(i,2) = vars.x_2[i];
    }

	for(int i = 0; i<6; i++)
	{
        solution(i,3) = vars.x_3[i];
    }

	for(int i = 0; i<6; i++)
	{
        solution(i,4) = vars.x_4[i];
    }

	for(int i = 0; i<6; i++)
	{
        solution(i,5) = vars.x_5[i];
    }

	for(int i = 0; i<6; i++)
	{
        solution(i,6) = vars.x_6[i];
    }

	for(int i = 0; i<6; i++)
	{
        solution(i,7) = vars.x_7[i];
    }

	for(int i = 0; i<6; i++)
	{
        solution(i,8) = vars.x_8[i];
    }

	for(int i = 0; i<6; i++)
	{
        solution(i,9) = vars.x_9[i];
    }

	for(int i = 0; i<6; i++)
	{
        solution(i,10) = vars.x_10[i];
    }

    for(int i = 0; i<6; i++)
	{
        solution(i,11) = vars.x_11[i];
    }

    for(int i = 0; i<6; i++)
	{
        solution(i,12) = vars.x_12[i];
    }

    for(int i = 0; i<6; i++)
	{
        solution(i,13) = vars.x_13[i];
    }

    for(int i = 0; i<6; i++)
	{
        solution(i,14) = vars.x_14[i];
    }

    for(int i = 0; i<6; i++)
	{
        solution(i,15) = vars.x_15[i];
    }

    for(int i = 0; i<6; i++)
	{
        solution(i,16) = vars.x_16[i];
    }

    for(int i = 0; i<6; i++)
	{
        solution(i,17) = vars.x_17[i];
    }

    for(int i = 0; i<6; i++)
	{
        solution(i,18) = vars.x_18[i];
    }

    for(int i = 0; i<6; i++)
	{
        solution(i,19) = vars.x_19[i];
    }

    for(int i = 0; i<6; i++)
	{
        solution(i,20) = vars.x_20[i];
    }

    // Control Output
    for(int i = 6; i<9; i++)
	{
		solution(i,0) = vars.u_0[i];
	}

	for(int i = 6; i<9; i++)
	{
        solution(i,1) = vars.u_1[i];
    }

	for(int i = 6; i<9; i++)
	{
        solution(i,2) = vars.u_2[i];
    }

	for(int i = 6; i<9; i++)
	{
        solution(i,3) = vars.u_3[i];
    }

	for(int i = 6; i<9; i++)
	{
        solution(i,4) = vars.u_4[i];
    }

	for(int i = 6; i<9; i++)
	{
        solution(i,5) = vars.u_5[i];
    }

	for(int i = 6; i<9; i++)
	{
        solution(i,6) = vars.u_6[i];
    }

	for(int i = 6; i<9; i++)
	{
        solution(i,7) = vars.u_7[i];
    }

	for(int i = 6; i<9; i++)
	{
        solution(i,8) = vars.u_8[i];
    }

	for(int i = 6; i<9; i++)
	{
        solution(i,9) = vars.u_9[i];
    }

	for(int i = 6; i<9; i++)
	{
        solution(i,10) = vars.u_10[i];
    }
	
    for(int i = 6; i<9; i++)
	{
        solution(i,11) = vars.u_11[i];
    }

    for(int i = 6; i<9; i++)
	{
        solution(i,12) = vars.u_12[i];
    }

    for(int i = 6; i<9; i++)
	{
        solution(i,13) = vars.u_13[i];
    }

    for(int i = 6; i<9; i++)
	{
        solution(i,14) = vars.u_14[i];
    }

    for(int i = 6; i<9; i++)
	{
        solution(i,15) = vars.u_15[i];
    }

    for(int i = 6; i<9; i++)
	{
        solution(i,16) = vars.u_16[i];
    }

    for(int i = 6; i<9; i++)
	{
        solution(i,17) = vars.u_17[i];
    }

    for(int i = 6; i<9; i++)
	{
        solution(i,18) = vars.u_18[i];
    }

    for(int i = 6; i<9; i++)
	{
        solution(i,19) = vars.u_19[i];
    }

    for(int i = 6; i<9; i++)
	{
        solution(i,20) = vars.u_20[i];
    }

    return solution;
}
/** Main **/
int main(int argc, char ** argv)
{
    // Initiating 
    ros::init(argc, argv, "mpcTrackerNode");
    ros::NodeHandle nh;

    // Publisher
    wayPointPub = nh.advertise<geometry_msgs::PoseStamped>("/iris/command/pose", 1000);

    // Subscriber 
    animalPositionSub = nh.subscribe("/odom", 1000, animalPositionCallback);
    animalVelocitySub = nh.subscribe("/odom", 1000, animalVelocityCallback);

    uavPositionSub = nh.subscribe("/iris/odometry_sensor1/odometry", 1000, uavPositionCallback);
    uavVelocitySub = nh.subscribe("/iris/odometry_sensor1/odometry", 1000, uavVelocityCallback);

    // Model Predictive Controller
    ros::Rate loopRate(50);

    while(ros::ok())
    {
        mpc();
        ros::spinOnce();
        loopRate.sleep();
    }
    return 0;
} 

/** MPC Algorithm **/
Eigen::Matrix<double, 9, 21> algorithm(double sampleTime, Eigen::Matrix<double, 6, 1> initialState, Eigen::Matrix<double, 6, 21>desiredState)
{
        set_defaults();
        setup_indexing();

        settings.verbose = 0;
	
        load_data(sampleTime, initialState, desiredState);

        solve();

        trajectory = use_solution(vars);

        return trajectory;
}

/** Navigation **/
void mpc()
{
        ros::Rate loopRate(50);
    
        do{
            double xDistance = uavPosition.pose.pose.position.x-animalPosition.pose.pose.position.x;
            double yDistance = uavPosition.pose.pose.position.y-animalPosition.pose.pose.position.y;
            double xTolerance = abs(xDistance);
            double yTolerance = abs(yDistance);

            yaw = atan2((yDistance), (xDistance));
            
            for(int k=1; k<21; k++) 
            {
                desiredState(0,k) = animalPosition.pose.pose.position.x + threshold*cos(yaw);
                desiredState(1,k) = animalPosition.twist.twist.linear.x;                
                desiredState(2,k) = animalPosition.pose.pose.position.y + threshold*sin(yaw);
                desiredState(3,k) = animalPosition.twist.twist.linear.y;
                
                if (animalPosition.twist.twist.linear.x > 4.4444)
                {
                    desiredState(4,k) = animalPosition.pose.pose.position.z+height+2;
                }
                else
                {
                    desiredState(4,k) = animalPosition.pose.pose.position.z+height;
                }
            }
	
	        // Current State for MPC
	        initialState(0) = uavPosition.pose.pose.position.x;
	        initialState(1) = uavVelocity.twist.twist.linear.x;
        	initialState(2) = uavPosition.pose.pose.position.y;
	        initialState(3) = uavVelocity.twist.twist.linear.y;
	        initialState(4) = uavPosition.pose.pose.position.z;
	        initialState(5) = uavVelocity.twist.twist.linear.z;
            //initialState(6) = yawUAV;
		
            // MPC-Algorithm
        	algorithm(sampleTime, initialState, desiredState);

            /** ROS_INFO             
            ROS_INFO("UAV's z-position: %f", uavPosition.pose.pose.position.z);
            ROS_INFO("MPC's x_7 Output: %f", trajectory(0,7));
            ROS_INFO("MPC's y_7 Output: %f", trajectory(2,7));
            **/

            // Next Waypoint        
            wayPoint.pose.position.x = trajectory(0,7);
            wayPoint.pose.position.y = trajectory(2,7);                
            wayPoint.pose.position.z = trajectory(4,7);
            
            // Next Orientation 
            goalQuaternion.setRPY(rollUAV, pitchUAV , yawAnimal);
	        goalQuaternion = goalQuaternion.normalize();
	        wayPoint.pose.orientation.x = goalQuaternion.x();
	        wayPoint.pose.orientation.y = goalQuaternion.y();
	        wayPoint.pose.orientation.z = goalQuaternion.z();
	        wayPoint.pose.orientation.w = goalQuaternion.w(); 

       	    // publish DATA
            wayPointPub.publish(wayPoint);

            ros::spinOnce();
            loopRate.sleep();

        }while(ros::ok());
}


/** CVXGEN **/

extern "C"{
#include "cvxgen/solver.h"
}

Vars vars;
Params params;
Workspace work;
Settings settings;

/** Libraries **/
#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/TwistWithCovarianceStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Vector3.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float64.h>
#include <cmath>
#include <math.h>
#include <sensor_msgs/Imu.h>
#include <Eigen/Dense>
#include <Eigen/Eigen>
#include <visualization_msgs/Marker.h>


/** Variables **/
// MPC 
double sampleTime = 0.6;

/** MPC-Functions **/
// Load Parameters into CVXGEN
void load_data(double sampleTime, Eigen::Matrix<double, 6, 1> initialState, Eigen::Matrix<double, 6, 21>desiredState);

// MPC-Algorithm 
Eigen::Matrix<double, 9, 21> algorithm(double sampleTime, Eigen::Matrix<double, 6, 1> initialState, Eigen::Matrix<double, 6, 21>desiredState);

// MPC-Output
Eigen::Matrix<double, 9, 21> use_solution(Vars vars);


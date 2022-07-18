#include <ros/ros.h>
#include <car_msgs/Trajectory.h>

// include std lib
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

// // datatype of car_state
// typedef struct
// {
//     double x;
//     double y;
//     double theta;
// } car_state;


// // datatype of car_command
// typedef struct
// {
//     double v;
//     double w;
// } car_command;

// // datatype of trajectory
// typedef struct
// {
//     std::vector<car_state> states;
//     std::vector<car_command> commands;
// } trajectory;

// // datatype of steering angle
// typedef struct
// {
//     double steering_angle;
//     double steering_angle_dot;
// } steering_angle;

// // datatype of throttle
// typedef struct
// {
//     double throttle;
//     double throttle_dot;
// } throttle;

// // datatype of brake
// typedef struct
// {
//     double brake;
//     double brake_dot;
// } brake;

// // datatype of car including position velocity and steering angle and throttle and brake
// typedef struct
// {
//     car_state state;
//     car_command command;
//     steering_angle steering_angle;
//     throttle throttle;
//     brake brake;
// } car;
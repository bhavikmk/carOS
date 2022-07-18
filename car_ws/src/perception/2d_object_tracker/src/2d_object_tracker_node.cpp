// import ros and sensor msgs Image lib
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include "car_msgs/Detection.h"
#include "car_msgs/Detections.h"


// import cv lib
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// import c++ lib
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

// import cv_bridge lib
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

// import image_transport 
#include <image_transport/image_transport.h>

// create class for 2d object tracker 
class ObjectTracker
{
    public:

        ros::Publisher pub;
        ros::Subscriber sub;

        ObjectTracker(ros::NodeHandle nh){

            pub = nh.advertise<car_msgs::Detections>("/objects_tracked", 1);
            sub = nh.subscribe<car_msgs::Detections>("/objects_detected", 1, &ObjectTracker::detectionsCallback, this);
        }
        void detectionsCallback(const car_msgs::Detections::ConstPtr &msg){

            car_msgs::Detections detections = *msg;
        }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "2d_object_tracker");
    ros::NodeHandle nh;
    ObjectTracker object_tracker(nh);
    ros::spin();
    return 0;
}
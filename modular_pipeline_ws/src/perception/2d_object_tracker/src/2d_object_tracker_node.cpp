#include "object_tracker.h"

class ObjectTracker
{
    public:

        ros::Publisher pub;
        ros::Subscriber sub;

        ObjectTracker(ros::NodeHandle nh){

            pub = nh.advertise<car_msgs::Detections>("/2d_objects_tracked", 1);
            sub = nh.subscribe<car_msgs::Detections>("/2d_objects_detected", 1, &ObjectTracker::detectionsCallback, this);
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
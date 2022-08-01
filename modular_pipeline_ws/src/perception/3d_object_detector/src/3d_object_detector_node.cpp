#include "3d_detector.h"

class LidarObjectDetector {

    public:

    ros::Subscriber sub;
    ros::Publisher pub;

    // Parameters & Attributes
    PointCloud cloud;
    car_msgs::LidarObjectDetect detections;
    
    void cloudCB(const PointCloud::ConstPtr &msg)
    {
        this->cloud = *msg;
    }

    LidarObjectDetector (ros::NodeHandle &nh){

        sub = nh.subscribe<PointCloud>("/pointcloud", 1, &LidarObjectDetector::cloudCB, this);
        pub = nh.advertise<car_msgs::LidarObjectDetect> ("/3d_objects_detected", 1);
    }

    // Methods for processing point clouds & detecting obstacles (vehicles, pedestrians)

};

    

int main(int argc, char **argv)
{
    ros::init(argc, argv, "object_detector_3d");
    ros::NodeHandle nh;
    LidarObjectDetector object_detector = LidarObjectDetector(nh);
    ros::spin();
}

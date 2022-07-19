// Standard libs
#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include "pcl-1.10/pcl/point_types.h"

// Msg types
#include "car_msgs/LidarObjectDetect.h"

using namespace std;

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

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
    ros::init(argc, argv, "3d_object_detector");
    ros::NodeHandle nh;
    LidarObjectDetector object_detector = LidarObjectDetector(nh);
    ros::spin();
}

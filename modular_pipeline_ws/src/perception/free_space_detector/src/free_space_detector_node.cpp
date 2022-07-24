#include "free_space.h"

class FreeSpaceDetector {

    public:

    ros::Subscriber sub;
    ros::Publisher pub;

    // Parameters & Attributes
    PointCloud cloud;
    car_msgs::FreeSpace freeSpace;
    
    void cloudCB(const PointCloud::ConstPtr &msg)
    {
        this->cloud = *msg;
    }

    FreeSpaceDetector (ros::NodeHandle &nh){

        sub = nh.subscribe<PointCloud>("/pointcloud", 1, &FreeSpaceDetector::cloudCB, this);
        pub = nh.advertise<car_msgs::FreeSpace> ("/free_space", 1);
    }

    // Methods for processing point clouds & detecting free space (vehicles, pedestrians)

};

    

int main(int argc, char **argv)
{
    ros::init(argc, argv, "3d_object_detector");
    ros::NodeHandle nh;
    FreeSpaceDetector object_detector = FreeSpaceDetector(nh);
    ros::spin();
}

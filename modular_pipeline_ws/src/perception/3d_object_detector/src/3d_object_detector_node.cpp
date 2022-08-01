#include "3d_detector.h"

class Detection3Dor {

    public:

    ros::Subscriber sub;
    ros::Publisher pub;
    // min size, max size and cluster threshold for detection
    float  cluster_threshold;
    int min_size, max_size;


    // Parameters & Attributes
    PointCloud cloud;
    car_msgs::Detections3D detections;
    
    void cloudCB(const PointCloud::ConstPtr &msg)
    {
        cloud = *msg;
        detections = detectObjects(cloud, cluster_threshold, min_size, max_size);
        pub.publish(detections);        
    }

    Detection3Dor (ros::NodeHandle &nh){

        sub = nh.subscribe<PointCloud>("/pointcloud", 1, &Detection3Dor::cloudCB, this);
        pub = nh.advertise<car_msgs::Detection3D> ("/3d_objects_detected", 1);
    }

    // Methods for processing point clouds & detecting obstacles (vehicles, pedestrians)
    
    PointCloud filterCloud(PointCloud cloud, float min_range, float max_range)
    {
        PointCloud filtered_cloud;
        for (int i = 0; i < cloud.points.size(); i++)
        {
            if (cloud.points[i].x > min_range && cloud.points[i].x < max_range)
            {
                filtered_cloud.points.push_back(cloud.points[i]);
            }
        }
        return filtered_cloud;
    } 

    PointCloud filterCloud(PointCloud cloud, float min_range, float max_range, float min_angle, float max_angle)
    {
        PointCloud filtered_cloud;
        for (int i = 0; i < cloud.points.size(); i++)
        {
            if (cloud.points[i].x > min_range && cloud.points[i].x < max_range && cloud.points[i].y > min_angle && cloud.points[i].y < max_angle)
            {
                filtered_cloud.points.push_back(cloud.points[i]);
            }
        }
        return filtered_cloud;
    }

    std::vector<PointCloud> segmentCloud(PointCloud cloud, float cluster_tolerance, int min_cluster_size, int max_cluster_size)
    {
        std::vector<PointCloud> clusters;
        pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
        tree->setInputCloud (cloud.makeShared());
        std::vector<pcl::PointIndices> cluster_indices;
        pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
        ec.setClusterTolerance (cluster_tolerance); // in meters
        ec.setMinClusterSize (min_cluster_size);
        ec.setMaxClusterSize (max_cluster_size);
        ec.setSearchMethod (tree);
        ec.setInputCloud (cloud.makeShared());
        ec.extract (cluster_indices);
        for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin (); it != cluster_indices.end (); ++it)
        {
            PointCloud cluster;
            for (std::vector<int>::const_iterator pit = it->indices.begin (); pit != it->indices.end (); ++pit)
            {
                cluster.points.push_back(cloud.points[*pit]);
            }
            clusters.push_back(cluster);
        }
        return clusters;
    }
    
    car_msgs::Detections3D detectObjects(PointCloud cloud, float cluster_tolerance, int min_cluster_size, int max_cluster_size)
    {
        car_msgs::Detections3D detections;
        std::vector<PointCloud> clusters = segmentCloud(cloud, cluster_tolerance, min_cluster_size, max_cluster_size);
        for (int i = 0; i < clusters.size(); i++)
        {
            car_msgs::Detection3D detection; // Detection3Dion
            detection.header.stamp = ros::Time::now();
            detection.header.frame_id = "lidar";
            detection.class_id = i;
            // detection.object_type = "object";
            detection.object_pose[0]= clusters[i].points[0].x;
            detection.object_pose[1]= clusters[i].points[0].y;
            detection.object_pose[2]= clusters[i].points[0].z;
            detection.object_pose[3] = 0;
            detection.object_pose[4] = 0;
            detection.object_pose[5] = 0;
            detection.object_pose[6] = 1;
            detection.object_size[7] = 0;
            detection.object_size[1] = 0;
            detection.object_size[2] = 0;
            detections.detect3d.push_back(detection);
        }
        return detections;
    }
};

    

int main(int argc, char **argv)
{
    ros::init(argc, argv, "object_detector_3d");
    ros::NodeHandle nh;
    Detection3Dor object_detector = Detection3Dor(nh);
    ros::spin();
}

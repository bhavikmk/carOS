// Standard libs
#include <ros/ros.h>

// Pcl libs
#include "pcl_ros/point_cloud.h"
#include "pcl_ros/transforms.h"

// #include "pcl-1.10/pcl/point_cloud.h"
#include "pcl-1.10/pcl/point_types.h"
#include "pcl-1.10/pcl/io/pcd_io.h"
#include "pcl-1.10/pcl/filters/voxel_grid.h"
#include "pcl-1.10/pcl/filters/passthrough.h"
#include "pcl-1.10/pcl/filters/extract_indices.h"

#include "pcl-1.10/pcl/segmentation/sac_segmentation.h"
#include "pcl-1.10/pcl/segmentation/extract_clusters.h"
#include "pcl-1.10/pcl/segmentation/region_growing_rgb.h"
#include "pcl-1.10/pcl/segmentation/region_growing.h"

#include "pcl-1.10/pcl/search/kdtree.h"
#include "pcl-1.10/pcl/search/search.h"
#include "pcl-1.10/pcl/features/normal_3d.h"
#include "pcl-1.10/pcl/features/normal_3d_omp.h"

//  include pcl_ros libs


// Msg types
#include "car_msgs/Detection3D.h"
#include "car_msgs/Detections3D.h"

using namespace std;

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

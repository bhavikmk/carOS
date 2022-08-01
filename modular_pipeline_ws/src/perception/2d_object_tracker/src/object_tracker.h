#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include "car_msgs/Detection.h"
#include "car_msgs/Detections.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <opencv2/tracking.hpp>
#include <opencv2/tracking/tracker.hpp>
// #include <opencv2/tracking/tracker_kcf.hpp>

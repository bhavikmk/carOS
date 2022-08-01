// Standard libs
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include "sensor_msgs/Image.h"

// OpenCV deps
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>

// include opencv dnn libs
#include <opencv4/opencv2/dnn.hpp>
#include <opencv4/opencv2/dnn/shape_utils.hpp>
#include <opencv4/opencv2/imgproc.hpp>


// Msg types
#include "car_msgs/Detections.h"
#include "car_msgs/Detection.h"
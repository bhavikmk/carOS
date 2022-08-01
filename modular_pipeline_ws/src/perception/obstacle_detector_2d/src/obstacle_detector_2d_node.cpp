#include "object_detector.h"

class ObstacleDetector2D
{
    ros::NodeHandle nh;
    ros::Publisher pub;
    car_msgs::Detections detections;
    image_transport::ImageTransport it;
    image_transport::Subscriber image_sub_;

    cv::dnn::Net net;
    cv::Mat blob;
    std::vector<cv::String> labels;
    std::vector<cv::String> class_names;

public:
    ObstacleDetector2D() : it(nh)
    {
        image_sub_ = it.subscribe("/front_cam/image_raw", 1, &ObstacleDetector2D::imageCb, this);
        pub = nh.advertise<car_msgs::Detections>("/2d_objects_detected", 1);
    }

    ~ObstacleDetector2D(){}

    void imageCb(const sensor_msgs::ImageConstPtr &msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        namespace enc = sensor_msgs::image_encodings;

        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception &e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }
        detectClassify(cv_ptr->image);
        
    }

    void detectClassify(cv::Mat frame)
    {
        cv::Mat frame_gray;
        cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
        
        cv::Mat frame_resized;
        cv::resize(frame_gray, frame_resized, cv::Size(300, 300));
        
        cv::Mat inputBlob = cv::dnn::blobFromImage(frame_resized, 1.0, cv::Size(300, 300), cv::Scalar(), true, false);
        net.setInput(inputBlob, "data");
        
        cv::Mat detection = net.forward("detection_out");
        cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
        
        car_msgs::Detections detections;

        for (int i = 0; i < detectionMat.rows; i++)
        {
            float confidence = detectionMat.at<float>(i, 2);
            car_msgs::Detection detection;
            
            if (confidence > 0.5)
            {
                int classId = detectionMat.at<float>(i, 1);
                int left = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
                int top = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
                int right = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
                int bottom = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
                cv::rectangle(frame, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar(255, 0, 0), 2);
                
                detection.x = left + (right - left) / 2;
                detection.y = top + (bottom - top) / 2;
                detection.width = right - left;
                detection.height = bottom - top;
                detection.confidence = confidence;
                detection.class_id = classId;
                
                cv::putText(frame, labels[classId], cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
            }
            detections.detections.push_back(detection);
        }
        detections.Header.stamp = ros::Time::now();
        pub.publish(detections);
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "obstacle_detector_2d");
    ObstacleDetector2D ic;
    ros::spin();
    return 0;
}
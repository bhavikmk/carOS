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

            cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();
            cv::Rect2d roi;
            bool initialized = false;
            int id = 0;
            int num_objects = detections.detections.size();
            std::vector<cv::Rect2d> objects;
            std::vector<int> ids;
            std::vector<cv::Ptr<cv::Tracker>> trackers;
            std::vector<cv::Mat> images;
            
            for(int i = 0; i < num_objects; i++){
                cv::Rect2d rect = cv::Rect2d(detections.detections[i].x, detections.detections[i].y, detections.detections[i].width, detections.detections[i].height);
                objects.push_back(rect);
                ids.push_back(detections.detections[i].id);
                trackers.push_back(tracker);
                images.push_back(cv::Mat());
            }

            car_msgs::Detections objects_tracked;
            
            if(!initialized){
                for(int i = 0; i < num_objects; i++){
                    tracker->init(images[i], objects[i]);
                    initialized = true;
                }
            }
            else{
                for(int i = 0; i < num_objects; i++){
                    tracker->update(images[i], objects[i]);
                }
            }
            for(int i = 0; i < num_objects; i++){
                car_msgs::Detection track;
                track.id = ids[i];
                track.x = objects[i].x;
                track.y = objects[i].y;
                track.width = objects[i].width;
                track.height = objects[i].height;
                objects_tracked.detections.push_back(track);
            }
                        
            objects_tracked.Header.stamp = ros::Time::now();

            pub.publish(objects_tracked);
        }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "object_tracker_2d");
    ros::NodeHandle nh;
    ObjectTracker object_tracker(nh);
    ros::spin();
    return 0;
}

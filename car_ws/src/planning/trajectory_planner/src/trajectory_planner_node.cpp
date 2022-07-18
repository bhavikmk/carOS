#include "trajectory_planner.h"

class TrajectoryPlanner
{
    public:
    ros::Subscriber sub;
    ros::Publisher pub;

    TrajectoryPlanner(ros::NodeHandle nh){
        sub = nh.subscribe<car_msgs::Trajectory>("/car_state", 1, &TrajectoryPlanner::carStateCallback, this);
        pub = nh.advertise<car_msgs::Trajectory>("/planned_trajectory", 1);
                
    }
    
    // create callback function of carStateCallback with Trajectory msg
    void carStateCallback(const car_msgs::Trajectory::ConstPtr& msg){

    }       
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "trajectory_planner");
    ros::NodeHandle nh;
    TrajectoryPlanner trajectory_planner(nh);
    ros::spin();
    return 0;
}
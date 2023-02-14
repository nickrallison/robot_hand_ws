#include <ros/ros.h>
#include "../include/leg_inverse_kinematics.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "sign_controller_node");

    ros::NodeHandle nh_private("~");
    //tf::TransformListener tf(ros::Duration(10));
    SignController scSC = SignController(nh_private);

    ros::Timer timer = nh_private.createTimer(ros::Duration(1.0 / sc.operating_freq), &SignController::hand_update, &sc);
    
    ros::spin();
    return 0;
}
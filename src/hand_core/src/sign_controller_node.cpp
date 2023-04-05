#include <ros/ros.h>
#include "../include/sign_controller.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "sign_controller_node");

    ros::NodeHandle nh_private("~");
    //tf::TransformListener tf(ros::Duration(10));
    SignController sc = SignController(nh_private);
    ros::Timer timer = nh_private.createTimer(ros::Duration(sc.period), &GaitExecutor::next_sign, &sc);
    ros::spin();
    return 0;
}
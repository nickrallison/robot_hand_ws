#include <iostream>

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>

#include "../include/sign_controller.h"

std_msgs::String debug_msg;

int main(int argc, char **argv){
    ros::init(argc, argv, "leg_inverse_kinematics_node");
    ros::NodeHandle nh;
    ros::Subscriber text_sub  = nh.subscribe<std_msgs::String>("/input/text", 10, hand_cb);
    ros::Publisher  hand_pub  = nh.advertise<std_msgs::Float64>("/command/pos", 10);
    ros::Publisher  debug_pub = nh.advertise<std_msgs::String>("/debug", 10);

    while(true) {
        debug_pub.publish(debug_msg);
        ros::spinOnce();
    }
    return 0;
}

void hand_cb(const std_msgs::String::ConstPtr& Phrase) {
    debug_msg.data = Phrase->data;
    
}
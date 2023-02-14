#include <iostream>
#include <cmath>

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>

#include "../include/sign_controller.h"

//std_msgs::String debug_msg;

SignController::SignController(const ros::NodeHandle &nh_private_) {
    text_sub        = nh.subscribe<std_msgs::String>("/input/text", 10, hand_cb);
    hand_pub        = nh.advertise<std_msgs::Float64>("/command/pos", 10);
    percent_pub_pub = nh.advertise<std_msgs::Float64>("/command/completion", 10);
    debug_pub       = nh.advertise<std_msgs::String>("/debug", 10);

    position_queue = {};
    percent_complete = 0;

    margin = 0.999;
}

void SignController::hand_update(const ros::TimerEvent& event) {
    if (percent_complete > margin) {
        pos_prev = pos_next;
        pos_nex = position_queue.pop();
        percent_complete = 0;
    }
    hand_lerp();
    command_hand();
    percent_complete += velocity / operating_freq;
}

void SignController::hand_lerp(const std_msgs::String::ConstPtr& Phrase) {
    debug_msg.data = Phrase->data;
    std::string msg = Phrase->data;
    for (char chr : msg) {
        position_queue.push(chr - 96);
    }
    percent_complete = 1;
    
}


void SignController::hand_cb(const std_msgs::String::ConstPtr& Phrase) {
    debug_msg.data = Phrase->data;
    std::string msg = Phrase->data;
    for (char chr : msg) {
        position_queue.push(chr - 96);
    }
    percent_complete = 1;
    
}

// Non Class Functions


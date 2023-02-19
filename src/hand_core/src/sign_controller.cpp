#include <iostream>
#include <cmath>

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>

#include "../include/sign_controller.h"

//std_msgs::String debug_msg;

SignController::SignController(const ros::NodeHandle &nh_private_) {
    text_sub        = nh.subscribe<std_msgs::String>("/input/text", 10, hand_cb);
    //hand_pub        = nh.advertise<std_msgs::Float64>("/command/pos", 10);
    //percent_pub_pub = nh.advertise<std_msgs::Float64>("/command/completion", 10);
    debug_pub       = nh.advertise<std_msgs::String>("/debug", 10);

    thumb_flex_pub = nh.advertise<std_msgs::Float64>("/command/pos", 10);;
    thumb_abd_pub = nh.advertise<std_msgs::Float64>("/command/pos", 10);;
    index_flex_pub = nh.advertise<std_msgs::Float64>("/command/pos", 10);;
    index_abd_pub = nh.advertise<std_msgs::Float64>("/command/pos", 10);;
    middle_flex_pub = nh.advertise<std_msgs::Float64>("/command/pos", 10);;
    middle_abd_pub = nh.advertise<std_msgs::Float64>("/command/pos", 10);;
    ring_flex_pub = nh.advertise<std_msgs::Float64>("/command/pos", 10);;
    ring_abd_pub = nh.advertise<std_msgs::Float64>("/command/pos", 10);;
    pinky_flex_pub = nh.advertise<std_msgs::Float64>("/command/pos", 10);;
    pinky_abd_pub = nh.advertise<std_msgs::Float64>("/command/pos", 10);;
    wrist_flex_pub = nh.advertise<std_msgs::Float64>("/command/pos", 10);;
    wrist_dev_pub = nh.advertise<std_msgs::Float64>("/command/pos", 10);;
    wrist_rot_pub = nh.advertise<std_msgs::Float64>("/command/pos", 10);;

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

void SignController::hand_lerp() {
    thumb_flex = std::lerp(positions_map[pos_prev].thumb_flex, positions_map[pos_next].thumb_flex, percent_complete);
    thumb_abd = std::lerp(positions_map[pos_prev].thumb_abd, positions_map[pos_next].thumb_abd, percent_complete);
    index_flex = std::lerp(positions_map[pos_prev].index_flex, positions_map[pos_next].index_flex, percent_complete);
    index_abd = std::lerp(positions_map[pos_prev].index_abd, positions_map[pos_next].index_abd, percent_complete);
    middle_flex = std::lerp(positions_map[pos_prev].middle_flex, positions_map[pos_next].middle_flex, percent_complete);
    middle_abd = std::lerp(positions_map[pos_prev].middle_abd, positions_map[pos_next].middle_abd, percent_complete);
    ring_flex = std::lerp(positions_map[pos_prev].ring_flex, positions_map[pos_next].ring_flex, percent_complete);
    ring_abd = std::lerp(positions_map[pos_prev].ring_abd, positions_map[pos_next].ring_abd, percent_complete);
    pinky_flex = std::lerp(positions_map[pos_prev].pinky_flex, positions_map[pos_next].pinky_flex, percent_complete);
    pinky_abd = std::lerp(positions_map[pos_prev].pinky_abd, positions_map[pos_next].pinky_abd, percent_complete);
    wrist_flex = std::lerp(positions_map[pos_prev].wrist_flex, positions_map[pos_next].wrist_flex, percent_complete);
    wrist_dev = std::lerp(positions_map[pos_prev].wrist_dev, positions_map[pos_next].wrist_dev, percent_complete);
    wrist_rot = std::lerp(positions_map[pos_prev].wrist_rot, positions_map[pos_next].wrist_rot, percent_complete);
}


void SignController::command_hand() {
    
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


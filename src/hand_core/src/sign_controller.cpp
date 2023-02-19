#include <iostream>
#include <cmath>
#include <string>
#include <jsoncpp/json/json.h>
#include <fstream>

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>


#include "../include/sign_controller.h"

const std::string path_to_json = "hand_positions.json";

SignController::SignController(const ros::NodeHandle &nh_private_) {
    text_sub        = nh_.subscribe<std_msgs::String>("/input/text", 10, &SignController::hand_cb, this);

    debug_pub       = nh_.advertise<std_msgs::String>("/debug", 10);

    thumb_flex_pub = nh_.advertise<std_msgs::Float64>("/command/pos", 10);
    thumb_abd_pub = nh_.advertise<std_msgs::Float64>("/command/pos", 10);
    index_flex_pub = nh_.advertise<std_msgs::Float64>("/command/pos", 10);
    index_abd_pub = nh_.advertise<std_msgs::Float64>("/command/pos", 10);
    middle_flex_pub = nh_.advertise<std_msgs::Float64>("/command/pos", 10);
    middle_abd_pub = nh_.advertise<std_msgs::Float64>("/command/pos", 10);
    ring_flex_pub = nh_.advertise<std_msgs::Float64>("/command/pos", 10);
    ring_abd_pub = nh_.advertise<std_msgs::Float64>("/command/pos", 10);
    pinky_flex_pub = nh_.advertise<std_msgs::Float64>("/command/pos", 10);
    pinky_abd_pub = nh_.advertise<std_msgs::Float64>("/command/pos", 10);
    wrist_flex_pub = nh_.advertise<std_msgs::Float64>("/command/pos", 10);
    wrist_dev_pub = nh_.advertise<std_msgs::Float64>("/command/pos", 10);
    wrist_rot_pub = nh_.advertise<std_msgs::Float64>("/command/pos", 10);

    position_queue = {};
    percent_complete = 0;

    margin = 0.999;

    positions_map = read_from_json(path_to_json);
}

void SignController::hand_update(const ros::TimerEvent& event) {
    if (percent_complete > margin) {
        pos_prev = pos_next;
        pos_next = position_queue.front();
        position_queue.pop();
        percent_complete = 0;
    }
    hand_lerp();
    command_hand();
    percent_complete += velocity / operating_freq;
}

void SignController::hand_lerp() {
    thumb_flex_msg.data = lerp(positions_map[pos_prev]["thumb_flex"].asDouble(), positions_map[pos_next]["thumb_flex"].asDouble(), percent_complete);
    thumb_abd_msg.data = lerp(positions_map[pos_prev]["thumb_abd"].asDouble(), positions_map[pos_next]["thumb_abd"].asDouble(), percent_complete);
    index_flex_msg.data = lerp(positions_map[pos_prev]["index_flex"].asDouble(), positions_map[pos_next]["index_flex"].asDouble(), percent_complete);
    index_abd_msg.data = lerp(positions_map[pos_prev]["index_abd"].asDouble(), positions_map[pos_next]["index_abd"].asDouble(), percent_complete);
    middle_flex_msg.data = lerp(positions_map[pos_prev]["middle_flex"].asDouble(), positions_map[pos_next]["middle_flex"].asDouble(), percent_complete);
    middle_abd_msg.data = lerp(positions_map[pos_prev]["middle_abd"].asDouble(), positions_map[pos_next]["middle_abd"].asDouble(), percent_complete);
    ring_flex_msg.data = lerp(positions_map[pos_prev]["ring_flex"].asDouble(), positions_map[pos_next]["ring_flex"].asDouble(), percent_complete);
    ring_abd_msg.data = lerp(positions_map[pos_prev]["ring_abd"].asDouble(), positions_map[pos_next]["ring_abd"].asDouble(), percent_complete);
    pinky_flex_msg.data = lerp(positions_map[pos_prev]["pinky_flex"].asDouble(), positions_map[pos_next]["pinky_flex"].asDouble(), percent_complete);
    pinky_abd_msg.data = lerp(positions_map[pos_prev]["pinky_abd"].asDouble(), positions_map[pos_next]["pinky_abd"].asDouble(), percent_complete);
    wrist_flex_msg.data = lerp(positions_map[pos_prev]["wrist_flex"].asDouble(), positions_map[pos_next]["wrist_flex"].asDouble(), percent_complete);
    wrist_dev_msg.data = lerp(positions_map[pos_prev]["wrist_dev"].asDouble(), positions_map[pos_next]["wrist_dev"].asDouble(), percent_complete);
    wrist_rot_msg.data = lerp(positions_map[pos_prev]["wrist_rot"].asDouble(), positions_map[pos_next]["wrist_rot"].asDouble(), percent_complete);
}


void SignController::command_hand() {
    thumb_flex_pub.publish(thumb_flex_msg);
    thumb_abd_pub.publish(thumb_abd_msg);
    index_flex_pub.publish(index_flex_msg);
    index_abd_pub.publish(index_abd_msg);
    middle_flex_pub.publish(middle_flex_msg);
    middle_abd_pub.publish(middle_abd_msg);
    ring_flex_pub.publish(ring_flex_msg);
    ring_abd_pub.publish(ring_abd_msg);
    pinky_flex_pub.publish(pinky_flex_msg);
    pinky_abd_pub.publish(pinky_abd_msg);
    wrist_flex_pub.publish(wrist_flex_msg);
    wrist_dev_pub.publish(wrist_dev_msg);
    wrist_rot_pub.publish(wrist_rot_msg);
}


void SignController::hand_cb(const std_msgs::String::ConstPtr& Phrase) {
    debug_msg.data = Phrase->data;
    std::string msg = Phrase->data;
    for (char chr : msg) {
        std::string s(1, chr);
        position_queue.push(s);
    }
    percent_complete = 1;
    
}

double lerp(double a, double b, double f) {
    return a * (1.0 - f) + (b * f);
}

Json::Value read_from_json(std::string path_to_json) {
    std::ifstream people_file(path_to_json, std::ifstream::binary);
    Json::Value people;
    people_file >> people;
    return people;
}
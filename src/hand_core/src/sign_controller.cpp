#include <iostream>
#include <cmath>
#include <string>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <cstdio>
#include <chrono>
#include <thread>

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>


#include "../include/sign_controller.h"
#include "../include/json_fake.h"

//const std::string path_to_json = "/home/nick/hand_ws/src/hand_core/hand_positions.json";

SignController::SignController(const ros::NodeHandle &nh_private_) {
    text_sub        = nh_.subscribe<std_msgs::String>("/input/text", 10, &SignController::hand_cb, this);
    //percent_sub        = nh_.subscribe<std_msgs::Float64>("/percent", 10, &SignController::percent_cb, this);
    debug_pub       = nh_.advertise<std_msgs::String>("/debug", 10);
    clear_pub       = nh_.advertise<std_msgs::Bool>("/output/clear", 10);

    thumb_flex_pub = nh_.advertise<std_msgs::Float64>("/actuation/thumb/flex", 10);
    thumb_abd_pub = nh_.advertise<std_msgs::Float64>("/actuation/thumb/abd", 10);
    index_flex_pub = nh_.advertise<std_msgs::Float64>("/actuation/index/flex", 10);
    index_abd_pub = nh_.advertise<std_msgs::Float64>("/actuation/index/abd", 10);
    middle_flex_pub = nh_.advertise<std_msgs::Float64>("/actuation/middle/flex", 10);
    middle_abd_pub = nh_.advertise<std_msgs::Float64>("/actuation/middle/abd", 10);
    ring_flex_pub = nh_.advertise<std_msgs::Float64>("/actuation/ring/flex", 10);
    ring_abd_pub = nh_.advertise<std_msgs::Float64>("/actuation/ring/abd", 10);
    pinky_flex_pub = nh_.advertise<std_msgs::Float64>("/actuation/pinky/flex", 10);
    pinky_abd_pub = nh_.advertise<std_msgs::Float64>("/actuation/pinky/abd", 10);
    wrist_flex_pub = nh_.advertise<std_msgs::Float64>("/actuation/wrist/flex", 10);

    position_queue = {};

    margin = 0.99;
    period = 2;
    started = false;

    //positions_map = read_from_json();
    json_out = json_fake_func();
}

void SignController::command_hand() {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    thumb_flex_msg.data = json_out[pos_next]["thumb_flex"];
    thumb_abd_msg.data = json_out[pos_next]["thumb_abd"];
    index_flex_msg.data = json_out[pos_next]["index_flex"];
    index_abd_msg.data = json_out[pos_next]["index_abd"];
    middle_flex_msg.data = json_out[pos_next]["middle_flex"];
    middle_abd_msg.data = json_out[pos_next]["middle_abd"];
    ring_flex_msg.data = json_out[pos_next]["ring_flex"];
    ring_abd_msg.data =json_out[pos_next]["ring_abd"];
    pinky_flex_msg.data = json_out[pos_next]["pinky_flex"];
    pinky_abd_msg.data = json_out[pos_next]["pinky_abd"];
    wrist_flex_msg.data = json_out[pos_next]["wrist_flex"];

    thumb_flex_pub.publish(thumb_flex_msg);
    sleep_for(milliseconds(5));
    thumb_abd_pub.publish(thumb_abd_msg);
    sleep_for(milliseconds(5));
    index_flex_pub.publish(index_flex_msg);
    sleep_for(milliseconds(5));
    index_abd_pub.publish(index_abd_msg);
    sleep_for(milliseconds(5));
    middle_flex_pub.publish(middle_flex_msg);
    sleep_for(milliseconds(5));
    middle_abd_pub.publish(middle_abd_msg);
    sleep_for(milliseconds(5));
    ring_flex_pub.publish(ring_flex_msg);
    sleep_for(milliseconds(5));
    ring_abd_pub.publish(ring_abd_msg);
    sleep_for(milliseconds(5));
    pinky_flex_pub.publish(pinky_flex_msg);
    sleep_for(milliseconds(5));
    pinky_abd_pub.publish(pinky_abd_msg);
    sleep_for(milliseconds(5));
    wrist_flex_pub.publish(wrist_flex_msg);
    sleep_for(milliseconds(5));
}


void SignController::hand_cb(const std_msgs::String::ConstPtr& Phrase) {
    debug_msg.data = Phrase->data;
    std::string msg = Phrase->data;
    //debug_pub.publish(debug_msg);
    std::string z(1, '0');
    position_queue.push(z);
    for (char chr : msg) {
        std::string s(1, chr);
        std::string z(1, '0');
        position_queue.push(s);
        position_queue.push(z);
    }
    pos_next = position_queue.front();
    position_queue.pop();
    debug_msg.data = pos_next;
    debug_pub.publish(debug_msg);
    command_hand();
    started = true;
}

void SignController::next_sign(const ros::TimerEvent& event) {
    if (!position_queue.empty()) {
        pos_next = position_queue.front();
        position_queue.pop();
        debug_msg.data = pos_next;
        debug_pub.publish(debug_msg);
        command_hand();
    }
}


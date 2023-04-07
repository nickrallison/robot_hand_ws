#include <ros/ros.h>
#include <vector>
#include <queue>
#include <jsoncpp/json/json.h>
#include <fstream>

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

class SignController
{
    public:
        // Constructor
        SignController(const ros::NodeHandle &nh_private_);

        // Destructor
        ~SignController() = default;

        // Callback methods
        void hand_cb(const std_msgs::String::ConstPtr& Phrase);
        void next_sign(const ros::TimerEvent& event);
        double period;

    private:
        /**
         * Node handlers
         */
        ros::NodeHandle nh_;
        ros::NodeHandle nh_private_;


        /*
         * Messages
         */

        std_msgs::Float64 thumb_flex_msg;
        std_msgs::Float64 thumb_abd_msg;
        std_msgs::Float64 index_flex_msg;
        std_msgs::Float64 index_abd_msg;
        std_msgs::Float64 middle_flex_msg;
        std_msgs::Float64 middle_abd_msg;
        std_msgs::Float64 ring_flex_msg;
        std_msgs::Float64 ring_abd_msg;
        std_msgs::Float64 pinky_flex_msg;
        std_msgs::Float64 pinky_abd_msg;
        std_msgs::Float64 wrist_flex_msg;
        std_msgs::Float64 wrist_dev_msg;
        std_msgs::Float64 wrist_rot_msg;

        std_msgs::Float64 percent_msg;

        std_msgs::String debug_msg;
        std_msgs::Bool clear_msg;

        /**
         * Publishers and subscribers
         */
        ros::Subscriber text_sub;
        ros::Subscriber percent_sub;

        ros::Publisher  debug_pub;
        ros::Publisher  clear_pub;

        ros::Publisher thumb_flex_pub;
        ros::Publisher thumb_abd_pub;
        ros::Publisher index_flex_pub;
        ros::Publisher index_abd_pub;
        ros::Publisher middle_flex_pub;
        ros::Publisher middle_abd_pub;
        ros::Publisher ring_flex_pub;
        ros::Publisher ring_abd_pub;
        ros::Publisher pinky_flex_pub;
        ros::Publisher pinky_abd_pub;
        ros::Publisher wrist_flex_pub;
        ros::Publisher wrist_dev_pub;
        ros::Publisher wrist_rot_pub;

        /**
         * Runtime Functions
         */
        void command_hand();
        void get_msgs();
        

        
        /**
         * Runtime variables
         */
        std::string pos_prev = "0";
        std::string pos_next = "0";

        std::queue<std::string> position_queue;

        double margin;
        bool started;

        std::map<std::string, std::map<std::string, double>> json_out;

};

#include <ros/ros.h>
#include <vector>
#include <queue>
#include <jsoncpp/json/json.h>
#include <fstream>

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>

class SignController
{
    public:
        // Constructor
        SignController(const ros::NodeHandle &nh_private_);

        // Destructor
        ~SignController() = default;

        // Callback methods
        void hand_update(const ros::TimerEvent& event);
        void hand_cb(const std_msgs::String::ConstPtr& Phrase);


        // Public Vars
        double operating_freq = 30;



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

        std_msgs::String debug_msg;

        /**
         * Publishers and subscribers
         */
        ros::Subscriber text_sub;

        ros::Publisher  debug_pub;

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
        void hand_lerp();
        

        
        /**
         * Runtime variables
         */
        std::string pos_prev = "none";
        std::string pos_next = "none";

        std::queue<std::string> position_queue;
        double percent_complete;
        double velocity = 0.1; // signs / second

        double margin;

        double thumb_flex =  0;
        double thumb_abd =   0;
        double index_flex =  0;
        double index_abd =   0;
        double middle_flex = 0;
        double middle_abd =  0;
        double ring_flex =   0;
        double ring_abd =    0;
        double pinky_flex =  0;
        double pinky_abd =   0;
        double wrist_flex =  0;
        double wrist_dev =   0;
        double wrist_rot =   0;

        Json::Value positions_map;

};

double lerp(double a, double b, double f);
Json::Value read_from_json(std::string path_to_json);
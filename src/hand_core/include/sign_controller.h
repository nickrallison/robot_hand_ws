#include <ros/ros.h>
#include <vector>
#include <queue>

class SignController
{
    public:
        // Constructor
        LegInverseKinematicsProcessor(const ros::NodeHandle &nh_private_);

        // Destructor
        ~LegInverseKinematicsProcessor() = default;

        // Callback methods
        void hand_update(const ros::TimerEvent& event)
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

        std_msgs::Float64 superior_right_shoulder_msg;

        /**
         * Publishers and subscribers
         */
        ros::Subscriber text_sub;
        ros::Publisher  hand_pub;
        ros::Publisher  percent_pub_pub;
        ros::Publisher  debug_pub;

        
        
        
        /**
         * Runtime variables
         */
        int pos_prev = 0;
        int pos_next = 0;

        std::queue<int> position_queue;
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

};
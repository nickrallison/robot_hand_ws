import os
import rospy
import time
from std_msgs.msg import String, Bool

file_path = '/home/nick/hand_ws/src/hand_core/src/test.txt'  # Replace with your file path
topic = '/input/text'  # Replace with your desired ROS topic name

import os
import rospy
from std_msgs.msg import String

rospy.init_node('file_reader_node', anonymous=True)
pub = rospy.Publisher(topic, String, queue_size=10)
period = 3
rate = rospy.Rate(1.0 / period)

def read_publish_delete_file(file_path):
    """
    Reads a file, publishes its contents to a ROS topic, and then deletes the file.

    Args:
        file_path (str): The path of the file to be read and deleted.
        topic (str): The name of the ROS topic to publish the file contents to.
    """
    try:
        with open(file_path, 'r') as file:
            file_contents = file.read()
            rospy.loginfo("Publishing file contents to topic: %s", topic)
            pub.publish(file_contents)
        # Delete the file
        os.remove(file_path)
        rospy.loginfo("File '%s' deleted successfully!", file_path)
    except FileNotFoundError:
        rospy.loginfo("File '%s' not found.", file_path)
    except Exception as e:
        rospy.logerr("An error occurred: %s", e)

while not rospy.is_shutdown():
    read_publish_delete_file(file_path)
    rate.sleep()



    
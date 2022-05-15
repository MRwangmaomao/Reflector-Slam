//
// Created by wpr on 2022/5/15.
//

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>
#include <vector>

const int THRETHOLD = 1000;
const int WINDOWS_SIZE = 80;


void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    // Get laser data. frame_id is scanner
    ROS_INFO("get laser seq is %d", msg->header.seq);
    std::vector<float> ranges = msg->ranges;
    for (int i = WINDOWS_SIZE - 1; i < ranges.size() - WINDOWS_SIZE - 1; i++) {
        if (msg->intensities[i] > THRETHOLD && (msg->intensities[i] > msg->intensities[i-1]
            && msg->intensities[i] > msg->intensities[i+1])) {
            int max = 0;
            for(int j = i - WINDOWS_SIZE; j < i + WINDOWS_SIZE; j++) {
                if (max < msg->intensities[j]) {
                    max = msg->intensities[j];
                }
            }
            if (msg->intensities[i] >= max) {
                double angle = msg->angle_min + i * msg->angle_increment;
                double point_x = ranges[i] * cos(angle);
                double point_y = ranges[i] * sin(angle);
                ROS_INFO("      detect reflect position is %f, %f", point_x, point_y);
            }
        }
    }

}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "reflector_slam");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/scan", 10, laserCallback);
    ros::spin();
    return 0;
}
//
// Created by wpr on 2022/5/15.
//

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>
#include <vector>

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    // Get laser data.
    ROS_INFO("get laser seq is %d", msg->header.seq);
    std::vector<float> ranges = msg->ranges;

    for (int i = 0; i < ranges.size(); i++) {
        double angle = msg->angle_min + i * msg->angle_increment;
        double point_x = ranges[i] * cos(angle);
        double point_y = ranges[i] * sin(angle);
        float intensity = msg->intensities[i];
        
        // std::cout << ranges[i] << "," << std::endl;
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
#ifndef DRONE_COLTROLLER__COMP_CONTROL_TORQUE_HPP
#define DRONE_COLTROLLER__COMP_CONTROL_TORQUE_HPP

// Include necessary C/C++ headers
#include <functional>
#include <chrono>

// Include ROS related headers
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <sensor_msgs/msg/imu.hpp>

class compControlTorque : public rclcpp::Node
{
	public:
	compControlTorque();

	protected:
		double torqueVals_[4], accel_[3], gyro_[3];
		rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr motorTqPub_;
		rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imuSub_;
		rclcpp::TimerBase::SharedPtr timer_;
		void pubMotorTqMsg();
		void onQuadImuMsg(const sensor_msgs::msg::Imu::SharedPtr msg);
};

#endif // #ifndef DRONE_COLTROLLER__COMP_CONTROL_TORQUE_HPP
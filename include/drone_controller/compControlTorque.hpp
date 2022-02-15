#ifndef DRONE_COLTROLLER__COMP_CONTROL_TORQUE_HPP
#define DRONE_COLTROLLER__COMP_CONTROL_TORQUE_HPP

// Include necessary C/C++ headers
#include <functional>
#include <chrono>

// Include ROS related headers
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>

class compControlTorque : public rclcpp::Node
{
	public:
	compControlTorque();

	protected:
	double torqueVals_[4];
	rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_;
	rclcpp::TimerBase::SharedPtr timer_;
	void callbackFun();
};

#endif // #ifndef DRONE_COLTROLLER__COMP_CONTROL_TORQUE_HPP
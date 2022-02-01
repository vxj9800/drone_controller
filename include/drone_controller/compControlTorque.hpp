// Include necessary C/C++ headers
#include <functional>
#include <chrono>

// Include ROS related headers
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"

class compControlTorque : public rclcpp::Node
{
	public:
	compControlTorque();

	protected:
	double torqueVals_[3];
	rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr publisher_;
	rclcpp::TimerBase::SharedPtr timer_;
	void callbackFun();
};
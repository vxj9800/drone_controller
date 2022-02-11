#include "drone_controller/compControlTorque.hpp"

compControlTorque::compControlTorque() : Node("compControlTorque")
{
	torqueVals_[0] = 0; torqueVals_[1] = 0; torqueVals_[2] = 0;
	publisher_ = this->create_publisher<geometry_msgs::msg::Vector3>("control_torque",10);
	timer_ = this->create_wall_timer(std::chrono::milliseconds(500),std::bind(&compControlTorque::callbackFun,this));
}

void compControlTorque::callbackFun()
{
	geometry_msgs::msg::Vector3 message;
	message.x = torqueVals_[0];
	message.y = torqueVals_[1];
	message.z = torqueVals_[3];
	RCLCPP_INFO(this->get_logger(),"Publishing message.");
	publisher_->publish(message);
}

int main(int argc, char ** argv)
{
	rclcpp::init(argc,argv);
	rclcpp::spin(std::make_shared<compControlTorque>());
	rclcpp::shutdown();
	return 0;
}

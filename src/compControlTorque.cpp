#include "drone_controller/compControlTorque.hpp"

compControlTorque::compControlTorque() : Node("compControlTorque")
{
	torqueVals_[0] = 0; torqueVals_[1] = 0;
	torqueVals_[2] = 0; torqueVals_[3] = 0.001;
	publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/myQuad/motorIn", 10);
	timer_ = this->create_wall_timer(std::chrono::milliseconds(500),std::bind(&compControlTorque::callbackFun,this));
}

void compControlTorque::callbackFun()
{
	std_msgs::msg::Float64MultiArray message;
	std_msgs::msg::MultiArrayDimension dim;
	dim.label = "torque"; dim.size = 4;
	dim.stride = 1;
	message.layout.dim.push_back(dim);
	message.data.push_back(torqueVals_[0]);
	message.data.push_back(torqueVals_[1]);
	message.data.push_back(torqueVals_[2]);
	message.data.push_back(torqueVals_[3]);
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

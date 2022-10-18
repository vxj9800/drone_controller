#include "drone_controller/compControlTorque.hpp"

compControlTorque::compControlTorque() : Node("compControlTorque")
{
	torqueVals_[0] = 0;
	torqueVals_[1] = 0;
	torqueVals_[2] = 0;
	torqueVals_[3] = 0;
	motorTqPub_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/myQuad/motorIn", 10);
	imuSub_ = this->create_subscription<sensor_msgs::msg::Imu>("myQuad/imuData",
															   rclcpp::QoS(rclcpp::QoSInitialization::from_rmw(rmw_qos_profile_sensor_data)),
															   std::bind(&compControlTorque::onQuadImuMsg, this, std::placeholders::_1));
	timer_ = this->create_wall_timer(std::chrono::milliseconds(10), std::bind(&compControlTorque::pubMotorTqMsg, this));
}

void compControlTorque::pubMotorTqMsg()
{
	if (torqueVals_[0] < 5.3)
	{
		torqueVals_[0] += 0.05;
		torqueVals_[1] += 0.05;
		torqueVals_[2] += 0.05;
		torqueVals_[3] += 0.05;
	}
	std_msgs::msg::Float64MultiArray message;
	std_msgs::msg::MultiArrayDimension dim;
	dim.label = "torque"; dim.size = 4;
	dim.stride = 1;
	message.layout.dim.push_back(dim);
	message.data.push_back(torqueVals_[0]);
	message.data.push_back(torqueVals_[1]);
	message.data.push_back(torqueVals_[2]);
	message.data.push_back(torqueVals_[3]);
	// RCLCPP_INFO(this->get_logger(),"Publishing message.");
	motorTqPub_->publish(message);
}

void compControlTorque::onQuadImuMsg(const sensor_msgs::msg::Imu::SharedPtr msg)
{
	// Extract accelerometer data
	accel_[0] = msg->linear_acceleration.x;
	accel_[1] = msg->linear_acceleration.y;
	accel_[2] = msg->linear_acceleration.z;

	// Extract accelerometer data
	gyro_[0] = msg->angular_velocity.x;
	gyro_[1] = msg->angular_velocity.y;
	gyro_[2] = msg->angular_velocity.z;
}

int main(int argc, char **argv)
{
	rclcpp::init(argc,argv);
	rclcpp::spin(std::make_shared<compControlTorque>());
	rclcpp::shutdown();
	return 0;
}

/*
 * DriveController.cpp
 *
 *  Created on: May 15, 2017
 *      Author: gracekwak
 */
#include "DriveController.h"

#define PI 3.14159265

const int CAN_TALON_FRONT_LEFT = 24;
const int CAN_TALON_BACK_LEFT = 21;
const int CAN_TALON_FRONT_RIGHT = 27;
const int CAN_TALON_BACK_RIGHT = 26;

const double MAX_Y_RPM_ACTUAL = 1325.0; //950
const double MAX_Y_RPM = 600.0;
const double MAX_ROT_VEL_ACTUAL = 50.0; //35
const double MAX_YAW_RATE = (MAX_ROT_VEL_ACTUAL / MAX_Y_RPM_ACTUAL) * MAX_Y_RPM; //scale down from actual rot vel

const double UNITS_PER_ROT = 4096.0;
const double MINUTE_CONVERSION = 600.0; //100 ms to min

double output_l = 0.0;
double output_r = 0.0;

double Kf_d = 1.0 / MAX_Y_RPM_ACTUAL; //scale down targets
double Kp_d = 0.0;
double Ki_d = 0.0;
double Kd_d = 0.0;

double P_l = 0.0;
double P_r = 0.0;

double I_l = 0.0;
double I_r = 0.0;

double x = 0;
double y = 0;

double i_l = 0.0;
double i_r = 0.0;

double D_l = 0.0;
double D_r = 0.0;

double d_r = 0.0;
double d_l = 0.0;

double error_l = 0.0;
double error_r = 0.0;
double target_l = 0.0;
double target_r = 0.0;
double current_l = 0.0;
double current_r = 0.0;
double last_error_r = 0.0;
double last_error_l = 0.0;

double target_yaw_rate = 0.0;
double yaw_error = 0.0;
double yaw_rate_current = 0.0;
double yaw_last_error = 0.0;

double d_yaw = 0.0;
double k_p_yaw = 0.0;
double k_d_yaw = 0.0;

double yaw_output = 0.0;

DriveController::DriveController() {

	canTalonFrontLeft = new TalonSRX(CAN_TALON_FRONT_LEFT);
	canTalonBackLeft = new TalonSRX(CAN_TALON_BACK_LEFT);
	canTalonBackLeft->Set(ControlMode::Follower, CAN_TALON_FRONT_LEFT);

	canTalonFrontRight = new TalonSRX(CAN_TALON_FRONT_RIGHT);
	canTalonBackRight = new TalonSRX(CAN_TALON_BACK_RIGHT);
	canTalonBackRight->Set(ControlMode::Follower,CAN_TALON_FRONT_RIGHT);

	ahrs = new AHRS(SPI::Port::kMXP, 200);

}

void DriveController::Drive(Joystick *joyThrottle) {

	if(joyThrottle->GetRawButton(4)){
		x = 1.0;
	} else if(joyThrottle->GetRawButton(2)) {
		x = -1.0;
	} else {
		x = 0.0;
	}

	if(joyThrottle->GetRawButton(3)){
		y = 1.0;
	} else if(joyThrottle->GetRawButton(1)) {
		y = -1.0;
	} else {
		y = 0.0;
	}

	target_l = -x * MAX_Y_RPM;
	target_r = -x * MAX_Y_RPM;

	current_l = (canTalonFrontLeft->GetSensorCollection().GetQuadratureVelocity() / UNITS_PER_ROT) * MINUTE_CONVERSION;
	current_r = (canTalonFrontRight->GetSensorCollection().GetQuadratureVelocity() / UNITS_PER_ROT) * MINUTE_CONVERSION; //right is negative for forward

	error_l = target_l - current_l;
	error_r = target_r + current_r;

	target_yaw_rate = 1.0 * (-y) * MAX_YAW_RATE; //left should be positive
	yaw_rate_current = 1.0 * (double) ahrs->GetRawGyroZ()
			* (double) ((PI) / 180);
	yaw_error = target_yaw_rate - yaw_rate_current;

	target_l = target_l - (target_yaw_rate * (MAX_Y_RPM / MAX_YAW_RATE)); //linear velocities for each side, controlling inputs
	target_r = target_r + (target_yaw_rate * (MAX_Y_RPM / MAX_YAW_RATE));

	d_yaw = yaw_error - yaw_last_error;
	yaw_output = (k_p_yaw * yaw_error) + (k_d_yaw * d_yaw);

	target_l = target_l - yaw_output; //after using yaw controller
	target_r = target_r + yaw_output;

	P_l = Kp_d * error_l;
	P_r = Kp_d * error_r;

	i_l += error_l;
	i_r += error_r;

	I_l = Ki_d * i_l;
	I_r = Ki_d * i_r;

	d_r = (error_r - last_error_r);
	d_l = (error_l - last_error_l);

	D_l = Kd_d * d_l;
	D_r = Kd_d * d_r;

	output_l = P_l + I_l + D_l + (Kf_d * target_l);
	output_r = P_r + I_r + D_r + (Kf_d * target_r);

	canTalonFrontLeft->Set(ControlMode::PercentOutput, -output_l); //backs are slaved to fronts
	canTalonFrontRight->Set(ControlMode::PercentOutput, output_r);

	last_error_l = error_l;
	last_error_r = error_r;
	yaw_last_error = yaw_error;

}
// void DriveController::DriveTest(Joystick *joyThrottle, Joystick *joyWheel) {

// 	double target_left = joyThrottle->GetY();//joyWheel->GetX();
// 	double target_right = joyThrottle->GetY();//-joyWheel->GetX();

//	canTalonFrontLeft->Set(-target_left);
//	canTalonFrontRight->Set(target_right);

// }

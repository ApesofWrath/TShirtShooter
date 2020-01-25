/*
 * Barrel.cpp
 *
 *  Created on: May 16, 2017
 *      Author: gracekwak
 */

#include "Barrel.h"
//#include <WPILib.h>
#define PI 3.14159265

const double DOWN_ANGLE = 0.0;
const double UP_ANGLE = PI / 2.2;

const double DOWN_SPEED = 0.15;
const double UP_SPEED = 0.325;

const double MAX_VELOCITY = 0.0; //set these values
const double MAX_ACCELERATION = 0.0;
const double TIME_STEP = 0.01;

const int ZERO_STATE = 0;
const int DOWN_STATE = 1;
const int UP_STATE = 2;
const int STOP_STATE = 3;
int barrel_state = ZERO_STATE; //init state

const int CAN_TALON_BARREL = 28;

const int BARREL_SLEEP_TIME = 0.0;
const double BARREL_WAIT_TIME = 0.01;

const int UNITS_PER_ROT = 4096;
const double ACCEPTABLE_ERROR = PI / 25.0;

const double MAX_OUTPUT = 1.0;
const double MIN_OUTPUT = -1.0;

double position = 0.0;
double output = 0.0;

double Kp = 0.0;
double Ki = 0.0;
double Kd = 0.0;

double P = 0.0;
double I = 0.0;
double D = 0.0;

double i = 0.0;
double d = 0.0;

double error = 0.0;
double last_error = 0.0;

std::thread BarrelThread;

double ref_;
bool active_;

frc::Timer *barrelTimer = new frc::Timer();

Barrel::Barrel() {

	canTalonBarrel = new TalonSRX(CAN_TALON_BARREL);

	ref_ = DOWN_ANGLE;
	active_ = false;

}

void Barrel::MoveTo(double ref) { //ref must be in radians from the starting position, the horizontal is NOT 0 Rad

	position = GetBarrelPos();

	if (ref <= position) { //going down

		Kp = 1.0; //not real values
		Ki = 1.0;
		Kd = 1.0;

	} else { //going up

		Kp = 0.0;
		Ki = 0.0;
		Kd = 0.0;

	}

	error = ref - position;

	P = Kp * error;

	i += error;
	I = Ki * i;

	d = (error - last_error);
	D = Kd * d;

	output = P + I + D;

	if (output > MAX_OUTPUT) {
		output = MAX_OUTPUT;
	} else if (output < MIN_OUTPUT) {
		output = MIN_OUTPUT;
	}

	canTalonBarrel->Set(ControlMode::PercentOutput, -output);

	last_error = error;

}

bool Barrel::IsAtPosition(double ref) {

	if (std::abs(GetBarrelPos() - ref) <= ACCEPTABLE_ERROR) { //error will be 0 on startup
		return true;
	} else {
		return false;
	}

}

double Barrel::GetBarrelPos() {
	return canTalonBarrel->GetSensorCollection().GetQuadraturePosition()
			* (2.0 * PI / (double) UNITS_PER_ROT);
}

void Barrel::BarrelStateMachine() {

	switch (barrel_state) {

	case ZERO_STATE:
	  canTalonBarrel->GetSensorCollection().SetQuadraturePosition(0, 0);
		//active_ = false;
		break;

	case DOWN_STATE:
		canTalonBarrel->Set(ControlMode::PercentOutput, DOWN_SPEED);
		//ref_ = DOWN_ANGLE;
		//active_ = true;
		//IsAtPosition(DOWN_ANGLE);
		break;

	case UP_STATE:
	  canTalonBarrel->Set(ControlMode::PercentOutput, -UP_SPEED);
		//ref_ = UP_ANGLE;
		//active_ = true;
		//IsAtPosition(UP_ANGLE);
		break;

	case STOP_STATE:
    canTalonBarrel->Set(ControlMode::PercentOutput, 0.0);
		//active_ = false;
		break;

	}

}

void Barrel::BarrelWrapper(Barrel *barrel, double *ref, bool *active) {

	while (true) {

		while (frc::RobotState::IsEnabled()) {

			std::this_thread::sleep_for(std::chrono::milliseconds(BARREL_SLEEP_TIME));

			while (*active) {

				if (barrelTimer->HasPeriodPassed(BARREL_WAIT_TIME)) {

					barrel->MoveTo(*ref);
					barrelTimer->Reset();
				}
			}
		}
	}

}

void Barrel::StartThread() {

	Barrel *barrel = this;
	BarrelThread = std::thread(&Barrel::BarrelWrapper, barrel, &ref_, &active_);
	BarrelThread.detach();

}

void Barrel::DisableThread() {

	BarrelThread.~thread();
}

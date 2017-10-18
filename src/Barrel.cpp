/*
 * Barrel.cpp
 *
 *  Created on: May 16, 2017
 *      Author: gracekwak
 */
#include "Barrel.h"
#include <WPILib.h>
#define PI 3.14159265

const double DOWN_ANGLE = 0.0;
const double UP_ANGLE = PI/2.2;

const double SPIN_SPEED = 0.6;

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
const double ACCEPTABLE_ERROR = PI/25.0;

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

const int DOWN_TO_UP_ANGLE = 0;
const int UP_TO_DOWN_ANGLE = 1;

int ref_pos_;

Timer *barrelTimer = new Timer();

Barrel::Barrel() {

	canTalonBarrel = new CANTalon(CAN_TALON_BARREL);

	ref_pos_ = DOWN_ANGLE;

}

void Barrel::MoveTo(double ref) { //ref must be in radians from the starting position, the horizontal is NOT 0 Rad

//	position = GetBarrelPos();
//
//	if (ref <= position){ //going down
//
//		Kp = 1.0; //not real values
//		Ki = 1.0;
//		Kd = 1.0;
//
//	} else { //going up
//
//		Kp = 0.0;
//		Ki = 0.0;
//		Kd = 0.0;
//
//	}
//
//	error = ref - position;
//
//	P = Kp * error;
//
//	i += error;
//	I = Ki * i;
//
//	d = (error - last_error);
//	D = Kd * d;
//
//	output = P + I + D;
//
//	if(output > MAX_OUTPUT) {
//		output = MAX_OUTPUT;
//	}
//	else if(output < MIN_OUTPUT) {
//		output = MIN_OUTPUT;
//	}
//
//	canTalonBarrel->Set(output);
//
//	last_error = error;

}

bool Barrel::IsAtPosition(double ref) {

	if(std::abs(GetBarrelPos() - ref) <= ACCEPTABLE_ERROR) { //error will be 0 on startup
		return true;
	}
	else {
		return false;
	}

}

double Barrel::GetBarrelPos() {
	return canTalonBarrel->GetEncPosition() * (2.0 * PI / (double)UNITS_PER_ROT);
}

void Barrel::BarrelStateMachine() {

	switch(barrel_state) {

	case ZERO_STATE:
		canTalonBarrel->SetEncPosition(0.0);
		break;

	case DOWN_STATE:
		canTalonBarrel->Set(SPIN_SPEED);
		IsAtPosition(DOWN_ANGLE);
		break;

	case UP_STATE:
		canTalonBarrel->Set(-SPIN_SPEED);
		IsAtPosition(UP_ANGLE);
		break;

	case STOP_STATE:
		canTalonBarrel->Set(0.0);
		break;

	}

}

void Barrel::MoveWrapper(Barrel *barrel, int *ref_pos) {

//	std::vector<std::vector<double>> barrel_profile = { };
//
//		int barrel_index = 0;
//		int last_ref = 0;
//		int profile = 0;
//
//		barrelTimer->Start();
//
//		while (true) {
//			while (frc::RobotState::IsEnabled()) {
//
//				std::this_thread::sleep_for(
//						std::chrono::milliseconds(BARREL_SLEEP_TIME));
//
//				if (barrelTimer->HasPeriodPassed(BARREL_WAIT_TIME)) { //if enough time has passed to start a new loop
//
//					profile = *ref_pos;
//
//					switch (profile) {
//
//					case DOWN_TO_UP_ANGLE:
//						std::cout << "0" << std::endl;
//						barrel_profile = down_to_up_profile;
//						if (last_ref != profile) {
//							barrel->SetIndex(0);
//						}
//						break;
//
//					case UP_TO_DOWN_ANGLE:
//						std::cout << "1" << std::endl;
//						barrel_profile = standard_to_down_profile;
//						if (last_ref != profile) {
//							barrel->SetIndex(0);
//						}
//						break;
//
//					case STARTING_TO_STANDARD_ANGLE:
//						std::cout << "2" << std::endl;
//						gear_profile = starting_to_standard_profile;
//						if (last_ref != profile) {
//							gp->SetIndex(0);
//						}
//						break;
//
//					}
//					last_ref = profile;
//
//					if (profile == 1) {
//						gp->MoveArm(gear_profile.at(0).at(gp->gearpickup_index),
//								0.0); //see if all you need to do is not have velocity motion profiles
//						std::cout<<"HERE"<<std::endl;
//					} else {
//						gp->MoveArm(gear_profile.at(0).at(gp->gearpickup_index),
//								gear_profile.at(1).at(gp->gearpickup_index));
//					}
//					std::cout << "Target: "
//							<< gear_profile.at(0).at(gp->gearpickup_index)
//							<< std::endl;
//
//					//std::cout << "ref" << *ref_pos << std::endl;
//
//					if (gp->gearpickup_index < gear_profile.at(0).size() - 1) {
//						gp->gearpickup_index++;
//					}
//
//					timerPickup->Reset();
//
//				}
//
//			}
//		}

}

void Barrel::SetIndex(int index) {
	//barrel_index = index;
}


void Barrel::StartThread() {

//	Barrel *barrel = this;
//
//  BarrelThread = std::thread(&Barrel::MoveWrapper, barrel, &ref_pos_);
//	BarrelThread.detach();

}

void Barrel::DisableThread() {

	//BarrelThread.~thread();
}

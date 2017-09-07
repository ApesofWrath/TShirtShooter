/*
 * Barrel.cpp
 *
 *  Created on: May 16, 2017
 *      Author: gracekwak
 */
//position
#include "Barrel.h"
#include <WPILib.h>
#define PI 3.14159

const int UNITS_PER_ROT = 4096;
const double ACCEPTABLE_ERROR = PI/30.0;

const int ZERO_STATE = 0;
const int DOWN_STATE = 1;
const int SIXTY_STATE = 2;
const int SEVENTY_STATE = 3;
const int EIGHTY_STATE = 4;
int barrel_pos_state = ZERO_STATE; //init state

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

Barrel::Barrel() {

	canTalonBarrel = new CANTalon(0);

}

void Barrel::MoveTo(double ref) { //ref must be in radians from the starting position, the horizontal is NOT 0 Rad

	position = canTalonBarrel->GetEncPosition() * (2 * PI / UNITS_PER_ROT); //conversion to rad

	if (ref <= position){ //going down

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

	canTalonBarrel->Set(output);

	last_error = error;

}

bool Barrel::IsAtPosition() {

	if(error <= ACCEPTABLE_ERROR) {
		return true;
	}
	else {
		return false;
	}

}

void Barrel::BarrelStateMachine() {

	switch(barrel_pos_state) {

	case ZERO_STATE:
		canTalonBarrel->Set(0);
		break;

	case DOWN_STATE:
		MoveTo(0.0);
		break;

	case SIXTY_STATE:
		MoveTo(PI/3);
		IsAtPosition();
		break;

	case SEVENTY_STATE:
		MoveTo(PI/2.5);
		IsAtPosition();
		break;

	case EIGHTY_STATE:
		MoveTo(PI/2.2);
		IsAtPosition();
		break;

	}

}

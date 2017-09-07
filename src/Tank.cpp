/*
 * Tank.cpp
 *
 *  Created on: May 17, 2017
 *      Author: gracekwak
 */

#include "Tank.h"
#include <WPILib.h>

const int CLOSE_STATE = 0;
const int OPEN_STATE = 1;
int tank_state = CLOSE_STATE;

Tank::Tank() {

	inputValve = new DoubleSolenoid(0, 0, 0);
	pressureSensor = new AnalogInput(0);

}

void Tank::Open() {

	inputValve->Set(DoubleSolenoid::Value::kForward);

}

void Tank::Close() {

	inputValve->Set(DoubleSolenoid::Value::kReverse);

}

void Tank::TankStateMachine() {

	switch(tank_state) {

	case CLOSE_STATE:
		Close();
		break;

	case OPEN_STATE:
		Open();
		break;

	}

}



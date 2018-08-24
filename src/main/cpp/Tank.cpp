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

	inputValve = new Solenoid(39, 3);
	pressureSensor = new AnalogInput(0); //not used

}

void Tank::Open() {

	inputValve->Set(true);

}

void Tank::Close() {

	inputValve->Set(false);

}

double Tank::GetPressureValue() {

	return pressureSensor->GetValue(); //GetVoltage()

}

void Tank::TankStateMachine() {

	switch(tank_state) {

	case CLOSE_STATE:
		Close();
	//	std::cout << "close" << std::endl;
		break;

	case OPEN_STATE:
		Open();
//		std::cout << "open" << std::endl;
		break;

	}

}

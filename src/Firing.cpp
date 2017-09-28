/*
 * Firing.cpp
 *
 *  Created on: May 22, 2017
 *      Author: gracekwak
 */

#include <Firing.h>

const int CLOSE_ALL_STATE = 0;
const int OPEN_FIRE_STATE = 1;
const int OPEN_EMERGENCY_STATE = 2;
const int OPEN_ALL_STATE = 3;
int fire_state = CLOSE_ALL_STATE;

Firing::Firing() {

	outputValve = new Solenoid(4, 4);
	emergencyRelease = new Solenoid(4, 5);

}

void Firing::Close() {

	outputValve->Set(false);

}

void Firing::Fire() {

	outputValve->Set(true);

}

void Firing::OpenEmergency() {

	emergencyRelease->Set(true);

}

void Firing::CloseEmergency() {

	emergencyRelease->Set(false);

}

void Firing::FiringStateMachine() {

	switch(fire_state) {

	case CLOSE_ALL_STATE:
		Close();
		CloseEmergency();
		break;

	case OPEN_FIRE_STATE:
		Fire();
		CloseEmergency();
		break;

	case OPEN_EMERGENCY_STATE:
		Close();
		OpenEmergency();
		break;

	case OPEN_ALL_STATE: //just in case
		Fire();
		OpenEmergency();
		break;
	}

}



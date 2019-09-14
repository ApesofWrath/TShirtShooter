/*
 * Firing.cpp
 *
 *  Created on: May 22, 2017
 *      Author: gracekwak
 */

#include "Firing.h" //needs "", not <>

const int CLOSE_STATE = 0;
const int OPEN_STATE = 1;
int fire_state = CLOSE_STATE;

Firing::Firing() {

	outputValve = new frc::Solenoid(0, 2);

}

void Firing::Close() {

	outputValve->Set(false);

}

void Firing::Open() {

	outputValve->Set(true);

}

void Firing::FiringStateMachine() {

	switch(fire_state) {

	case CLOSE_STATE:
		Close();
		break;

	case OPEN_STATE:
		Open();
		break;
	}

}

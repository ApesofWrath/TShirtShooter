/*
 * Firing.cpp
 *
 *  Created on: May 22, 2017
 *      Author: gracekwak
 */

#include <Firing.h>

const int CLOSE_STATE = 0;
const int OPEN_STATE = 1;
int fire_state = CLOSE_STATE;

Firing::Firing() {

	outputValve = new Solenoid(39, 4);

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



/*
 * Firing.cpp
 *
 *  Created on: May 22, 2017
 *      Author: gracekwak
 */

#include <Firing.h>

const int CLOSE_STATE = 0;
const int FIRE_STATE = 1;
int barrel_fire_state = CLOSE_STATE;

Firing::Firing() {

	outputValve = new Solenoid(4, 2);

}

void Firing::Close() {

	outputValve->Set(false);

}

void Firing::Fire() {

	outputValve->Set(true);

}

void Firing::FiringStateMachine() {

	switch(barrel_fire_state) {

	case CLOSE_STATE:
		Close();
		break;

	case FIRE_STATE:
		Fire();
		break;
	}

}



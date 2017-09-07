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

	outputValve = new DoubleSolenoid(0, 0, 0);

}

void Firing::Close() {

	outputValve->Set(DoubleSolenoid::Value::kReverse);

}

void Firing::Fire() {

	outputValve->Set(DoubleSolenoid::Value::kForward);

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



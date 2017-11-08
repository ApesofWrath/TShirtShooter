/*
 * TeleopStateMachine.cpp
 *
 *  Created on: May 17, 2017
 *      Author: gracekwak
 */

#include "TeleopStateMachine.h"
#define PI 3.14159

const int PRESSURE_THRESHOLD = 10; //check this value
const int FIRING_TIME = 3; //seconds

const int INIT_STATE = 0;
const int WAIT_FOR_BUTTON_STATE = 1;
const int INPUT_VALVE_STATE = 2;
const int UP_STATE = 3;
const int OUTPUT_VALVE_STATE = 4;
const int EMERGENCY_STATE = 5;
int state = INIT_STATE;

Timer *timer = new Timer();

TeleopStateMachine::TeleopStateMachine(Barrel *barrelP, Tank *tankP, Firing *firingP, ReleaseValve *releaseP) {

	barrel_ = barrelP;
	tank_ = tankP;
	firing_ = firingP;
	release_ = releaseP;

}
void TeleopStateMachine::StateMachine(bool fire_button) {

	switch(state){

	case INIT_STATE:
		state = WAIT_FOR_BUTTON_STATE;
		break;

	case WAIT_FOR_BUTTON_STATE:
		if (fire_button) {
			state = INPUT_VALVE_STATE;
		}
		break;

	case INPUT_VALVE_STATE:
		timer->Start();
		tank_->tank_state = tank_->OPEN_STATE_H;

		if (timer->HasPeriodPassed(5)){
			tank_->tank_state = tank_->CLOSE_STATE_H;
			state = UP_STATE;
		}
		break;

	case UP_STATE:
		barrel_->barrel_state = barrel_->UP_STATE_H;
		state = OUTPUT_VALVE_STATE;
		break;

	case OUTPUT_VALVE_STATE:
		timer->Start();
		firing_->fire_state = firing_->OPEN_STATE_H;
		if(timer->HasPeriodPassed(1.5)){
			firing_->fire_state = firing_->CLOSE_STATE_H;
			state = WAIT_FOR_BUTTON_STATE;
		}
		break;

	case EMERGENCY_STATE:
		release_->release_state = release_->OPEN_STATE_H;
		break;

	}

}

void TeleopStateMachine::Initialize() {
	state = INIT_STATE;
}

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
int state = INIT_STATE;

Timer *firingTimer = new Timer();

TeleopStateMachine::TeleopStateMachine(Barrel *barrelP, Tank *tankP, Firing *firingP) {

	barrel_ = barrelP;
	tank_ = tankP;
	firing_ = firingP;

}

void TeleopStateMachine::StateMachine(bool shoot_button, bool input_valve_button, bool close_tank_button, bool up_button, bool down_button) {

	switch(state){

	if(up_button) {
		barrel_->barrel_pos_state = barrel_->UP_STATE_H;
	}
	else if(down_button) {
		barrel_->barrel_pos_state = barrel_->DOWN_STATE_H;
	}

	case INIT_STATE:
		barrel_->barrel_pos_state = barrel_->ZERO_STATE_H;
		state = WAIT_FOR_BUTTON_STATE;
		break;

	case WAIT_FOR_BUTTON_STATE:
		tank_->tank_state = tank_->CLOSE_STATE_H;
		firing_->barrel_fire_state = firing_->CLOSE_STATE_H;
		if(input_valve_button) {
		state = INPUT_VALVE_STATE;
		}
		break;

	case INPUT_VALVE_STATE:
		tank_->tank_state = tank_->OPEN_STATE_H;
		if(tank_->GetPressureValue() >= tank_->MAX_TANK_PRESSURE || close_tank_button) {
		tank_->tank_state = tank_->CLOSE_STATE_H;
		state = UP_STATE;
		}
		std::cout << "TANK: " << tank_->GetPressureValue() << std::endl;
		break;

	case UP_STATE:
		if(shoot_button) {
			state = OUTPUT_VALVE_STATE;
		}
		break;

	case OUTPUT_VALVE_STATE:
		firing_->barrel_fire_state = firing_->FIRE_STATE_H;
		firingTimer->Start();
		if(firingTimer->HasPeriodPassed(FIRING_TIME)) {
			firingTimer->Reset();
			state = WAIT_FOR_BUTTON_STATE;
		}
		break;

	}

}

void TeleopStateMachine::Initialize() {
	state = INIT_STATE;
}

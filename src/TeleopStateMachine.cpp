/*
 * TeleopStateMachine.cpp
 *
 *  Created on: May 17, 2017
 *      Author: gracekwak
 */

#include "TeleopStateMachine.h"
#define PI 3.14159

const int PRESSURE_THRESHOLD = 10; //check this value
const int FIRING_TIME = 2; //seconds

const int INIT_STATE = 0;
const int WAIT_FOR_BUTTON_STATE = 1;
const int INPUT_VALVE_STATE = 2;
const int SIXTY_STATE = 3;
const int SEVENTY_STATE = 4;
const int EIGHTY_STATE = 5;
const int OUTPUT_VALVE_STATE = 6;
int state = INIT_STATE;

bool sixty_chosen = false; //stores button value for input valve state
bool seventy_chosen = false;
bool eighty_chosen = false;

Barrel * barrel_;
Tank * tank_;
Firing * firing_;

Timer *firingTimer = new Timer();

TeleopStateMachine::TeleopStateMachine(Barrel *barrelP, Tank *tankP, Firing *firingP) {

	barrel_ = barrelP;
	tank_ = tankP;
	firing_ = firingP;

}

void TeleopStateMachine::StateMachine(bool shoot, bool sixty, bool seventy, bool eighty) {

	switch(state){

	case INIT_STATE:
		barrel_->barrel_pos_state = barrel_->ZERO_STATE_H;
		state = WAIT_FOR_BUTTON_STATE;

		break;

	case WAIT_FOR_BUTTON_STATE:
		barrel_->barrel_pos_state = barrel_->DOWN_STATE_H;
		tank_->tank_state = tank_->CLOSE_STATE_H;
		firing_->barrel_fire_state = firing_->CLOSE_STATE_H;
		if(sixty) {
			sixty_chosen = true;
			state = INPUT_VALVE_STATE;
		}
		if(seventy) {
			seventy_chosen = true;
			state = INPUT_VALVE_STATE;
		}
		if(eighty) {
			eighty_chosen = true;
			state = INPUT_VALVE_STATE;
		}
		break;

	case INPUT_VALVE_STATE:
		tank_->tank_state = tank_->OPEN_STATE_H;
		if(tank_->pressureSensor->GetValue() >= PRESSURE_THRESHOLD) {
			tank_->tank_state = tank_->CLOSE_STATE_H;
			if(sixty_chosen) {
				sixty_chosen = false;
				state = SIXTY_STATE;
			}
			else if (seventy_chosen) {
				seventy_chosen = false;
				state = SEVENTY_STATE;
			}
			else if (eighty_chosen) {
				eighty_chosen = false; //
				state = EIGHTY_STATE;
			}
		}
		break;

	case SIXTY_STATE:
		barrel_->barrel_pos_state = barrel_->SIXTY_STATE_H;
		if(shoot && barrel_->IsAtPosition()) {
			state = OUTPUT_VALVE_STATE;
		}
		break;

	case SEVENTY_STATE:
		barrel_->barrel_pos_state = barrel_->SEVENTY_STATE_H;
		if(shoot && barrel_->IsAtPosition()) {
			state = OUTPUT_VALVE_STATE;
		}
		break;

	case EIGHTY_STATE:
		barrel_->barrel_pos_state = barrel_->EIGHTY_STATE_H;
		if(shoot && barrel_->IsAtPosition()) {
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

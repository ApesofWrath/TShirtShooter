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
	canTalonCompressor1 = new TalonSRX(CAN_TALON_COMPRESSOR_1);
	canTalonCompressor2 = new TalonSRX(CAN_TALON_COMPRESSOR_2);
	canTalonCompressor2->Follow(*canTalonCompressor1);
}

void Firing::Close() {

	outputValve->Set(false);

}

void Firing::Open() {

	outputValve->Set(true);

}

void Firing::StartCompressor() {

	canTalonCompressor1->Set(ControlMode::PercentOutput,1.0f);

}

void Firing::StopCompressor() {

	canTalonCompressor1->Set(ControlMode::PercentOutput,0.0f);

}

void Firing::FiringStateMachine() {

	switch(fire_state) {

	case CLOSE_STATE:
		Close();
		break;

	case OPEN_STATE:
		Open();
		break;
	
	case START_COMPRESSOR_STATE:
		StartCompressor();
		break;

	case STOP_COMPRESSOR_STATE:
		StopCompressor();
		break;
	}

}

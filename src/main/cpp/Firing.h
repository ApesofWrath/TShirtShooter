/*
 * Firing.h
 *
 *  Created on: May 22, 2017
 *      Author: gracekwak
 */
#include <frc/WPILib.h>
#include "ctre/Phoenix.h"

#ifndef SRC_FIRING_H_
#define SRC_FIRING_H_

#define START_COMPRESSOR_STATE 2
#define STOP_COMPRESSOR_STATE 3

class Firing {
public:

	Firing();
	void FiringStateMachine();
	void Close();
	void Open();
	void StartCompressor();
	void StopCompressor();

	frc::Solenoid *outputValve;
	TalonSRX *canTalonCompressor1, *canTalonCompressor2;

	const int CLOSE_STATE_H = 0;
	const int OPEN_STATE_H = 1;

	int fire_state = CLOSE_STATE_H;

	const int CAN_TALON_COMPRESSOR_1 = 1;
	const int CAN_TALON_COMPRESSOR_2 = 11;

};

#endif

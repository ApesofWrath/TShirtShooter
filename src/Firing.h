/*
 * Firing.h
 *
 *  Created on: May 22, 2017
 *      Author: gracekwak
 */
#include <WPILib.h>
#ifndef SRC_FIRING_H_
#define SRC_FIRING_H_

class Firing {
public:

	Firing();
	void FiringStateMachine();
	void Close();
	void Open();

	Solenoid *outputValve;

	const int CLOSE_STATE_H = 0;
	const int OPEN_STATE_H = 1;
	int fire_state = CLOSE_STATE_H;

};

#endif

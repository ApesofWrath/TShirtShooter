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
	void Fire();

	Solenoid *outputValve;

	const int CLOSE_STATE_H = 0;
	const int FIRE_STATE_H = 1;
	int barrel_fire_state = CLOSE_STATE_H;

};

#endif /* SRC_FIRING_H_ */

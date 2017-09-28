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
	void OpenEmergency();
	void CloseEmergency();

	Solenoid *outputValve, *emergencyRelease;

	const int CLOSE_ALL_STATE_H = 0;
	const int OPEN_FIRE_STATE_H = 1;
	const int OPEN_EMERGENCY_STATE_H = 2;
	const int OPEN_ALL_STATE_H = 3;
	int fire_state = CLOSE_ALL_STATE_H;

};

#endif /* SRC_FIRING_H_ */

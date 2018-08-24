/*
 * ReleaseValve.h
 *
 *  Created on: Oct 25, 2017
 *      Author: DriversStation
 */
#include <WPILib.h>
#ifndef SRC_RELEASEVALVE_H_
#define SRC_RELEASEVALVE_H_

class ReleaseValve {
public:

	ReleaseValve();
	void Close();
	void Open();

	void ReleaseValveStateMachine();

	Solenoid *releaseValve;

	const int CLOSE_STATE_H = 0;
	const int OPEN_STATE_H = 1;
	int release_state = CLOSE_STATE_H;

};

#endif

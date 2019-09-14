/*
 * ReleaseValve.cpp
 *
 *  Created on: Oct 25, 2017
 *      Author: DriversStation
 */

#include "ReleaseValve.h"
#include <frc/WPILib.h>

const int CLOSE_STATE = 0;
const int OPEN_STATE = 1;
int release_state = CLOSE_STATE;

ReleaseValve::ReleaseValve() {

	releaseValve = new frc::Solenoid(0, 3);

}

void ReleaseValve::Open() {

	releaseValve->Set(true);

}

void ReleaseValve::Close() {

	releaseValve->Set(false);

}

void ReleaseValve::ReleaseValveStateMachine() {

	switch(release_state) {

	case CLOSE_STATE:
		Close();
		break;

	case OPEN_STATE:
		Open();
		break;

	}

}

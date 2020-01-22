/*
 * DriveController.h
 *
 *  Created on: May 15, 2017
 *      Author: gracekwak
 */

#include <AHRS.h>
#include <frc/WPILib.h>
#include "ctre/Phoenix.h"

#ifndef DRIVECONTROLLER_H_
#define DRIVECONTROLLER_H_

class DriveController {
public:


	TalonSRX *canTalonFrontLeft, *canTalonFrontRight, *canTalonBackLeft,
				*canTalonBackRight;
	AHRS *ahrs;

	DriveController();
	void Drive(Joystick *joyThrottle, Joystick *joyWheel);
	void DriveTest(Joystick *joyThrottle, Joystick *joyWheel);

};

#endif /* DRIVECONTROLLER_H_ */

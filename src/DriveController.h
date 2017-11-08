/*
 * DriveController.h
 *
 *  Created on: May 15, 2017
 *      Author: gracekwak
 */
#include <WPILib.h>
#include <CANTalon.h>
#include <AHRS.h>
#ifndef DRIVECONTROLLER_H_
#define DRIVECONTROLLER_H_

class DriveController {
public:


	CANTalon *canTalonFrontLeft, *canTalonFrontRight, *canTalonBackLeft,
				*canTalonBackRight;
	AHRS *ahrs;

	DriveController();
	void Drive(Joystick *joyThrottle, Joystick *joyWheel);
	void DriveTest(Joystick *joyThrottle, Joystick *joyWheel);

};

#endif /* DRIVECONTROLLER_H_ */

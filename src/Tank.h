/*
 * Tank.h
 *
 *  Created on: May 17, 2017
 *      Author: gracekwak
 */
#include <WPILib.h>
#include <CANTalon.h>

#ifndef TANK_H_
#define TANK_H_

class Tank {
public:

	DoubleSolenoid *inputValve;
	AnalogInput *pressureSensor;
	Tank();
	void Open();
	void Close();
	void TankStateMachine();

	const int CLOSE_STATE_H = 0;
	const int OPEN_STATE_H = 1;
	int tank_state = CLOSE_STATE_H;


};

#endif /* TANK_H_ */

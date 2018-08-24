/*
 * Tank.h
 *
 *  Created on: May 17, 2017
 *      Author: gracekwak
 */
#include <WPILib.h>

#ifndef TANK_H_
#define TANK_H_

class Tank {
public:

	Solenoid *inputValve;
	AnalogInput *pressureSensor;
	Tank();
	void Open();
	void Close();
	double GetPressureValue();
	void TankStateMachine();

	const int CLOSE_STATE_H = 0;
	const int OPEN_STATE_H = 1;
	int tank_state = CLOSE_STATE_H;

	const int MAX_TANK_PRESSURE = 55; //check this


};

#endif /* TANK_H_ */

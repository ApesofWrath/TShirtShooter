/*
 * Barrel.h
 *
 *  Created on: May 16, 2017
 *      Author: gracekwak
 */
#include <WPILib.h>
#include <CANTalon.h>
//#include <TrapezoidalProfile.h>
#ifndef BARREL_H_
#define BARREL_H_

class Barrel {
public:

	CANTalon *canTalonBarrel;

	Barrel();
	void MoveTo(double ref);
	void BarrelStateMachine();
	bool IsAtPosition(double ref);
	double GetBarrelPos();

	void StartThread();
	void DisableThread();
	void MoveWrapper(Barrel *barrel, int *ref_pos);
	void SetIndex(int index);

	const int ZERO_STATE_H = 0;
	const int DOWN_STATE_H = 1;
	const int UP_STATE_H = 2;
	const int STOP_STATE_H = 3;
	int barrel_pos_state = ZERO_STATE_H; //init state

};

#endif /* BARREL_H_ */

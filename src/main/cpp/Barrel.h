/*
 * Barrel.h
 *
 *  Created on: May 16, 2017
 *      Author: gracekwak
 */
#include <WPILib.h>
#include "ctre/Phoenix.h"
#include <thread>
#include <chrono>
#include <Timer.h>
#ifndef BARREL_H_
#define BARREL_H_

class Barrel {
public:

	TalonSRX *canTalonBarrel;

	Barrel();
	void MoveTo(double ref);
	void BarrelStateMachine();
	bool IsAtPosition(double ref);
	double GetBarrelPos();

	void StartThread();
	void DisableThread();
	static void BarrelWrapper(Barrel *barrel, double *ref, bool *active);

	const int ZERO_STATE_H = 0;
	const int DOWN_STATE_H = 1;
	const int UP_STATE_H = 2;
	const int STOP_STATE_H = 3;
	int barrel_state = ZERO_STATE_H;

};

#endif /* BARREL_H_ */

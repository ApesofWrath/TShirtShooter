/*
 * Barrel.h
 *
 *  Created on: May 16, 2017
 *      Author: gracekwak
 */
#include <WPILib.h>
#include <CANTalon.h>
#ifndef BARREL_H_
#define BARREL_H_

class Barrel {
public:

	CANTalon *canTalonBarrel;

	Barrel();
	void MoveTo(double ref);
	void BarrelStateMachine();
	bool IsAtPosition();

	const int ZERO_STATE_H = 0;
	const int DOWN_STATE_H = 1;
	const int SIXTY_STATE_H = 2;
	const int SEVENTY_STATE_H = 3;
	const int EIGHTY_STATE_H = 4;
	int barrel_pos_state = ZERO_STATE_H;

};

#endif /* BARREL_H_ */

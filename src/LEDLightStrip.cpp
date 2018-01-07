/*
 * LEDLightStrip.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: DriversStation
 */

#include <LEDLightStrip.h>

int led_state = 0;
const int RED_STATE = 0;
const int BLINKING_STATE = 1;

Timer *timerLED = new Timer;

LEDLightStrip::LEDLightStrip() {
	light = new CANLight(2);
}

void LEDLightStrip::Red() {
	light->ShowRGB(255, 0, 0);

}

void LEDLightStrip::Blue() {
	light->ShowRGB(0, 0, 255);

}

void LEDLightStrip::White() {
	light->ShowRGB(255, 255, 255);
}

void LEDLightStrip::LEDLightStrip::LEDLightStripStateMachine() {

	switch (led_state) {

	case RED_STATE:
		Red();
		std::cout << "Red" << std::endl;
		break;

	case BLINKING_STATE:
//		//timerLED->Start();
//		Red();
//
////		if (timerLED->HasPeriodPassed(.5)) {
////			Blue();
////			timerLED->Reset();
////		}
		//  timerLED->Start();
////
////		if (timerLED->HasPeriodPassed(.5)) {
				White();
////			timerLED->Reset();
////		}
		break;
	}
}


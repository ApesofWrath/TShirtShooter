/*
 * LEDLightStrip.h
 *
 *  Created on: Nov 8, 2017
 *      Author: DriversStation
 */

#ifndef SRC_LEDLIGHTSTRIP_H_
#define SRC_LEDLIGHTSTRIP_H_
#include <WPILib.h>
#include <CANTalon.h>
#include <mindsensors.h>

using mindsensors::CANLight;

class LEDLightStrip {
public:

	LEDLightStrip();

	void Red();
	void Blue();
	void White();
	void LEDLightStripStateMachine();

	CANLight *light;

	int led_state = 0;
	const int RED_STATE_H = 0;
	const int BLINKING_STATE_H = 1;
};

#endif
/*
bool shoot_button = joyOp->GetRawButton(SHOOT_BUTTON);
bool input_valve_button = joyOp->GetRawButton(INPUT_VALVE_BUTTON);
bool up_button = joyOp->GetRawButton(UP_BUTTON);
bool down_button = joyOp->GetRawButton(DOWN_BUTTON);
bool emergency_button = joyOp->GetRawButton(EMERGENCY_BUTTON);
bool fire_button = joyOp->GetRawButton(FIRE_BUTTON);
bool slow_button = joyOp->GetRawButton(SLOW_BUTTON);
bool led_button = joyOp->GetRawButton(LED_BUTTON);

//	teleop_state_machine->StateMachine(fire_button);
tank_->TankStateMachine();
barrel_->BarrelStateMachine();
firing_->FiringStateMachine();
release_->ReleaseValveStateMachine();
light_strip->LEDLightStripStateMachine();

drive_controller->Drive(joyThrottle, joyWheel);

if (led_button) { //6
//	light_strip->led_state = light_strip->BLINKING_STATE_H;
}

if (up_button) { //3
	barrel_->barrel_state = barrel_->UP_STATE_H;
} else if (down_button) { //4
	barrel_->barrel_state = barrel_->DOWN_STATE_H;
} else {
	barrel_->barrel_state = barrel_->STOP_STATE_H;
}

if (shoot_button) { //1
	firing_->fire_state = firing_->OPEN_STATE_H;
} else {
	firing_->fire_state = firing_->CLOSE_STATE_H;
}

if (emergency_button) { //10
	release_->release_state = release_->OPEN_STATE_H;
} else {
	release_->release_state = release_->CLOSE_STATE_H;
}

if (input_valve_button) { //11
	tank_->tank_state = tank_->OPEN_STATE_H;
} else {
	tank_->tank_state = tank_->CLOSE_STATE_H;
} */

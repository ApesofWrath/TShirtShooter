#include <iostream>
#include <memory>
#include <string>

#include <frc/TimedRobot.h>
#include <frc/WPILib.h>
#include "ctre/Phoenix.h"
#include <frc/Joystick.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "DriveController.h"
#include "Barrel.h"
#include "TeleopStateMachine.h"
#include "ReleaseValve.h"
#include "Firing.h"
#include "Tank.h"


#define PI 3.14159265

class Robot: public frc::TimedRobot {

	const int UP_BUTTON = 4;
	const int DOWN_BUTTON = 2;
	const int INPUT_VALVE_BUTTON = 11;
	//const int CLOSE_TANK_BUTTON = 10;
	const int EMERGENCY_BUTTON = 10;
	const int FIRE_BUTTON = 8;
	//const int RETURN_BUTTON = 3;
	const int START_COMPRESSOR_BUTTON = 5;
	const int STOP_COMPRESSOR_BUTTON = 6;
	const int SLOW_BUTTON = 2;
	//const int LED_BUTTON = 6;
	const int FORWARD_BUTTON = 7; //?
	const int STOP_BUTTON = 8;

	const int JOY_THROTTLE = 0;
	const int JOY_OP = 1;
	const int JOY_WHEEL = 2;

	Firing *firing_;
	Joystick *joyOp, *joyThrottle, *joyWheel;
	Tank *tank_;
	Barrel *barrel_;
	ReleaseValve *release_;
	TeleopStateMachine *teleop_state_machine;
	DriveController *drive_controller;

	void RobotInit() {

		joyThrottle = new Joystick(2);
		joyOp = new Joystick(0);
		joyWheel = new Joystick(1);

		tank_ = new Tank();
		barrel_ = new Barrel();
		firing_ = new Firing();
		release_ = new ReleaseValve();
		drive_controller = new DriveController();
		teleop_state_machine = new TeleopStateMachine(barrel_, tank_, firing_, release_);

	}

	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() { //does not run again on re-enable

	}

	void TeleopPeriodic() { //20ms

		bool up_button = joyOp->GetRawButton(UP_BUTTON); //TODO: change for arcade buttons
		bool down_button = joyOp->GetRawButton(DOWN_BUTTON);
		bool input_valve_button = joyOp->GetRawButton(INPUT_VALVE_BUTTON);
		bool emergency_button = joyOp->GetRawButton(EMERGENCY_BUTTON);
		bool fire_button = joyOp->GetRawButton(FIRE_BUTTON);
		bool slow_button= joyOp->GetRawButton(SLOW_BUTTON);
		bool forward_button = joyOp->GetRawButton(FORWARD_BUTTON);
		bool stop_button = joyOp->GetRawButton(STOP_BUTTON);
		bool start_compressor_button = joyOp->GetRawButton(START_COMPRESSOR_BUTTON);
		bool stop_compressor_button = joyOp->GetRawButton(STOP_COMPRESSOR_BUTTON);

		drive_controller->Drive(joyOp); 
		tank_->TankStateMachine();
		barrel_->BarrelStateMachine();
		firing_->FiringStateMachine();
		release_->ReleaseValveStateMachine();

		if(fire_button){
			firing_->fire_state = firing_->OPEN_STATE_H;
		} else {
			firing_->fire_state = firing_->CLOSE_STATE_H;
		}

		if(stop_compressor_button){
			firing_->fire_state = STOP_COMPRESSOR_STATE;
		} else if(start_compressor_button){
			firing_->fire_state = START_COMPRESSOR_STATE;
		}


		frc::SmartDashboard::PutBoolean("up_button = ", up_button);
		frc::SmartDashboard::PutBoolean("down_button = ", down_button);
		if(up_button) {
			barrel_->barrel_state = barrel_->UP_STATE_H;
		} else if(down_button) {
			barrel_->barrel_state = barrel_->DOWN_STATE_H;
		} else {
			barrel_->barrel_state = barrel_->STOP_STATE_H;
		}

		if(input_valve_button) {
			tank_->tank_state = tank_->OPEN_STATE_H;
		} else {
			tank_->tank_state = tank_->CLOSE_STATE_H;
		}


		if(emergency_button) {
			release_->release_state = release_->OPEN_STATE_H;
		} else {
		  release_->release_state = release_->CLOSE_STATE_H;
		}

	}

	void TestPeriodic() {

	/*	drive_controller->Drive(joyThrottle, joyWheel);

		if (joyOp->GetRawButton(3)) { //up
			barrel_->canTalonBarrel->Set(0.6);
		} else if (joyOp->GetRawButton(4)) { //down
			barrel_->canTalonBarrel->Set(-0.6);
		} else {
			barrel_->canTalonBarrel->Set(0.0);
		}

		//	tank_->inputValve->Set(true);

//		if (joyOp->GetRawButton(8)) {
//			firing_->outputValve->Set(true);
//		} else {
//			firing_->outputValve->Set(false);
//		}

		if (joyOp->GetRawButton(12)) {
			firing_->emergencyRelease->Set(true);
		} else {
			firing_->emergencyRelease->Set(false);
		}
//
		if (joyOp->GetRawButton(1)) {
			//	std::cout << "HERE" << std::endl;
			tank_->inputValve->Set(true);
		} else {
			tank_->inputValve->Set(false);
		}
		//tank_->emergencyRelease->Set(false);

		//if(joyOp->GetRawButton(3)) {
		//			tank_->inputValve(false);
		//		}
		//		else if (joyOp->GetRawButton(4)) {
		//			tank_->inputValve(true);
		//		}



		//if(joyOp->GetRawButton(3)) {
		//			firing_->outputValve(false);
		//		}
		//		else if (joyOp->GetRawButton(4)) {
		//			firing_->outputValve(true);
		//		}*/

	}

	void DisabledInit() {


	}


private:

};

START_ROBOT_CLASS(Robot)

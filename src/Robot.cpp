#include <iostream>
#include <memory>
#include <string>
#include <IterativeRobot.h>
#include <WPILib.h>
#include <CANTalon.h>
#include <Barrel.h>
#include <Tank.h>
#include <Firing.h>
#include <Joystick.h>
#include <DriveController.h>
#include <TeleopStateMachine.h>

#define PI 3.14159265

class Robot: public frc::IterativeRobot {

	const int SHOOT_BUTTON = 1;
	const int UP_BUTTON = 3;
	const int DOWN_BUTTON = 4;
	const int INPUT_VALVE_BUTTON = 9;
	const int CLOSE_TANK_BUTTON = 10;
	const int EMERGENCY_BUTTON = 8;
	const int RETURN_BUTTON = 3;

	const int JOY_THROTTLE = 0;
	const int JOY_OP = 1;
	const int JOY_WHEEL = 2;

	Firing *firing_;
	Joystick *joyOp, *joyThrottle, *joyWheel;
	Tank *tank_;
	Barrel *barrel_;
	TeleopStateMachine *teleop_state_machine;
	DriveController *drive_controller;

//	Solenoid *solenoid_1, *solenoid_2;

//int first = 0;

	void RobotInit() {

		joyThrottle = new Joystick(JOY_THROTTLE);
		joyOp = new Joystick(JOY_OP);
		joyWheel = new Joystick(JOY_WHEEL);

		tank_ = new Tank();
		barrel_ = new Barrel();
		firing_ = new Firing();
		drive_controller = new DriveController();
		teleop_state_machine = new TeleopStateMachine(barrel_, tank_, firing_);

//		solenoid_1 = new Solenoid(4, 0);
//		solenoid_2 = new Solenoid(4, 1);

	}

	void TeleopInit() { //does not run again on re-enable

		teleop_state_machine->Initialize();
	}

	void TeleopPeriodic() {

		bool shoot_button = joyOp->GetRawButton(SHOOT_BUTTON);
		bool input_valve_button = joyOp->GetRawButton(INPUT_VALVE_BUTTON);
		bool up_button = joyOp->GetRawButton(UP_BUTTON);
		bool down_button = joyOp->GetRawButton(DOWN_BUTTON);
//		bool close_tank_button = joyOp->GetRawButton(CLOSE_TANK_BUTTON);
		bool emergency_button = joyOp->GetRawButton(EMERGENCY_BUTTON);
//		bool return_button = joyOp->GetRawButton(RETURN_BUTTON);
//
//		teleop_state_machine->StateMachine(shoot_button, input_valve_button, close_tank_button, up_button, down_button, emergency_button, return_button);
		tank_->TankStateMachine();
    	barrel_->BarrelStateMachine();
		firing_->FiringStateMachine();

		drive_controller->Drive(joyThrottle, joyWheel);

		if (up_button) { //3
			barrel_->barrel_state = barrel_->UP_STATE_H;
		} else if (down_button) { //4
			barrel_->barrel_state = barrel_->DOWN_STATE_H;
		} else {
			barrel_->barrel_state = barrel_->STOP_STATE_H;
		}

		if (shoot_button) { //1
			firing_->fire_state = firing_->OPEN_FIRE_STATE_H;
		} else {
			firing_->fire_state = firing_->CLOSE_ALL_STATE_H;
		}

		if (emergency_button) {//8
			firing_->fire_state = firing_->OPEN_EMERGENCY_STATE_H;
		} else {
			firing_->fire_state = firing_->CLOSE_ALL_STATE_H;
		}

		if (input_valve_button) { //9
			tank_->tank_state = tank_->OPEN_STATE_H;
		} else {
			tank_->tank_state = tank_->CLOSE_STATE_H;
		}

	}

	void TestPeriodic() {

//		if(first) {
//			barrel_->canTalonBarrel->SetEncPosition(0);
//			first++;
//		}
//	//	std::cout << "BARREL: " << barrel_->GetBarrelPos() << std::endl; //did not print
//
		drive_controller->Drive(joyThrottle, joyWheel);

		if (joyOp->GetRawButton(3)) { //up
			barrel_->canTalonBarrel->Set(0.6);
		} else if (joyOp->GetRawButton(4)) { //down
			barrel_->canTalonBarrel->Set(-0.6);
		} else {
			barrel_->canTalonBarrel->Set(0.0);
		}

		//	tank_->inputValve->Set(true);

		if (joyOp->GetRawButton(8)) {
			firing_->outputValve->Set(true);
		} else {
			firing_->outputValve->Set(false);
		}

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
		//		}

	}

	void DisabledInit() {

		teleop_state_machine->Initialize();

	}

};

START_ROBOT_CLASS(Robot)

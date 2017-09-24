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
	const int UP_BUTTON = 6;

	const int JOY_THROTTLE = 0;
	const int JOY_OP = 1;
	const int JOY_WHEEL = 2;

	Firing *firing_;
	Joystick *joyOp, *joyThrottle, *joyWheel;
	Tank *tank_;
    Barrel *barrel_;
	TeleopStateMachine *teleop_state_machine;
	DriveController *drive_controller;

	Solenoid *solenoid_1, *solenoid_2;

	int first = 0;

	void RobotInit() {

		joyThrottle = new Joystick(JOY_THROTTLE);
		joyOp = new Joystick(JOY_OP);
		joyWheel = new Joystick(JOY_WHEEL);

		tank_ = new Tank();
		barrel_ = new Barrel();
		firing_ = new Firing();
		drive_controller = new DriveController();
		teleop_state_machine = new TeleopStateMachine(barrel_, tank_, firing_);

		solenoid_1 = new Solenoid(4, 0);
		solenoid_2 = new Solenoid(4, 1);

	}

	void TeleopInit() { //does not run again on re-enable

		teleop_state_machine->Initialize();
	}

	void TeleopPeriodic() {

		bool shoot_button = joyOp->GetRawButton(SHOOT_BUTTON);
		bool up_button = joyOp->GetRawButton(UP_BUTTON);

		teleop_state_machine->StateMachine(shoot_button, up_button);
		tank_->TankStateMachine();
    	barrel_->BarrelStateMachine();
		firing_->FiringStateMachine();
		drive_controller->Drive(joyThrottle, joyWheel);

	}

	void TestPeriodic() {

		if(first) {
			barrel_->canTalonBarrel->SetEncPosition(0);
			first++;
		}
		std::cout << "BARREL: " << barrel_->GetBarrelPos() << std::endl; //did not print

		if(joyOp->GetRawButton(3)) {
			barrel_->canTalonBarrel->Set(0.6);
		}
		else if (joyOp->GetRawButton(4)) {
			barrel_->canTalonBarrel->Set(-0.6);
		}
		else {
			barrel_->canTalonBarrel->Set(0.0);
		}

		if(joyOp->GetRawButton(8)) {
			firing_->outputValve->Set(false);
		}
		else {
			firing_->outputValve->Set(true);
		}

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

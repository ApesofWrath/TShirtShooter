#include <iostream>
#include <memory>
#include <string>
#include <IterativeRobot.h>
#include <WPILib.h>
#include <Joystick.h>
#include <CANTalon.h>
#include <Barrel.h>
#include <Tank.h>
#include <Firing.h>
#include <DriveController.h>
#include <TeleopStateMachine.h>

#define PI 3.14159265

class Robot: public frc::IterativeRobot {

	const int SHOOT_BUTTON = 1;
	const int SIXTY_BUTTON = 6;
	const int SEVENTY_BUTTON = 7;
	const int EIGHTY_BUTTON = 8;

	const int JOY_OP = 0;

	Firing *firing_;
	Joystick *joyOp;
	Tank *tank_;
	Barrel *barrel_;
	TeleopStateMachine *teleop_state_machine;
	DriveController *drive_controller;

	Solenoid *solenoid_1, *solenoid_2;


	void RobotInit() {

		joyOp = new Joystick(JOY_OP);
		tank_ = new Tank();
		barrel_ = new Barrel();
		firing_ = new Firing();
		drive_controller = new DriveController();
		teleop_state_machine = new TeleopStateMachine(barrel_, tank_, firing_);

		solenoid_1 = new Solenoid(0, 0);
		solenoid_2 = new Solenoid(0, 1);

	}

	void TeleopInit() {

		teleop_state_machine->Initialize();
	}

	void TeleopPeriodic() {

		bool shoot_button = joyOp->GetRawButton(SHOOT_BUTTON);
		bool sixty_button = joyOp->GetRawButton(SIXTY_BUTTON);
		bool seventy_button = joyOp->GetRawButton(SEVENTY_BUTTON);
		bool eighty_button = joyOp->GetRawButton(EIGHTY_BUTTON);

		teleop_state_machine->StateMachine(shoot_button, sixty_button, seventy_button, eighty_button);
		tank_->TankStateMachine();
		barrel_->BarrelStateMachine();
		firing_->FiringStateMachine();
		drive_controller->Drive();

	}

	void TestPeriodic() {

		if(joyOp->GetRawButton(1)) {
			solenoid_1->Set(true);
		}
		else {
			solenoid_1->Set(false);
		}

		if(joyOp->GetRawButton(2)) {
				solenoid_2->Set(true);
			}
			else {
				solenoid_2->Set(false);
			}

	}

};

START_ROBOT_CLASS(Robot)

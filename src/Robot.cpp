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

	const int SHOOT_BUTTON = 0;
	const int SIXTY_BUTTON = 0;
	const int SEVENTY_BUTTON = 0;
	const int EIGHTY_BUTTON = 0;

	Firing *firing_;
	Joystick *joyOp;
	Tank *tank_;
	Barrel *barrel_;
	TeleopStateMachine *teleop_state_machine;
	DriveController *drive_controller;

	void RobotInit() {

		joyOp = new Joystick(0);
		tank_ = new Tank();
		barrel_ = new Barrel();
		firing_ = new Firing();
		drive_controller = new DriveController();
		teleop_state_machine = new TeleopStateMachine(barrel_, tank_, firing_);

	}

	void TeleopInit() {

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

};

START_ROBOT_CLASS(Robot)

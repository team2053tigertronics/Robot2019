/**
 * \file Robot.cpp
 * \brief The Main Class
 * \author Drew Williams
 */


#include "Robot.h"
#include <Commands/Scheduler.h>
#include "Commands/Drive/DriveToPosition.h"

std::unique_ptr<OI> Robot::oi;
std::unique_ptr<SwerveSubsystem> Robot::swerveSubsystem;

/**
 * \brief Robot Initialization
 *
 * This is the entry point for the robot program.
 * We have all of the main functions that control how
 * the robot behaves. Usually we init subsystems here and
 * also set up game specific auto routines.
 */
void Robot::RobotInit() {
	swerveSubsystem = std::make_unique<SwerveSubsystem>();
	oi = std::make_unique<OI>();
	driveToPos = new DriveToPosition();
}

/**
 * \brief Disabled Init
 *
 * This function runs once when you disable the robot.
 * Runs everytime you disable. Might want to use to
 * make sure everything shuts down correctly.
 */
void Robot::DisabledInit() {}

/**
 * \brief Disabled Periodic
 *
 * This function runs every 20ms while the robot is
 * disabled. Used to check for auto state changes
 * like the scale state in auto.
 *
 */
void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

/**
 * \brief Auto Init
 *
 * This function runs once when you first change to
 * autonomous mode. Used to get selected auto mode.
 */
void Robot::AutonomousInit() {
	driveToPos->Start();
}

/**
 * \brief Auto Periodic
 *
 * This function runs every 20ms while the robot is
 * in autonomous mode. Can be used to check path following
 * or if we are waiting for something in auto.
 */
void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

/**
 * \brief Teleop Init
 *
 * This function runs once when you enable the robot in teleop.
 * Runs everytime you enable
 */
void Robot::TeleopInit() {

}

/**
 * \brief Teleop Periodic
 *
 * This function runs every 20ms while teleop mode is active.
 * Can be used to check for different states like LED status or
 * smartdashboard updates. Make sure you dont overload this function
 * or you will lag the robot!
 */
void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

/**
 * \brief Test Periodic
 *
 * This function runs every 20ms while test mode is active.
 * Not used that much...
 */
void Robot::TestPeriodic() {

}

START_ROBOT_CLASS(Robot)
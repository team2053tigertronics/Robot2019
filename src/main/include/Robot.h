/**
 * \file Robot.h
 * \brief The Main Class
 * \author Drew Williams
 */

#pragma once

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "OI.h"
#include "Subsystems/DrivebaseSubsystem.h"
#include "Subsystems/IntakeSubsystem.h"
#include "Subsystems/LiftSubsystem.h"
#include "Subsystems/ObserverSubsystem.h"
#include "Subsystems/ElevatorSubsystem.h"
#include "Subsystems/VisionSubsystem.h"
#include "Utilities/TigerMecanum/PathManager.h"
#include <opencv2/core/core.hpp>
#include <cameraserver/CameraServer.h>
#include "RobotMap.h"
#include <string>

/**
 * This is the main class of the robot. Sort of like
 * a main.cpp file.
 */
class Robot : public frc::TimedRobot {
public:
	static std::unique_ptr<OI> oi;
	static std::unique_ptr<DrivebaseSubsystem> drivebaseSubsystem;
	static std::shared_ptr<ObserverSubsystem> observer;
	static std::unique_ptr<IntakeSubsystem> intakeSubsystem;
	static std::unique_ptr<LiftSubsystem> liftSubsystem;
	static std::unique_ptr<ElevatorSubsystem> elevatorSubsystem;
	static std::unique_ptr<VisionSubsystem> visionSubsystem;
	static std::unique_ptr<PathManager> pathManager;
	static std::unique_ptr<RobotMap> robotMap;

	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;
private:
	frc::SendableChooser<std::string> autoChooser;
	std::string selectedMode;
	frc::Command* pathAuto;
	frc::Command* driveCommand;
	bool overrideCmd;
};

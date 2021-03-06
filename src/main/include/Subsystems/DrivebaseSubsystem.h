/**
 * \file DrivebaseSubsystem.h
 * \brief This file holds all information regarding the drivebase
 * \author Drew Williams
 */

#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>
#include <rev/CANSparkMaxLowLevel.h>
#include "Utilities/TigerDrive/TigerDrive.h"
#include <frc/drive/MecanumDrive.h>
#include "Utilities/Math/Translation2D.h"
#include "Utilities/Math/Rotation2D.h"
#include "Utilities/Math/RigidTransform2D.h"
#include "Utilities/TigerMecanum/DriveController.h"
#include "Utilities/TigerMecanum/RobotPose.h"
#include <rev/CANPIDController.h>


/**
 * This class represents a SwerveSubsystem. We hold the tigerSwerve, tigerDrive and talons in here
 */
class DrivebaseSubsystem : public frc::Subsystem {
public:
	DrivebaseSubsystem();
	void InitDefaultCommand();
	const std::unique_ptr<TigerDrive>& GetTigerDrive();
	void MecDrive(double xAxis, double yAxis, double rotAxis, double currentYaw);
	void SetWheelVelocities(double fl, double fr, double bl, double br);
	RigidTransform2D::Delta MecanumForwardKinematics(RigidTransform2D::Delta& flVelocity, RigidTransform2D::Delta& frVelocity, RigidTransform2D::Delta& blVelocity, RigidTransform2D::Delta& brVelocity);
	double ConvertEncoderTicksToEncoderRotations(int ticks);
	double ConvertEncoderRotationsToWheelsRotations(double rotations);
	double ConvertWheelRotationsToDistance(double rotations);
	double ConvertInPerSecondToRPM(double ips);
	double GetWheelSpeed(std::string wheel);
	Translation2D GetWheelDistance(std::string wheel);
	double ConvertRPMToTicksPer100MS(double rpm);
	void ZeroEncoders();
	virtual void Periodic();
	DriveController* GetDriveController();
	void ConfigSparkVelocityPID();
private:
	std::shared_ptr<AHRS> imu;
	std::unique_ptr<rev::CANSparkMax> frontLeftSpark;
	std::unique_ptr<rev::CANSparkMax> frontRightSpark;
	std::unique_ptr<rev::CANSparkMax> backLeftSpark;
	std::unique_ptr<rev::CANSparkMax> backRightSpark;

	std::unique_ptr<TigerDrive> tigerDrive;
	std::unique_ptr<frc::MecanumDrive> mecDrive;
	double m_xVel, m_yVel, m_yawRate;
	double m_oldTimestamp;
	bool m_first;
	Translation2D m_oldFlDistance, m_oldFrDistance, m_oldBlDistance, m_oldBrDistance;
	Rotation2D m_oldGyroYaw;
	Translation2D m_motionSetpoint;
	double flPos, frPos, blPos, brPos;
	DriveController* m_driveController;
	std::unique_ptr<RobotPose> pose;

	std::unique_ptr<rev::CANPIDController> flVelPID;
	std::unique_ptr<rev::CANPIDController> frVelPID;
	std::unique_ptr<rev::CANPIDController> blVelPID;
	std::unique_ptr<rev::CANPIDController> brVelPID;
	const double maxMotorRPM = 5700;
};


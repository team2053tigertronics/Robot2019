/**
 * \file TigerDrive.h
 * \brief Controls the auto rotation of the robot
 * \author Drew Williams & Douglas Williams
 */

#pragma once

#include <AHRS.h>
#include <frc/PIDController.h>
#include <frc/PIDOutput.h>

class TigerDrive : public frc::PIDOutput
{
private:
	const double K_P = .03;
	const double K_I = 0.0;
	const double K_D = .1;
	const double K_F = 0.0;
	const int OVERSHOOT_TIMEOUT = 5;

	bool tooFarCW;
	bool tooFarCCW;
	double rotateToAngleRate;
	double yawOffset;
	int timesThroughLoop;
	bool isRotDone;
	bool controllerOverride;
public:
	TigerDrive(const std::shared_ptr<AHRS>& imuP);
	virtual ~TigerDrive();
	double CalculateRotationValue(double angleToRotateTo, double speedMultiplier);
	double CalculateSpinDirection(double targetAngle, double imuAngle);
	double CalculateSpeedAndOvershoot(int spinDir, double speedMulti);
	double GetAdjYaw();
	void SetAdjYaw(double offset);
	float GetImuYaw();
	bool GetIsRotDone();
	void SetIsRotDone(bool isDone);
	void SetIsRotDoneOverride(bool isDone);
	void SetTimesThroughLoop(int timeLoop);
	bool GetIsRotDoneOverride();

	std::shared_ptr<frc::PIDController> rotateController;
	std::shared_ptr<AHRS> imu;

	void PIDWrite(double output) {
	    rotateToAngleRate = output;
	}
};
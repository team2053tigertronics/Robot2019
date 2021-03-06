/**
 * \file DriveCommand.h
 * \brief The lets us drive around!
 * \author Drew Williams
 */

#pragma once

#include <frc/commands/Command.h>

class DriveCommand : public frc::Command {
public:
	DriveCommand(bool inAuto);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void GetInputs();
	void SetAngleFromInput();
	void RotateCommand();
	void CallToTigerDrive();
	void CheckRotateOverride();
private:
	double xAxis;
	double yAxis;
	double rotAxis;
	double currentYaw;
	double setAngle;
	double finalRotVal;
	bool isAPressed;
	bool isBPressed;
	bool isXPressed;
	bool isYPressed;
	bool isRightShoulderButtonPressed;
	bool isLeftStickPressed;
	bool isRotDone;
	bool autoOverride;
};

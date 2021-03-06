#include "Commands/Drive/RotateToAngle.h"
#include "Robot.h"
#include "RobotMap.h"

RotateToAngle::RotateToAngle(double angleToRotateTo) {
	inputAngle = angleToRotateTo;
	isDone = false;
	currentYaw = 0;
}

void RotateToAngle::Initialize() {
	isDone = false;
	currentYaw = 0;
}

void RotateToAngle::Execute() {
	currentYaw = Robot::drivebaseSubsystem->GetTigerDrive()->GetAdjYaw();
	double outputRate = 0;

	Robot::drivebaseSubsystem->GetTigerDrive()->SetIsRotDoneOverride(false);
	isDone = Robot::drivebaseSubsystem->GetTigerDrive()->GetIsRotDone();
	Robot::drivebaseSubsystem->GetTigerDrive()->rotateController->SetSetpoint(inputAngle);

	outputRate = Robot::drivebaseSubsystem->GetTigerDrive()->CalculateRotationValue(inputAngle, 1);
	Robot::drivebaseSubsystem->MecDrive(0, 0, -outputRate, currentYaw);
}

bool RotateToAngle::IsFinished() {
	return isDone;
}

void RotateToAngle::End() {
	Robot::drivebaseSubsystem->MecDrive(0, 0, 0, currentYaw);
}

void RotateToAngle::Interrupted() {

}

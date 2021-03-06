/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/Drive/FollowPath.h"
#include "Robot.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "RobotMap.h"
#include "Utilities/Math/RigidTransform2D.h"
#include <iostream>

FollowPath::FollowPath(std::string filePath) : m_path(Robot::pathManager->GetPath(filePath)) {
  std::cout<<"got to the constuctor";
  Requires(Robot::drivebaseSubsystem.get());
  m_driveController = Robot::drivebaseSubsystem->GetDriveController();
  m_skip = false;
  m_filePath = filePath;
  isFirst = true;
}

// Called just before this Command runs the first time
void FollowPath::Initialize() {
  std::cout<<"got to the initializer";
  m_skip = false;
  m_driveController->EnableController();
  isFirst = true;
}

// Called repeatedly when this Command is scheduled to run
void FollowPath::Execute() {
  std::cout<<"got to execute";
  RigidTransform2D targetPos = m_path.getInterpolated(InterpolatingDouble(TimeSinceInitialized()));

  if(isFirst) {
    Robot::observer->SetRobotPos(targetPos, TimeSinceInitialized());
    isFirst = false;
  }

  m_driveController->SetFieldTarget(targetPos);

  SmartDashboard::PutNumber("Path X", targetPos.getTranslation().getX());
  SmartDashboard::PutNumber("Path Y", targetPos.getTranslation().getY());
  SmartDashboard::PutNumber("Path Yaw", targetPos.getRotation().getDegrees());

  RigidTransform2D driveSignal = m_driveController->GetDriveControlSignal();

  std::cout << "X Cmd: " << driveSignal.getTranslation().getX() << "\n";
  std::cout << "Y Cmd: " <<  driveSignal.getTranslation().getY() << "\n";
  std::cout << "Yaw Cmd: " << driveSignal.getRotation().getDegrees() << "\n";

  Robot::drivebaseSubsystem->MecDrive(-driveSignal.getTranslation().getX(), driveSignal.getTranslation().getY(), driveSignal.getRotation().getDegrees(), Robot::drivebaseSubsystem->GetTigerDrive()->GetAdjYaw());
}

// Make this return true when this Command no longer needs to run execute()
bool FollowPath::IsFinished() {
  std::cout<<"finished";
  RigidTransform2D lastPoint = m_path.rbegin()->second;
  RigidTransform2D robotPose = Robot::observer->GetLastRobotPose();

  Translation2D errorTranslation = lastPoint.getTranslation().translateBy(robotPose.getTranslation().inverse());
  Rotation2D errorRotation = lastPoint.getRotation().rotateBy(robotPose.getRotation().inverse());

  return ((fabs(errorTranslation.norm()) < Robot::robotMap->kTOLERANCE_POS) && (fabs(errorRotation.getDegrees()) < Robot::robotMap->kTOLERANCE_HEADING)) ||
    (m_path.rbegin()->first.m_value + 2 < TimeSinceInitialized()) ||
    m_skip;
}

// Called once after isFinished returns true
void FollowPath::End() {
  Robot::drivebaseSubsystem->MecDrive(0, 0, 0, 0);
  SmartDashboard::PutNumber("Drive path duration", TimeSinceInitialized());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FollowPath::Interrupted() {
  End();
}

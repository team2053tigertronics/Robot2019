/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/ElevatorSubsystem.h"
#include "Robot.h"
#include "Commands/Elevator/ElevatorControl.h"
#include "frc/WPILib.h"

ElevatorSubsystem::ElevatorSubsystem() : Subsystem("ElevatorSubsystem") {
  elevatorMotorLeader = std::make_unique<ctre::phoenix::motorcontrol::can::TalonSRX>(Robot::robotMap->kELEVATOR_LEADER_ID);
  elevatorMotorFollower01 = std::make_unique<ctre::phoenix::motorcontrol::can::TalonSRX>(Robot::robotMap->kELEVATOR_FOLLOWERONE_ID);
  elevatorMotorFollower02 = std::make_unique<ctre::phoenix::motorcontrol::can::TalonSRX>(Robot::robotMap->kELEVATOR_FOLLOWERTWO_ID);

  elevatorMotorLeader->ConfigFactoryDefault();
  elevatorMotorFollower01->ConfigFactoryDefault();
  elevatorMotorFollower02->ConfigFactoryDefault();

  elevatorMotorLeader->ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled);
  elevatorMotorFollower01->ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled);
  elevatorMotorFollower02->ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled);

  elevatorMotorLeader->ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled);
  elevatorMotorFollower01->ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled);
  elevatorMotorFollower02->ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource_Deactivated, ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled);

  elevatorMotorFollower01->Follow(*elevatorMotorLeader.get());
  elevatorMotorFollower02->Follow(*elevatorMotorLeader.get());

  elevatorMotorLeader->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::CTRE_MagEncoder_Relative);
  elevatorMotorLeader->SetSelectedSensorPosition(0);
  elevatorMotorLeader->ConfigAllowableClosedloopError(0, 1200, 0);
  elevatorMotorLeader->SetSensorPhase(false);

  elevatorMotorLeader->Config_kF(0, Robot::robotMap->kELEVATOR_F);
  elevatorMotorLeader->Config_kP(0, Robot::robotMap->kELEVATOR_P);
  elevatorMotorLeader->Config_kI(0, Robot::robotMap->kELEVATOR_I);
  elevatorMotorLeader->Config_kD(0, Robot::robotMap->kELEVATOR_D);
}

void ElevatorSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new ElevatorControl());
}

int ElevatorSubsystem::ConvertHeightToTicks(double inputHeight) {
  int ticks = 0;
  ticks = inputHeight * Robot::robotMap->kELEVATORTICKS_PER_INCH;
  return ticks;
}

void ElevatorSubsystem::RunElevatorMotor(double speed) {
  SmartDashboard::PutNumber("Elevator Ticks", elevatorMotorLeader->GetSelectedSensorPosition());
  elevatorMotorLeader->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, speed);
}

void ElevatorSubsystem::GoToHeight(double height) {
  elevatorMotorLeader->Set(ctre::phoenix::motorcontrol::ControlMode::Position, ConvertHeightToTicks(height));
}

int ElevatorSubsystem::GetElevatorHeight(){
  int distance = 0;
  int ticks = elevatorMotorLeader->GetSelectedSensorPosition();
  distance = ticks / Robot::robotMap->kELEVATORTICKS_PER_INCH;
  return distance;
}


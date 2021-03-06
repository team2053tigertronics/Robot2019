/*----------------------------------------------------------------------------*/
/* Catherine Deskur made this                                                 */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/phoenix/MotorControl/CAN/TalonSRX.h>
#include <rev/CANSparkMax.h>
#include <rev/CANSparkMaxLowLevel.h>

class LiftSubsystem : public frc::Subsystem {
 private:
 std::unique_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> FootDriverTalon;
 std::unique_ptr<ctre::phoenix::motorcontrol::can::TalonSRX> LegDriverTalon;
 public:
  LiftSubsystem();
  double GetPosition();
  void SetPosition(double position);
  void SetFootSpeed(double speed);
  void SetLegSpeed(double speed);
  int GetLegClosedLoopError();
  virtual void Periodic();
};

#include "ObserverSubsystem.h"
#include "../Utilities/TigerSwerve/TigerSwerve.h"
#include "../RobotMap.h"
#include <RobotController.h>

/**
 * Constructor for our observer. We init a random default value because we dont really know
 * where we will be
 */
ObserverSubsystem::ObserverSubsystem() : m_robotPos(5) {

}

/**
 * Destructor
 */
ObserverSubsystem::~ObserverSubsystem() {

}

/**
 * Looks at our angle and velocity of our wheel modules and estimates our robot pose based on that info.
 * @param flAngle
 * @param flVelocity
 * @param frAngle
 * @param frVelocity
 * @param blAngle
 * @param blVelocity
 * @param brAngle
 * @param brVelocity
 * @param timeStamp FPGA Timestamp
 * @param deltaGyroYaw
 */
void ObserverSubsystem::UpdateRobotPoseObservation(Rotation2D& flAngle, RigidTransform2D::Delta& flVelocity, Rotation2D& frAngle,
		RigidTransform2D::Delta& frVelocity, Rotation2D& blAngle, RigidTransform2D::Delta& blVelocity,
		Rotation2D& brAngle, RigidTransform2D::Delta& brVelocity, double timeStamp, Rotation2D& deltaGyroYaw) {
	RigidTransform2D::Delta deltaRobotPos = TigerSwerve::SwerveForwardKinematics(flAngle, flVelocity, frAngle, frVelocity, blAngle, blVelocity, brAngle, brVelocity);
	RigidTransform2D oldRobotPos = GetLastRobotPose();

	Rotation2D finalAngleDelta = Rotation2D::fromRadians((deltaRobotPos.GetTheta() * kFORWARD_KINEMATICS_WEIGHT) + (deltaGyroYaw.getRadians() * KGYRO_WEIGHT));
	Rotation2D newRobotAngle = oldRobotPos.getRotation().rotateBy(finalAngleDelta);

	Rotation2D halfAngle = oldRobotPos.getRotation().rotateBy(Rotation2D::fromDegrees(finalAngleDelta.getDegrees() * 1));

	Translation2D newRobotTranslation = oldRobotPos.getTranslation().translateBy(Translation2D(-deltaRobotPos.GetX(), -deltaRobotPos.GetY()).rotateBy(halfAngle));

	RigidTransform2D robotPos(newRobotTranslation, newRobotAngle);
	SetRobotPos(robotPos, timeStamp);
}

/**
 * Returns our current robot pose estimation
 * @param timestamp FPGA Timestamp
 * @return A RigidTransform2D holding our translation and rotation
 */
RigidTransform2D ObserverSubsystem::GetRobotPose(double timestamp) {
	return m_robotPos.getInterpolated(timestamp);
}

/**
 * Manually set robotPos. Used to calibrate at start
 * @param robotPos Where we want the robot to think we are
 * @param timestamp FPGA Timestamp
 */
void ObserverSubsystem::SetRobotPos(RigidTransform2D robotPos, double timestamp) {
	m_robotPos.put(InterpolatingDouble(timestamp), robotPos);
}

/**
 * Override the current pose with the new one
 * @param robotPose new robot pose
 */
void ObserverSubsystem::ResetPose(RigidTransform2D robotPose) {
	m_robotPos.clear();
	SetRobotPos(robotPose, RobotController::GetFPGATime() - 37);
	SetRobotPos(robotPose, RobotController::GetFPGATime());
}

/**
 * Override the current pose with zeroed translation and rotation
 */
void ObserverSubsystem::ResetPose() {
	m_robotPos.clear();
	Translation2D zeroTranslation = Translation2D(0, 0);
	Rotation2D zeroRotation = Rotation2D(1, 0, true);
	SetRobotPos(RigidTransform2D(zeroTranslation, zeroRotation), RobotController::GetFPGATime());
}

/**
 * Get our previous pose
 * @return RigidTransform2D holding our previous pose
 */
RigidTransform2D ObserverSubsystem::GetLastRobotPose() {
	return m_robotPos.rbegin()->second;
}

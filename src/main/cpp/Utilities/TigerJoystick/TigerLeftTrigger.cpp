#include "Utilities/TigerJoystick/TigerLeftTrigger.h"
#include <frc/Joystick.h>

/**
 * Constructor for a trigger. Please pass in a pointer to the joystick and axis!
 * @param joy joystick the trigger is attached to
 * @param axis the controller axis that we want to make a trigger
 */
TigerLeftTrigger::TigerLeftTrigger(frc::Joystick* joy, int axis) {
	joystick = joy;
	joystickAxis = axis;
	joystickValue = 0;
}

/**
 *  Are we pressing the left trigger?
 * @return if the right trigger is pressed down at this moment
 */
bool TigerLeftTrigger::Get() {
	joystickValue = TigerLeftTrigger::Deadband(joystick->GetRawAxis(joystickAxis));
	if(joystickValue > 0) {
		return true;
	}
	else {
		return false;
	}
}

/**
 * Makes sure we return clean values instead of something like .0001
 * @param axis what axis are we looking at
 * @return deadbanded value
 */
double TigerLeftTrigger::Deadband(double axis) {
	if(axis > -0.20 && axis < 0.20)
	{
		axis = 0;
	}
	else
	{
		axis = axis * fabs(axis);
	}
	return axis;
}

/**
 * Gets the floating point value of the right joystick
 * @return a value from 0 to 1
 */
double TigerLeftTrigger::GetTriggerValue() {
	joystickValue = TigerLeftTrigger::Deadband(joystick->GetRawAxis(joystickAxis));
	return joystickValue;
}

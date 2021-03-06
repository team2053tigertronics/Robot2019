/**
 * \file RobotMap.h
 * \brief Holds constants for the robot
 * \author Drew Williams
 *
 * Here we hold all of the robots constants.
 * These are the default values when the robot starts up.
 */
#pragma once

#include <string>
#include <iostream>
#include <sstream>

class RobotMap {
public: 
    RobotMap();
    void Init();

    //CONTROLLER STUFF
    int kDRIVER_CONTROLLER_PORT;
    int kOPERATOR_CONTROLLER_PORT;
    double  kCONTROLLER_PERIOD;

    //ENCODER STUFF
    int kTICKS_PER_REV_OF_ENCODER;
    int kTICKS_PER_REV_NEO;
    int kELEVATORTICKS_PER_INCH;
    double  kWRIST_GEAR_RATIO;
    double  kSLAPPER_GEAR_RATIO;
    double  kWHEEL_DIAMETER;
    double  kWHEEL_BASE_LENGTH;
    double  kWHEEL_BASE_WIDTH;

    //DRIVEBASE ROTATION PARAMETERS
    double  kROTATION_P;
    double  kROTATION_I;
    double  kROTATION_D;
    double  kROTATION_ANGLE_TOLERANCE;

    //ELEVATOR PID
    double  kELEVATOR_F;
    double  kELEVATOR_P;
    double  kELEVATOR_I;
    double  kELEVATOR_D;

    //WRIST PID
    double kWRIST_F;
    double kWRIST_P;
    double kWRIST_I;
    double kWRIST_D;

    //ELEVATOR PID
    double  kSLAPPER_F;
    double  kSLAPPER_P;
    double  kSLAPPER_I;
    double  kSLAPPER_D;

    //LEG PID
    double kLEG_F;
    double kLEG_P;
    double kLEG_I;
    double kLEG_D;

    //DRIVEBASE TALONS
    int kDRIVESPARK_FL_ID;
    int kDRIVESPARK_FR_ID;
    int kDRIVESPARK_BL_ID;
    int kDRIVESPARK_BR_ID;

    //INTAKE TALONS
    int kINTAKE_WHEELS_ID;
    int kINTAKE_LEFT_WRIST_ID;
    int KINTAKE_RIGHT_WRIST_ID;

    //ELEVATOR TALONS
    int kELEVATOR_LEADER_ID;
    int kELEVATOR_FOLLOWERONE_ID;
    int kELEVATOR_FOLLOWERTWO_ID;

    //SLAPPER TALONS
    int kINTAKE_SLAPPER_ID;

    //INTAKE PARAMS
    double  kINTAKE_ANGLE_BALL;
    double  kINTAKE_ANGLE_UP;
    double  kSLAPPER_UP_TICKS;
    double  kSLAPPER_DOWN_TICKS;
    double  kSLAPPER_RELEASE_TICKS;
    int kINTAKE_ANGLE_TOLERANCE;
    double  kINTAKE_SPEED;
    double kINTAKE_CURRENT;

    //ELEVATOR PARAMS
    double  kELEVATOR_GROUND;
    double  kELEVATOR_LEVEL_ONE_HATCH;
    double  kELEVATOR_LEVEL_TWO_HATCH;
    double  kELEVATOR_LEVEL_THREE_HATCH;
    double  kELEVATOR_LEVEL_ONE_PORT;
    double  kELEVATOR_LEVEL_TWO_PORT;
    double  kELEVATOR_LEVEL_THREE_PORT;

    //FORWARD KINEMATICS
    double  kFORWARD_KINEMATICS_WEIGHT;
    double  kGYRO_WEIGHT;
    double  kAUTO_CONTROLLER_P;
    double  kAUTO_CONTROLLER_I;
    double  kAUTO_CONTROLLER_D;
    double  kAUTO_CONTROLLER_V;

    double  kENCODER_REVS_PER_WHEEL_REV;

    double  kTOLERANCE_POS;
    double  kTOLERANCE_HEADING;

    double  kSTRAFE_MULTIPLIER;

    //LIFT STUFF
    int kFOOT_TALON_ID;
    int kLEG_LEADER_TALON_ID;

    //VISION
    double kVISION_STEER_P;
    double kVISION_FOW_P;
    double kVISION_MAX_SPEED;
    double kVISION_TARGET_AREA;
};
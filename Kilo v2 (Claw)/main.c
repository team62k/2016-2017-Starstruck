#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  RDrivebaseEncoder,     sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  LDriveBaseEncoder,      sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           LDriveBase,    tmotorVex393_MC29, PIDControl, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port3,           RDriveBase,    tmotorVex393_MC29, PIDControl, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port4,           leftLift,      tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           leftMidLift,   tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port6,           rightMidLift,  tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port7,           rightLift,     tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

#define LOOP_SPEED              25
#define MAX_POWER              127
#define MIN_POWER             -127
#define PID_SENSOR_INDEX    myEncoder
#define PID_SENSOR_SCALE    1

#define PID_MOTOR_INDEX     myMotor
#define PID_MOTOR_SCALE     -1

#define PID_INTEGRAL_LIMIT  50

float  pid_Kp = 2.0;
float  pid_Ki = 0.04;
float  pid_Kd = 0.0;

static int   pidRunning = 1;
static float pidRequestedValue;

// final motor drive
long            motor_driveR;            /// RIGHT
long            motor_driveL;            /// LEFT


/*///////////////////////////////////////////////////////////
/////                      __ ___  ____                 /////
/////                     / /|__ \|  _ \                /////
/////                    / /_   ) | |_) |               /////
/////                   | '_ \ / /|  _ <                /////
/////                   | (_) / /_| |_) |               /////
/////                    \___/____|____/                /////
///// Team 62K Robot                                    /////
///// Main Code                                         /////
///// Authors: Abner Benitez                            /////
///// Since: Nov. 10, 2016                              /////
*////////////////////////////////////////////////////////////

/*
To Do List
1. Try an empty main()
2. what does it mean to have greater resolution in sensors?
3. startTask( ); gotta use this within tasks
4. nMotorEncoder[ ]
*/

//setters

void
setLDriveBase( int valueL )
{
	motor[ LDriveBase ] = valueL;
}


void
setRDriveBase( int valueR )
{
	motor[ RDriveBase ] = valueR;
}

//action methods
void
move( int time, int left, int right )
{
	setLDriveBase( left );
	setRDriveBase( right );
	delay(time);

	setMotorR(0);
	setMotorL(0);
}

//overload this method
void
setArms( int time, int power )
{
	motor[ leftMidLift ] = power;
	motor[ leftLift ] = power;
	motor[ rightMidLift ] = power;
	motor[ rightLift ] = power;
	delay(time);

	motor[ leftMidLift ] = 0;
	motor[ leftLift ] = 0;
	motor[ rightMidLift ] = 0;
	motor[ rightLift ] = 0;
	delay(100);
}

void
setClaw( int time, int power)
{
	motor[claw]=power;
	delay(time);
	motor[claw]=0;
}
void
setClaw(int power){
	motor[claw]=power;
}
//stops everything
void
stopAll()
{
	move( 1000, 0, 0 );
	setArms( 1000, 0 );
	setClaw(1000,0)

}

//PID control task
task pidController()
{
	/*
	float  pidSensorCurrentValue;

	float  pidError;
	float  pidLastError;
	float  pidIntegral;
	float  pidDerivative;
	float  pidDrive;

	// If we are using an encoder then clear it
	if( SensorType[ PID_SENSOR_INDEX ] == sensorQuadEncoder )
	SensorValue[ PID_SENSOR_INDEX ] = 0;

	// Init the variables - thanks Glenn :)
	pidLastError  = 0;
	pidIntegral   = 0;

	while( true )
	{
	// Is PID control active ?
	if( pidRunning )
	{
	// Read the sensor value and scale
	pidSensorCurrentValue = SensorValue[ PID_SENSOR_INDEX ] * PID_SENSOR_SCALE;

	// calculate error
	pidError = pidSensorCurrentValue - pidRequestedValue;

	// integral - if Ki is not 0
	if( pid_Ki != 0 )
	{
	// If we are inside controlable window then integrate the error
	if( abs(pidError) < PID_INTEGRAL_LIMIT )
	pidIntegral = pidIntegral + pidError;
	else
	pidIntegral = 0;
	}
	else
	pidIntegral = 0;

	// calculate the derivative
	pidDerivative = pidError - pidLastError;
	pidLastError  = pidError;

	// calculate drive
	pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);

	// limit drive
	if( pidDrive > PID_DRIVE_MAX )
	pidDrive = PID_DRIVE_MAX;
	if( pidDrive < PID_DRIVE_MIN )
	pidDrive = PID_DRIVE_MIN;

	// send to motor
	motor[ PID_MOTOR_INDEX ] = pidDrive * PID_MOTOR_SCALE;
	}
	else
	{
	// clear all
	pidError      = 0;
	pidLastError  = 0;
	pidIntegral   = 0;
	pidDerivative = 0;
	motor[ PID_MOTOR_INDEX ] = 0;
	}

	// Run at 50Hz
	wait1Msec( 25 );
	}
	*/
}


void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}


//tasks
task autonomous()
{
	// Remove this function call once you have "real" code.
	AutonomousCodePlaceholderForTesting();
}


task usercontrol()
{
	while (true)
	{
		setMotorL(abs(vexRT[ Ch3 ]) > 25 ? vexRT[ Ch3 ] : 0); //mess with deadbands
		setMotorR(abs(vexRT[ Ch2 ]) > 25 ? vexRT[ Ch2 ] : 0);

		if(vexRT[ Btn5U ] || vexRT[ Btn6U ]) //test with == 1
		 setArms(MAX_POWER); // keeps the lift up when holding stars
		if(vexRT[Btn1]){
		 setClaw(MAX_POWER);
		}
		else if(vexRT[Btn2]){
			setClaw(MIN_POWER);
		}
		else{
			setClaw(0);
		}
		wait1Msec(20); //don't hog the CPU :)
	}
}

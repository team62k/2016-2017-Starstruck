#include "main.h"

//setters for Autonomous
void
setLDriveBase( int valueL, int time )
{
	setLDriveBase(valueL/2);
	delay( SAFETY_DELAY );

	setLDriveBase(valueL/2);
	delay( time );
}


void
setRDriveBase( int valueR, int time )
{
	setRDriveBase(valueR/2);
	delay( SAFETY_DELAY );

	setRDriveBase(valueR/2);
	delay( time );
}


#warning "action methods"
//action methods for Autonomous
void
move( int time, int left, int right )
{
	setLDriveBase( left, time );
	setRDriveBase( right, time );

	setLDriveBase( left, 0 );
	setRDriveBase( right, 0 );
}


void
setLift( int time, int power )
{
	setLift(power/2);
	delay( SAFETY_DELAY );

	setLift(power);
	delay( time );

	setLift(0);
	//sleep(100);
}


void
setClaw( int time, int power )
{
	motor[ leftClaw ] = power;
	motor[ rightClaw ] = power;
	delay( time );
}

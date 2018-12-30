#include "autonFunctions.c"

void blueFront_1() {
	punch.firePunch = true;
	wait1Msec(1500);
	setIntake(-1);
	driveStraight(4.5, 1.0);
	hold(200);
	driveStraight(-2, 1.0);
	pointTurn(90, 0.8);
	driveStraight(3, 1.0);
	hold(200);
	driveStraight(-1, 1.0);
}


void blueFront_2() {
	setIntake(-1);
	driveStraight(3.8, 1.0);
	driveStraight(0.7, 0.5);
	hold(200);
	driveStraight(-4, 1.0);
	pointTurn(300, 0.8);
	driveStraight(4.5, 1.0);
	hold(200);
	driveStraight(-2.5, 1.0);
	pointTurn(100, 0.8);
	driveStraight(3, 1.0);
}

void redBack_1() {
	setIntake(1);
	driveStraight(3.5, 1.0);
	driveStraight(1, 0.5);
	hold(200);
	driveStraight(-4, 1.0);
}

void redFront_1() {
	punch.firePunch = true;
	wait1Msec(1500);
	pointTurn(5, 0.8);
	driveStraight(4.5, 1.0);
	hold(200);
	driveStraight(-2, 1.0);
	pointTurn(300, 0.8);
	setIntake(-1);
	driveStraight(3, 1.0);
	hold(200);
	driveStraight(-1, 1.0);
}

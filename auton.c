#include "autonFunctions.c"

void skillsAuton() {
// PARK
	driveStraight(2, 0.5, true);
	pointTurn(-80);
	driveRaw(700, 0.5);
	hold(1000);
	driveStraight(1.5, -0.5);
	driveRaw(2000, -1);
	backTorque(0.5);
	return;
	punch.off = false;
	driveStraight(3.5, 0.5);
	setIntake(-1);
	driveStraight(1.5, 0.2, true);
	hold(1000);
	driveStraight(-3.8, 0.5);
	hold(500);
	pointTurn(-80);
	driveStraight(0.4, 0.5, true);
	shoot(true);
	waitForPunch();
	setIntake(0);
	// knocks over ballcap
	driveStraight(3, 1.0);
	driveStraight(0.5, 0.4, true);
	hold(300);
	// backs up to flat cap
	driveStraight(-2, 0.5, true);
	// points roller towards flat cap
	pointTurn(-90);
	setRoller(1);
	driveStraight(-2, 0.7);
	return;
}

void blueFront_1() {

//setIntake(-1);
	//hold(1000);
	// shoots and waits
	//shoot(true);
	//waitForPunch();
	driveStraight(4.2, 0.8);
	hold(200);
	driveStraight(-4, 0.8, true);
	pointTurn(-90);
	// up against wall on starting tile
	driveRaw(500, -0.6);
	// knocks over ballcap
	driveStraight(3.5, 1.0);
	driveStraight(0.7, 0.4);
	// backs up to flat cap
	driveStraight(-2.5, 0.5, true);
	// points roller towards flat cap
	pointTurn(-90);
	setRoller(1);
	driveStraight(-3, 0.7);
	return;
	pointTurn(90, 0.4);
	driveStraight(2.5, 0.8);
	// drives to center line and turns towards flag
	pointTurn(90, 0.4);
	// hits flag and backs up
	driveStraight(3, 0.8, true);
	driveStraight(-1, 1);
}

// from december comp
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

void blueBack_1() {
	// gets ball cap
	setIntake(-1);
	driveStraight(3.5, 0.8);
	driveStraight(0.6, 0.3, true);
	hold(300);
	pointTurn(90);
	setRoller(1);
	driveStraight(-2.2, 0.8, true, 1000);
	hold(1000);
	driveStraight(2, 0.8, false, 500);
	return;
	hold(100);
	pointTurn(90, 0.7);
	pointTurn(45, 0.7);
	setRoller(1);
	driveStraight(-3, 0.5);
	driveStraight(3, 0.5);
	setRoller(0);
	// turns front to wall and drives to it
	pointTurn(60, 0.4);
	driveStraight(2, 0.5);
	driveRaw(500, 0.5);
	// backs up from wall and turns
	driveStraight(-0.2, 0.4);
	pointTurn(-90, 0.7);
	driveStraight(2, 0.5, true);
	// turns back towards platform and tries to park
	pointTurn(90, 0.7);
	driveStraight(-4, 0.5);
}

// maybe parks
void blueBack_2() {
	driveStraight(2.6, 0.5, true);
	pointTurn(90);
	driveRaw(500, 0.5);
	hold(100);
	driveStraight(-1, 1);
	driveRaw(1500, -1);
}

void redBack_1() {
	// gets ball cap
	shoot(true);
	setIntake(-1);
	driveStraight(3.5, 0.8);
	driveStraight(0.6, 0.3, true);
	hold(300);
	pointTurn(-90);
	setRoller(1);
	driveStraight(-2, 0.8, true, 1000);
	hold(1000);
	driveStraight(2, 0.8, false, 500);
	return;
	driveRaw(1000, -0.8);
	driveRaw(500, 0.8);
	return;
	// backs up and turns roller towards flat cap
	driveStraight(-2, 1.0, true);
	setIntake(0);
	return;
}

// PARK
void redBack_2() {
	driveStraight(2, 0.5, true);
	pointTurn(-90);
	driveRaw(500, 0.5);
	hold(100);
	driveStraight(-1, 1);
	driveRaw(1500, -1);
}

void redFront_1() {
	punch.off = false;
	driveStraight(3.5, 0.5);
	setIntake(-1);
	driveStraight(1.5, 0.2, true);
	hold(1000);
	driveStraight(-3.8, 0.5);
	hold(500);
	pointTurn(-80);
	driveStraight(0.4, 0.5, true);
	shoot(true);
	waitForPunch();
	setIntake(0);
	// knocks over ballcap
	driveStraight(3, 1.0);
	driveStraight(0.5, 0.4, true);
	hold(300);
	// backs up to flat cap
	driveStraight(-2, 0.5, true);
	// points roller towards flat cap
	pointTurn(-90);
	setRoller(1);
	driveStraight(-2, 0.7);
	return;
}

void redFront_2() {

}

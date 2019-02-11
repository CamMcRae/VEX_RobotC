typedef struct{
	bool firePunch;
	bool inPosition;
	bool reset;
	bool lastValue;
	float power;
	bool off;
} linearPuncher;

linearPuncher punch;

void setPunch(float pwr) {
	motor[punch_1] = motor[punch_2] = motor[punch_3] = pwr;
}

task puncherController() {

	// PUNCH SETUP
	punch.firePunch = false;
	punch.inPosition = false;
	punch.reset = false;
	punch.lastValue = false;
	punch.power = 90;
	punch.off = true;

	while (true) {

		// gets the current value from the limit switch
		punch.reset = SensorValue[punchLimitSwitch] == 1 ? true : false;

		// tests if the punch has shot
		if (punch.lastValue && !punch.reset) {
			punch.firePunch = false;
		}

		// override button when true
		if (punch.firePunch) {
			setPunch(punch.power);
			} else if (!punch.off){
			// otherwise turn the motors to hit the button
			if (!punch.reset) {
				setPunch(punch.power);
				} else {
				setPunch(25);
			}
		} else {
				setPunch(0);
		}
		punch.lastValue = punch.reset;
		wait1Msec(35);
	}
}

void shoot(bool turnOff = false) {
		if (punch.off) {
			punch.off = false;
		} else {
			punch.firePunch = true;
			punch.off = turnOff;
		}
}

// blocking function to stop other autonomous functions while the punch is firing
void waitForPunch() {
	clearTimer(T2);
	// waits for the punch to fire or for 2.5 seconds if something has gone wrong and the punch is unable to fire
	while(punch.firePunch) {
		if (time1[T2] > 2500) break;
		wait1Msec(20);
	}
}

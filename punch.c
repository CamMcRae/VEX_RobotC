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
	motor[punch_1] = pwr;
	motor[punch_2] = pwr;
	motor[punch_3] = pwr;
}

task puncherController() {

	// PUNCH SETUP
	punch.firePunch = false;
	punch.inPosition = false;
	punch.reset = false;
	punch.lastValue = false;
	punch.power = 75;
	punch.off = false;

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
				setPunch(30);
			}
		} else {
				setPunch(0);
		}
		punch.lastValue = punch.reset;
		wait1Msec(35);
	}
}

void shoot(bool turnOff = false) {
		if (!punch.off) punch.firePunch = true;
		punch.off = turnOff;
}

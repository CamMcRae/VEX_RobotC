int intakeMode = 0;

task intakeControl() {
	while (true) {
		switch(intakeMode) {
		case 0:
			motor[intake] = 0;
			break;
		case 1:
			setIntake(127);
			break;
		case 2:
			setIntake(-127);
			break;
		case 3:
			if (SensorValue[intakeSen] < 50) {
				setIntake(127);
				break;
				} else {
				delay(20);
				continue;
			}
		}
		delay(20);
	}
}

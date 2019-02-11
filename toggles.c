bool reverseDrive = false;
bool reversePressed = false;

bool slowDrive = false;
bool slowPressed = false;

// reverse drive toggle
void reverseToggle() {
	if (vexRT[Btn6DXmtr2]) {
		if (!reversePressed){
			reverseDrive = !reverseDrive;
		}
		reversePressed = true;
		} else if (reversePressed) {
		reversePressed = false;
	}
}

// slow drive toggle
void slowToggle() {
	if (vexRT[Btn5DXmtr2]) {
		if (!slowPressed){
			slowDrive = !slowDrive;
		}
		slowPressed = true;
		} else if (slowPressed) {
		slowPressed = false;
	}
}

bool shootPressed1 = false;
bool shootPressed2 = false;

void shootToggle() {
	// shoots catapult
	if (vexRT[Btn6UXmtr2]){
		if (!shootPressed1) shoot();
		shootPressed1 = true;
		} else if (shootPressed1) {
		shootPressed1 = false;
	}

	// shoots catapult but doesnt reset it
	if (vexRT[Btn5UXmtr2]){
		if (!shootPressed2) shoot(true);
		shootPressed2 = true;
		} else if (shootPressed2) {
		shootPressed2 = false;
	}
}

bool cataPressed = false;

// toggles the E-Stop on the catapult
void cataToggle() {
	if (vexRT[Btn7L]) {
		if (!cataPressed) punch.off = !punch.off;
		cataPressed = true;
	} else if (cataPressed) {
		cataPressed = false;
	}
}

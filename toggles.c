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

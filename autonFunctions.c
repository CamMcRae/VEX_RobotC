float ticks2;
float leftSen2;
float rightSen2;

void setBaseLeft(float pwr){
	pwr = (int) clamp(pwr, -127.0, 127.0);
	motor[baseLeft] = motor[baseLeft_1] = pwr;
}

void setBaseRight(float pwr){
	pwr = (int) clamp(pwr, -127.0, 127.0);
	motor[baseRight] = motor[baseRight_1] = pwr;
}

void setBase(float leftPwr, float rightPwr){
	leftPwr = (int) clamp(leftPwr, -127, 127);
	rightPwr = (int) clamp(rightPwr, -127, 127);
	leftSen2 = leftPwr;
	rightSen2 = rightPwr;
	motor[baseLeft] = motor[baseLeft_1] = leftPwr;
	motor[baseRight] = motor[baseRight_1] = rightPwr;
}

void setBase(float pwr){
	pwr = (int) clamp(pwr, -127, 127);
	motor[baseLeft] = motor[baseLeft_1] = pwr;
	motor[baseRight] = motor[baseRight_1] = pwr;
}

// sets power to motors and powers for an amount of time
void driveRaw(int ms, float power = 1) {
	setBase(127 * power);
	wait1Msec(ms);
	setBase(0);
}

void setIntake(int dir) {
	motor[intake] = -dir * 127;
}

void setRoller(int dir) {
	motor[roller] = -dir * 127;
}

void hold(int ms) {
	wait1Msec(ms);
}

// applies backtorque to wheels
void backTorque(float dir, float pwr = 1) {
	setBase((int) 30 * pwr * dir);
	hold(100);
	setBase(0);
}

void backTorqueLeft(float dir) {
	setBaseLeft(30 * dir);
	hold(150);
	setBaseLeft(0);
}

void backTorqueRight(float dir) {
	setBaseRight(30 * dir);
	hold(150);
	setBaseRight(0);
}

void backTorque2(float lDir, float rDir) {
	setBase(30 * lDir, 30 * rDir);
	hold(150);
	setBase(0);
}

void pointTurn(int degrees, float power = 0.5, int maxTime = -1) {

	// finds which way to spin the wheels
	int dir = sgn(degrees);

	// calculates a max time to prevent infinite loops (30 * degrees + 1000) milliseconds
	if (maxTime == -1) maxTime = abs(degrees) * 30 + 1000;

	// Reset encoders
	SensorValue[leftBaseEnc] = 0;
	SensorValue[rightBaseEnc] = 0;

	// calculates ticks to turn encoders
	float ticks = (31 * abs(degrees)) / 10.0;
	ticks2 = ticks;

	// PID constants
	// something around this value
	float Kp = 0.9;
	float Kd = 0.1;

	//Kd = 0;

	// PID variables
	float error = 0;
	float lastError = 0;
	float derivative = 0;

	// sensorvalues to not do multiple encoder reads in a loop
	int leftSen = 0;
	int rightSen = 0;

	// resets infinite loop timer
	clearTimer(T1);

	while (true) {

		// timer exit condition
		if (time1[T1] > maxTime) break;

		// sensor reading
		leftSen = -SensorValue[leftBaseEnc] * dir;
		leftSen2 = leftSen;
		rightSen = SensorValue[rightBaseEnc] * dir;
		rightSen2= rightSen;

		datalogDataGroupStart();
		datalogAddValue(0, abs(leftSen2));
		datalogAddValue(1, abs(rightSen2));
		datalogDataGroupEnd();

		// left and right powers
		float leftPwr;

		float rightPwr;

		if (abs(leftSen) > ticks) break;

		error = abs(leftSen) - abs(rightSen);

		derivative = error - lastError;

		leftPwr = 100 * power;

		float modify = (error * Kp) + (derivative * Kd);

		rightPwr = leftPwr + modify;

		setBase(leftPwr * dir, -rightPwr * dir);

		lastError = error;
		delay(25);
	}
	backTorque2(-dir, dir);
	setBase(0);
}

void driveStraight(float distance, float power, bool hold = false, int maxTime = -1) {

	int dir = sgn(distance);

	// reset sensors
	SensorValue(leftBaseEnc) = 0;
	SensorValue(rightBaseEnc) = 0;

	// calculate ticks
	float ticks = (abs(distance)  * 12.0) / (PI * 5.5) * 360.0;
	ticks2 = ticks;
	if (maxTime < 0) maxTime = abs(distance) * 1000 + 1500; // 1 foot per second plus 1.5 seconds

	float Kp = 0.0065; //0.025;
	Kp = 0.025;
	//Kp = 0.0005;
	float Kd = 0.07; //higher than 0.7, less than 1

	Kd = 0;
	float error = 0;
	float lastError = 0;
	float derivative = 0;

	int leftSen = 0;
	int rightSen = 0;
	/*
	bool leftRun = true;
	bool rightRun = true;
	*/
	// only runs loop while left is less than target ticks
	clearTimer(T1);
	while (abs(leftSen) <= ticks) {

		// stop infinite loops and allows to run into walls, and it will exit automatically
		if (time1(T1) > maxTime) break;

		leftSen = -SensorValue[leftBaseEnc] * dir;
		leftSen2 = leftSen;
		rightSen = SensorValue[rightBaseEnc] * dir;
		rightSen2 = rightSen;
		/*// applies back torque when left has reached destination
		if (leftRun && leftSen > ticks) {
		if (hold) {
		backTorqueLeft(-dir);
		setBaseLeft(10);
		}
		leftRun = false;
		}

		// applies back torque when right has reached destination
		if (rightRun && rightSen > ticks) {
		if (hold) {
		backTorqueLeft(-dir);
		setBaseLeft(10);
		}
		rightRun = false;
		}
		// breaks loop when both have reached destination
		if (leftSen > ticks && rightSen > ticks) break;

		// error is the difference in ticks
		error = leftSen - rightSen;
		*/

		float leftPwr;

		float rightPwr;

		if (dir > 0) {

			error = abs(leftSen) - abs(rightSen);

			derivative = error - lastError;

			leftPwr = 100 * power;

			float modify = (error * Kp) + (derivative * Kd);

			rightPwr = leftPwr + modify;

			} else {

			error =  abs(rightSen) - abs(leftSen);

			derivative = error - lastError;

			rightPwr = 100 * power;

			float modify = (error * Kp) + (derivative * Kd);

			leftPwr = rightPwr - modify;

		}

		setBase(leftPwr * dir, rightPwr * dir);

		lastError = error;
		delay(25);
	}
	if (hold) {
		backTorque(-dir);
		} else {
		setBase(0);
	}
}

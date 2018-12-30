#include "utility.c"

void setIntake(int dir) {
	motor[intake] = dir * 127;
}

void setRoller(int dir) {
	motor[roller] = dir * 127;
}

void pointTurn(int degrees, float power) {

	int dir = sgn(degrees);

	// Reset encoders
	SensorValue[leftBaseEnc] = 0;
	SensorValue[rightBaseEnc] = 0;

	float arcLength = degreesToRadians(degrees) * 5.6;

	int ticks = arcLength / (PI * 4.0) * 360.0;

	// starts motors
	motor[baseLeft]  =  dir * power * 100;
	motor[baseRight] = -dir * power * 100;

	if (dir > 0) { // right turn
		bool exit1 = false;
		bool exit2 = false;
		while (!exit1 && !exit2) {
			if (SensorValue[leftBaseEnc] > ticks){
				motor[baseLeft] = dir * power * 100;
				exit1 = true;
			}
			if (-SensorValue[rightBaseEnc] > ticks){
				motor[baseRight] = -dir * power * 100;
				exit2 = true;
			}
		}
		} else { // left turn
		bool exit1 = false;
		bool exit2 = false;
		while (!exit1 && !exit2) {
			if (SensorValue[leftBaseEnc] < -ticks){
				motor[baseLeft] = dir * power * 100;
				exit1 = true;
			}
			if (SensorValue[rightBaseEnc] > ticks){
				motor[baseRight] = -dir * power * 100;
				exit2 = true;
			}
		}
	}
	// zero motors
	motor[baseLeft]  = -30;
	motor[baseRight] = 30;
	wait1Msec(80);
	motor[baseLeft]  = 0;
	motor[baseRight]  = 0;
}

// function to use when driving
void driveStraight(int distance, float power) {

	// reset sensors
	SensorValue(leftBaseEnc) = 0;
	SensorValue(rightBaseEnc) = 0;

	// calculate ticks
	float ticks = abs(distance) / (PI * 4.5/12.0) * 360.0;

	float Kp = 0.1;
	/*float Ki = 0.1;
	float Kd = 0.5;
	float Ilimit = 80;*/

	float lastError = 0;
	float error = 0;

	int leftSen = SensorValue[leftBaseEnc];
	int rightSen = -SensorValue[rightBaseEnc];

	// only runs loop while left is less than target ticks
	while (leftSen < ticks) {
		leftSen = SensorValue[leftBaseEnc] * sgn(distance);
		rightSen = -SensorValue[rightBaseEnc] * sgn(distance);

		// error is the differance in ticks
		error = leftSen - rightSen;

		// calculates motor power
		float leftPwr = -100 * power;
		float rightPwr = leftPwr + (error * Kp);

		// updates motor powers
		motor[baseLeft]  = leftPwr * sgn(distance);

		motor[baseRight] = rightPwr * sgn(distance);

		lastError = error;
		delay(20);
	}

	// zero motors
	motor[baseLeft]  = 30 * sgn(distance);
	motor[baseRight] = 30 * sgn(distance);
	wait1Msec(100);
	motor[baseLeft]  = 0;
	motor[baseRight]  = 0;
}

// turns to an angle, taking the shortest route
void turnTo(float deg, float pwr = 1, float dir = 0) {
	// ALL ANGLE VALUES ARE IN DEGREES

  // clamps power between 0 and 1
	pwr = clamp(pwr, 0, 1);

	// PID Constants
	float kP = 0.5;
	float kI = 0.0;
	float kD = 0.0;

	float ILimit = 50;

	// PID Vars
	float error = 0;
	float lastError = 0;
	float integral = 0;
	float derivative = 0;

	do {

		// PID works in relative angles. negative means left turn, positive is right.
		error = angleBetween(deg, bot.angle);
		// keeps integral within reason. Does not add unless error is less than limit
		integral += abs(error) < 5 ? error : 0;
		derivative = error - lastError;

		// modifier
		float modify = error * kP + integral * kI + derivative * kD;

		motor[baseLeft] = 100 * pwr * modify;
		motor[baseRight] = 100 * pwr * modify;
		lastError = error;

	// waits for error and last error to both be less than 1/2 a degree
	} while(abs(error) < 0.5 && abs(lastError) < 0.5);
}

void driveTo(float x, float y, float pwr = 1, float dir = 1, float hold = false) {

	// path following logic





	// stoping logic
	if (hold) {
		backTorque(-dir);
	}
}



// sets power to motors and powers for an amount of time
void driveRaw(int ms, int power = 1) {
	motor[baseLeft]  = -127 * power;
	motor[baseRight] = -127 * power;
	wait1Msec(ms);
	motor[baseLeft] = 0;
	motor[baseRight] = 0;
}

void hold(int ms) {
	wait1Msec(ms);
}

// applies backtorque to wheels
void backTorque(float dir) {
	motor[baseLeft] = 30 * dir;
	motor[baseRight] = 30 * dir;
	hold(100);
	motor[baseLeft] = 0;
	motor[baseLeft] = 0;
}

// keeps track of robots position
task odometry() {
	while (true) {

		float leftSen = SensorValue[leftBaseEnc];

		bot.deltaLeft = leftSen/360.0 * (2 * bot.leftRadius * PI);

		float rightSen = SensorValue[rightBaseEnc];

		bot.deltaRight = rightSen/360.0 * (2 * bot.leftRadius * PI);

		float backSen = SensorValue[backBaseEnc];

		bot.deltaBack = backSen/360.0 * (2 * bot.leftRadius * PI);

		float angle = (bot.deltaLeft - bot.deltaRight)/(bot.leftDist + bot.rightDist);

		float trackingRadius = bot.deltaRight / angle + bot.rightDist;

		float a = 2 * sin(angle / 2);

		float deltaX = a * ((bot.deltaBack / angle) + bot.backDist);

		float deltaY = a * ((bot.deltaRight / angle) + bot.rightDist);

		bot.posX = bot.lastPosX + deltaX;

		bot.posY = bot.lastPosY + deltaY;

		bot.angle = bot.lastAngle + angle;
		delay(20);
	}
}

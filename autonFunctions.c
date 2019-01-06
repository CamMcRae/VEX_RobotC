#include "utility.c"
#include "punch.c"

void setBaseLeft(float pwr){
		pwr = clamp(pwr, -127, 127);
		motor[baseLeft] = pwr;
		motor[baseLeft_1] = pwr;
}

void setBaseRight(float pwr){
		pwr = clamp(pwr, -127, 127);
		motor[baseRight] = pwr;
		motor[baseRight_1] = pwr;
}

void setBase(float leftPwr, float rightPwr){
		leftPwr = clamp(leftPwr, -127, 127);
		rightPwr = clamp(rightPwr, -127, 127);
		motor[baseLeft] = leftPwr;
		motor[baseLeft_1] = leftPwr;
		motor[baseRight] = rightPwr;
		motor[baseRight_1] = rightPwr;
}

void setBase(float pwr){
		pwr = clamp(pwr, -127, 127);
		motor[baseLeft] = pwr;
		motor[baseLeft_1] = pwr;
		motor[baseRight] = pwr;
		motor[baseRight_1] = pwr;
}

// sets power to motors and powers for an amount of time
void driveRaw(int ms, int power = 1) {
	setBase(-127 * power);
	wait1Msec(ms);
	setBase(0);
}

void setIntake(int dir) {
	motor[intake] = dir * 127;
}

void setRoller(int dir) {
	motor[roller] = dir * 127;
}

void hold(int ms) {
	wait1Msec(ms);
}

// applies backtorque to wheels
void backTorque(float dir) {
	setBase(30 * dir);
	hold(100);
	setBase(0);
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

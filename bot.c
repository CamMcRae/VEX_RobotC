typedef struct {
	// odometry things
	float leftDist;
	float rightDist;
	float backDist;

	float deltaLeft;
	float deltaRight;
	float deltaBack;

	float leftRadius;
	float rightRadius;
	float backRadius;

	float angle;
	float startAngle;
	float lastAngle;

	Vector pos;

	Vector lastPos;

} BotData;

BotData bot;

// keeps track of robots position
task odometry() {

	// ODOMETRY SETUP
	bot.leftRadius = 2.75;
	bot.rightRadius = 2.75;
	bot.backRadius = 3.0;

	bot.leftDist = 3.125;
	bot.rightDist = 3.625;
	bot.backDist = 1.0;

	bot.lastAngle = PI/4;
	bot.startAngle = bot.lastAngle;


	while (true) {

		float leftSen = SensorValue[leftBaseEnc];

		bot.deltaLeft = leftSen/360.0 * (2 * bot.leftRadius * PI);

		float rightSen = SensorValue[rightBaseEnc];

		bot.deltaRight = rightSen/360.0 * (2 * bot.rightRadius * PI);

		float backSen = SensorValue[backBaseEnc];

		bot.deltaBack = backSen/360.0 * (2 * bot.backRadius * PI);

		bot.angle = bot.lastAngle + (bot.deltaLeft - bot.deltaRight)/(bot.leftDist + bot.rightDist);

		float deltaAngle = bot.angle - bot.startAngle;

		Vector deltaPos;

		if (deltaAngle == 0) {

			deltaPos.x = bot.deltaBack;

			deltaPos.y = bot.deltaRight;

			} else {

			float a = 2 * sin(bot.angle / 2);

			deltaPos.x = a * ((bot.deltaBack / deltaAngle) + bot.backDist);

			deltaPos.y = a * ((bot.deltaRight / deltaAngle) + bot.rightDist);
		}

		float avgAngle = bot.startAngle + deltaAngle/2;

		// rotate position vector

		float newHeading = atan2(deltaPos.x, deltaPos.y) - avgAngle;

		float mag = sqrt((deltaPos.x * deltaPos.x) + (deltaPos.y * deltaPos.y ));

		Vector newPos;

		newPos.x = cos(newHeading) * mag;
		newPos.y = sin(newHeading) * mag;

		bot.pos.x = bot.lastPos.x + newPos.x;

		bot.pos.y = bot.lastPos.y + newPos.y;

		delay(20);
	}
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

	float ILimit = 5;

	// PID Vars
	float error = 0;
	float lastError = 0;
	float integral = 0;
	float derivative = 0;

	do {

		// PID works in relative angles. negative means left turn, positive is right.
		error = angleBetween(deg, bot.angle);
		// keeps integral within reason. Does not add unless error is less than limit
		integral += abs(error) < ILimit ? error : 0;
		derivative = error - lastError;

		// modifier
		float modify = error * kP + integral * kI + derivative * kD;

		float leftPwr = 100 * pwr * modify;
		float rightPwr = -100 * pwr * modify;

		setBase(leftPwr, rightPwr);

		lastError = error;

		// waits for error and last error to both be less than 1/2 a degree
	} while(abs(error) < 0.5 && abs(lastError) < 0.5);
}

void driveTo(Vector sp, Vector ep, float pwr = 1, float dir = 1, float brake = false) {

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

	// path following logic

	while (true) {

	Vector botTemp;
	botTemp.x = bot.pos.x;
	botTemp.y = bot.pos.y;

	Vector dist;
	dist.x = cos(bot.angle);
	dist.y = sin(bot.angle);

	vectorSetMag(dist, 12);

	Vector predicted;

	vectorAdd(predicted, botTemp, dist);

	error = distanceToLine(sp, ep, predicted.x, predicted.y);

	integral += abs(error) < ILimit ? error : 0;

	derivative = error - lastError;

	// modifier
	float modify = error * kP + integral * kI + derivative * kD;

	float leftPwr = 100 * -pwr * modify;
	float rightPwr = 100 * pwr * modify;

	setBase(leftPwr, rightPwr);

	lastError = error;
	}

	// stoping logic
	if (brake) {
		backTorque(-dir);
	}
}

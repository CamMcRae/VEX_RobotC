// returns the min of 2 inputs
float min(float a, float b) {
	return (a < b ? a : b);
}

// returns the max of 2 inputs
float max(float a, float b) {
	return (a < b ? b : a);
}

// returns the relative angle between the target coordinates
// works in degrees
float angleBetween(float target, float current) {
	return (target - current + 180) % 360 - 180;
}

// clamps a value between an upper and lower limit
float clamp(float value, float lowerLimit, float upperLimit) {
    return max(lowerLimit, min(value, upperLimit));
}

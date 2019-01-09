// returns the min of 2 inputs
float min(float a, float b) {
	return (a < b ? a : b);
}

// returns the max of 2 inputs
float max(float a, float b) {
	return (a < b ? b : a);
}

// clamps a value between an upper and lower limit
float clamp(float value, float lowerLimit, float upperLimit) {
    return max(lowerLimit, min(value, upperLimit));
}

float map(float a, float in_min, float in_max, float out_min, float out_max) {
	return (a - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
// returns the relative angle between the target coordinates
// works in degrees
float angleBetween(float target, float current) {
	return ((target - current + 180) % 360) - 180;
}

// returns the distance between 2 points
float distance(Vector p1, Vector p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

// returns the distance between a line define by p1,p2 and point x,y
float distanceToLine(Vector p1, Vector p2, float x0, float y0) {
  float top = (p2.y - p1.y) * x0 - (p2.x - p1.x) * y0 + p2.x * p1.y - p2.y * p1.x;
  float bottom = distance(p1, p2);
  return top / bottom;
}
*/

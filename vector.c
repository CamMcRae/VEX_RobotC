typedef struct{
	float x;
	float y;
} Vector;

void vectorAdd(Vector &v, Vector a, Vector b) {
	v.x = a.x + b.x;
	v.y = a.y + b.y;
}

void vectorSub(Vector &v, Vector a, Vector b) {
	v.x = a.x - b.x;
	v.y = a.y - b.y;
}

float vectorMag(Vector v) {
	return sqrt((v.x * v.x) + (v.y * v.y));
}

void vectorMult(Vector &v, float m) {
	v.x *= m;
	v.y *= m;
}

float vectorHeading(Vector v) {
	return atan2(v.y, v.x);
}

void vectorSetMag(Vector &v, float n) {
	vectorMult(v, n / vectorMag(v));
}

void vectorNormalize(Vector &v) {
		float len = vectorMag(v);

		if (len != 0) vectorMult(v, 1/len);
}

float vectorDot(Vector a, Vector b) {
	return a.x * (b.x || 0) + a.y * (b.y || 0);
}

void vectorRotate(Vector &v, float angle) {
	float newH = vectorHeading(v) + angle;
	float magnitude = vectorMag(v);
	v.x = cos(newH) * magnitude;
	v.y = sin(newH) * magnitude;
}

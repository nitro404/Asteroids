#ifndef EXTENDED_MATH_H
#define EXTENDED_MATH_H

namespace Math {
	extern const float PI;
	extern const float HalfPI;
	extern const float QuarterPI;
	extern const float TwoPI;
	extern const float E;
	extern const float Log10E;
	extern const float Log2E;

	float min(float a, float b);
	float max(float a, float b);
	float clamp(float value, float min, float max);
	float abs(float v);
	float distance(float a, float b);
	float radiansToDegrees(float r);
	float degreesToRadians(float d);
	float lerp(float a, float b, float amount);
	float normalize(float value, float min, float max);
}

#endif // EXTENDED_MATH_H

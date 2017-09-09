#ifndef __VEC3_H__
#define __VEC3_H__

struct Vec3_t
{
	float x, y, z;

	Vec3_t() :
		x(0.0f),
		y(0.0f),
		z(0.0f)
	{}

	Vec3_t(float _x, float _y, float _z) :
		x(_x),
		y(_y),
		z(_z)
	{}
};

#endif // __VEC3_H__
#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
};

class hitable
{
public:
	//純粋仮想関数　定義はそれぞれのhitで行う
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec)const = 0;
};

#endif
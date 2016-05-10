#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const = 0;
};

class lambertian : material {
public:
	lambertian(const vec3& a) :albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
	vec3 albedo;
};

struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
	material *mat_ptr;
};

class hitable
{
public:
	//純粋仮想関数　定義はそれぞれのhitで行う
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec)const = 0;
};

vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n)*n;
}

class metal :public material {
public:
	metal(const vec3& a) :albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const {
		vec3 reflected = reflect(unit_vector(r_in.direction()), red.notmal);
		attenuation = albedo;
		return (dot(csattered.direction(), rec.normal) > 0);
	}
	vec3 aldedo;
};

#endif

#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

#include <random>
std::random_device rnd;
std::mt19937 mt(rnd());
std::uniform_real_distribution<> rand01(0.0, 1.0);

double drand48() {
	//return random number ranges from 0<=t<1
	return rand01(mt);
}

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while (p.suared_length() >= 1.0);
	return p;
}

class material;

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
	virtual int hit(const ray& r, float t_min, float t_max, hit_record& rec)const = 0;
};

vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n)*n;
}

class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const = 0;
};


class metal :public material {
public:
	metal(const vec3& a, float f) :albedo(a) {
		if (f > 1) {
			fuzz = f;
		}
		else {
			fuzz = 1;
		}
	}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const {
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
	vec3 albedo;
	float fuzz;
};


class lambertian :public material {
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


#endif

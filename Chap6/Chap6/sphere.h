/*‹…–Ê‚Æ‚ÌŒð·”»’è*/

#ifndef SPHEREH
#define SPHEREH
#include "hitable.h"

//hitable‚©‚ç”h¶‚µ‚½sphereƒNƒ‰ƒX
class sphere: public hitable
{
public:
	sphere() {}
	sphere(vec3 cen, float r) :center(cen), radius(r) {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	vec3 center;
	float radius;
};

//ray‚ª‹…–Ê‚ÆÕ“Ë‚·‚é‚©‚Ì”»’è
bool sphere::hit(const ray& r, float tmin, float tmax, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - a*c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(b*b - a*c)) / a;
		if (temp<tmax && temp>tmin) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp = (-b + sqrt(b*b - a*c)) / a;
		if (temp<tmax && temp>tmin) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}
#endif // !SPHEREH


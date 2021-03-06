/*球面との交差判定*/

#ifndef SPHEREH
#define SPHEREH
#include "hitable.h"

//hitableから派生したsphereクラス
class sphere: public hitable
{
public:
	sphere() {}
	sphere(vec3 cen, float r, material* m) :center(cen), radius(r), mat(m){};
	virtual int hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	vec3 center;
	float radius;
	material* mat;
};

//rayが球面と衝突するかの判定
int sphere::hit(const ray& r, float tmin, float tmax, hit_record& rec) const
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
			return 1;
			//return true;
		}
		temp = (-b + sqrt(b*b - a*c)) / a;
		if (temp<tmax && temp>tmin) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return 1;
			//return true;
		}
	}
	return -1;
	//return false;
}
#endif // !SPHEREH


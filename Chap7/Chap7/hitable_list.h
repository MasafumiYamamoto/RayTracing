/**/

#ifndef HITABLELISTH
#define HITABLELISTH
#include "hitable.h"

class hitable_list: public hitable
{
public:
	hitable_list() {};
	hitable_list(hitable **l, int n) { list = l; list_size = n; }
	virtual int hit(const ray& r, float t_min, float t_max, hit_record& rec)const;
	hitable **list;
	int list_size;
};

int hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec)const {
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	int object_num = -1;
	//リスト内の物体に対して衝突判定。ぶつかれば衝突点を最奥とする
	for (int i = 0; i < list_size; i++) {
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec)>=0) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
			object_num = i;
		}
	}
	return object_num;
	//return hit_anything;
}

#endif // !HITABLELISTH

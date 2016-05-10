/**
@file レイトレ本体
@brief mainと画素値を決めるcolorを含む
@detail もともとは書き出しファイルが定義されていないためにwriting_fileを追加
*/

#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"

#include <fstream>

sphere a = sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));//手前のボール
sphere b = sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0)));//奥の丘
sphere c = sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2),1));
sphere d = sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 1));

vec3 color(const ray& r,hitable *world,int depth) {
	hit_record rec;
	bool flag;
	int object_num;
	object_num = world->hit(r, 0.0001, FLT_MAX, rec);
	if (object_num >= 0) {
		ray scattered;
		vec3 attenuation;
		if (object_num == 0) {
			rec.mat_ptr = a.mat;
		}
		else if(object_num==1){
			rec.mat_ptr = b.mat;
		}
		else if (object_num == 2) {
			rec.mat_ptr = c.mat;
		}
		else {
			rec.mat_ptr = d.mat;
		}
		//rec.mat_ptr = world[objectnum];
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation*color(scattered, world, depth + 1);
		}
		else {
			return vec3(0, 0, 0);
		}
	}
	else {
		//衝突しなければ特に処理せずに描画
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
	}
}

int main() {
	std::ofstream writing_file;
	writing_file.open("chap7_.ppm");
	int nx = 200;
	int ny = 100;
	int ns = 100;
	writing_file << "P3\n" << nx << " " << ny << "\n255\n";

	hitable *list[4];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));//手前のボール
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));//奥の丘
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2),0.3));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8),0.3));
	hitable *world = new hitable_list(list, 4);
	camera cam;

	//左上から右下へ
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				ray r = cam.ray_get(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
			}
			col /= float(ns);
			//col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			writing_file << ir << " " << ig << " " << ib << "\n";
		}
	}
}
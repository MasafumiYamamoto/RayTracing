/*
ÉJÉÅÉâÉNÉâÉX
*/
#pragma once
#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera
{
public:
	camera() {
		lower_left_camera = vec3(-2, -1, -1);
		horizontal = vec3(4.0, 0.0, 0.0);
		vertical = vec3(0.0, 2.0, 0.0);
		origin = vec3(0, 0, 0);
	}
	ray ray_get(float u, float v) {
		return ray(origin, lower_left_camera + u*horizontal + v*vertical - origin);
	}
	vec3 origin;
	vec3 lower_left_camera;
	vec3 vertical;
	vec3 horizontal;
};

#endif // !CAMERAH

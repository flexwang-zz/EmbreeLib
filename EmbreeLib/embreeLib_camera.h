#pragma once
#include <embree2\rtcore.h>
#include <embree2\rtcore_ray.h>

#include "embreeLib.h"
#include <math.h>

#ifndef M_PI
#define M_PI       (3.14159265358979323846)
#endif

#ifndef M_PI_2
#define M_PI_2     (1.57079632679489661923)
#endif
class embreeLibCamera
{
public:
    embreeLibCamera(
        const vector3f&     cam_center, 
        const vector3f&     cam_up, 
        const vector3f&     cam_lookat,
	    const float         fovx, 
        const int           width, 
        const int           height
        ):
        w(width), h(height),
        cx(width/2.f), cy(height/2.f),
        right(aim^cam_up.normalized_vector()),
        aim((cam_lookat-cam_center).normalized_vector()),
        up(right^aim),
        org(cam_center),
        px(tanf(fovx*M_PI_2/180.f)/(width/2.f)),
        dx(right*px),
        dy(-up*px)  
    {
    }

    void gen_ray(RTCRay& ray, const int x, const int y)
    {
	    ray.org[0] = org.x;
	    ray.org[1] = org.y;
	    ray.org[2] = org.z;

	    vector3f dir = (x+0.5f-cx)*dx+(y+0.5f-cy)*dy+aim;
        dir.normalize();

	    ray.dir[0] = dir.x;
	    ray.dir[1] = dir.y;
	    ray.dir[2] = dir.z;

	    ray.tnear = 0.f;
	    ray.tfar = FLT_MAX;
	    ray.geomID = RTC_INVALID_GEOMETRY_ID;
	    ray.primID = RTC_INVALID_GEOMETRY_ID;
	    ray.mask = -1;
	    ray.time = 0;
    }

private:
    const float     px;
    const float     cx, cy;
    const int       w, h;
    const vector3f  up, aim, right;
    const vector3f  org;
    const vector3f  dx, dy;
};
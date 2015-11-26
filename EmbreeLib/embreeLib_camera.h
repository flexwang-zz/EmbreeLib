#pragma once
#include <embree2\rtcore.h>
#include <embree2\rtcore_ray.h>

#include "embreeLib.h"

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
        );

    void gen_ray(RTCRay& ray, const int x, const int y) const;

private:
    const int       w, h;
    const float     cx, cy;
    const vector3f  aim, right, up;
    const vector3f  org;
    const float     px;
    const vector3f  dx, dy;
};
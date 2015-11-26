#include "embreeLib.h"
#include "embreeLib_mesh.h"
#include "embreeLib_camera.h"

#include <embree2\rtcore.h>
#include <embree2\rtcore_scene.h>
#include <embree2\rtcore_ray.h>

#include <math.h>

inline rt_result intersect(RTCScene& scene, RTCRay& ray)
{
    rt_result result;
    rtcIntersect(scene, ray);

    // Get the correspondence
    if (ray.primID != RTC_INVALID_GEOMETRY_ID || ray.tfar != FLT_MAX){
        float u = ray.u;
        float v = ray.v;
        float w = 1.f - u - v;

        result.tri_idx = ray.primID;
        result.bary = vector2f(w, u);
    }
    return result;
}

void rasterize(
    std::vector<rt_result>&         result, 
	const std::vector<vector3f>&    verts,
	const std::vector<int>&         index,
	const vector3f&                 cam_center, 
    const vector3f&                 cam_up, 
    const vector3f&                 cam_lookat,
	const float                     fovx, 
    const int                       width, 
    const int                       height)
{
    result = std::vector<rt_result>(width*height);
    rtcInit(NULL);
    RTCScene scene;
    InitMesh(scene, verts, index);
    embreeLibCamera camera(
        cam_center,
        cam_up,
        cam_lookat,
        fovx,
        width,
        height
        );
#pragma omp parallel
    for (int i=0; i<width*height; ++i) {
        int x = i%width, y = i/width;
        RTCRay ray;
        camera.gen_ray(ray, x, y);
        result[i] = intersect(scene, ray);
    }
    rtcDeleteScene(scene);
    rtcExit();
}

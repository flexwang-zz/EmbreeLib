#pragma once
#include <vector>

#include <codex_math.h>

typedef codex::math::vector::vector3<float>				vector3f;
typedef codex::math::vector::vector2<float>				vector2f;

struct rt_result
{
    rt_result():tri_idx(-1){}
    int			tri_idx;
	vector2f	bary;
};

/*
    fovx should be in degree.
*/
void rasterize(
    std::vector<rt_result>&         result, 
	const std::vector<vector3f>&    verts,
	const std::vector<int>&         index,
	const vector3f&                 cam_center, 
    const vector3f&                 cam_up, 
    const vector3f&                 cam_lookat,
	const float                     fovx,
    const int                       width, 
    const int                       height);

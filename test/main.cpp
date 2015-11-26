#include <embreeLib.h>

int main()
{
    std::vector<rt_result> result;
    const int width = 640, height = 480;
	const std::vector<vector3f>     verts;
	const std::vector<int>          index;
	const vector3f                  cam_center; 
    const vector3f                  cam_up;
    const vector3f                  cam_lookat;
	const float                     fovx = 90.f;

    rasterize(
        result,
        verts,
        index,
        cam_center,
        cam_up,
        cam_lookat,
        fovx,
        width, height
        );
}
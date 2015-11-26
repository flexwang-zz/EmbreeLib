#include <embreeLib.h>
#include "test.h"

int main()
{
    std::vector<rt_result> result;
    const int width = 10, height = 10;
    const std::vector<vector3f>     verts={{0, 0, -1}, {1, 0, -1}, {0, 1, -1}};
    const std::vector<int>          index={0, 1, 2};
	const vector3f                  cam_center(0, 0, 0); 
    const vector3f                  cam_up(0, 1, 1);
    const vector3f                  cam_lookat(0, 0, -2);
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
    print_image(
        result,
        width, height);

    print_image_uv(
        result,
        width, height);

    system("Pause");
    return 0;
}
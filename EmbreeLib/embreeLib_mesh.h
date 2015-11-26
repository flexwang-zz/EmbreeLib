#pragma once

#include "embreeLib.h"

#include <embree2\rtcore.h>

inline void InitMesh(
        RTCScene&                           scene,
        const std::vector<vector3f>&        tri_points,
        const std::vector<int>&             tri_index)
{
    // Initialize the scene
    scene = rtcNewScene(RTC_SCENE_STATIC, RTC_INTERSECT1);

    int triNum = tri_index.size()/3;
    int vertNum = tri_points.size();
    printf_s("%d tri %d vertex\n", triNum, vertNum);
    unsigned geomID = rtcNewTriangleMesh(scene, RTC_GEOMETRY_STATIC, triNum, vertNum, 1);

    // Set vertices
    float *vertex = (float *)rtcMapBuffer(scene, geomID, RTC_VERTEX_BUFFER);

    for (int vertId = 0; vertId<vertNum; vertId++){
        int local_index = vertId * 4;
        vertex[local_index]     = tri_points[vertId].x;
        vertex[local_index + 1] = tri_points[vertId].y;
        vertex[local_index + 2] = tri_points[vertId].z;
    }

    rtcUnmapBuffer(scene, geomID, RTC_VERTEX_BUFFER);

    // Set triangles
    int* index = (int *)rtcMapBuffer(scene, geomID, RTC_INDEX_BUFFER);
    memcpy_s(index, sizeof(int)*3*triNum, &tri_index[0], sizeof(int)*3*triNum);
    rtcUnmapBuffer(scene, geomID, RTC_INDEX_BUFFER);

    // Commit the scene
    rtcCommit(scene);
    printf_s("Mesh init done.\n");
}
#pragma once

#include <vector>

#include "../sdf_structs/sdf_structs.hpp"

struct Settings
{
    uint32_t spp = 1;
};


struct Camera
{
    float3 position;
    float3 target;
    
    float aspect;
    float fov;
};

class Renderer
{
public:
    Renderer(const Settings &settings) : settings(settings) {}

    ~Renderer() {}

    virtual void intersection(const float3 &ray_origin, const float3 &ray_dir, hitInfo &hit) const;
    virtual void render(uint32_t width, uint32_t height, std::vector<uint32_t> &data __attribute__((size("width*height")))) const;

    //  Kernel Slicer frontend
    virtual void CommitDeviceData() {}
    virtual void GetExecutionTime(const char* a_funcName, float a_out[4]) {} 

    Camera camera;

    Settings settings;
    std::vector<SphereSDF> spheres;
    std::vector<SierpinskiySDF> fractal_triangles;
    std::vector<ObjInfo> objinfos;
};
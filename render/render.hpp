#pragma once

#include <vector>

#include "../sdf_structs/sdf_structs.hpp"

struct Settings
{
    uint32_t spp = 1;
    float delta_ray = 0.001;
};

class Renderer
{
public:
    Renderer(const Settings &settings) : settings(settings) {}

    ~Renderer() 
    {
        objects.clear();
    }

    void load_objects(const std::vector<AbstractSDF*> &objects);
    void intersection(const float3 &ray_origin, const float3 &ray_dir, hitInfo &hit) const;
    void reduce_image(std::vector<uint32_t> &input, std::vector<uint32_t> &output);
    virtual void render(uint32_t width, uint32_t height, std::vector<uint32_t> &data __attribute__((size("width*height")))) const;

    //  Kernel Slicer frontend
    virtual void CommitDeviceData() {}
    virtual void GetExecutionTime(const char* a_funcName, float a_out[4]) {} 

protected:
    Settings settings;
    std::vector<AbstractSDF *> objects;
};
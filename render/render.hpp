#pragma once

#include <vector>

#include "../sdf_structs/sdf_structs.hpp"

class Renderer
{
public:
    Renderer() {}
    ~Renderer() 
    {
        objects.clear();
    }

    void load_objects(const std::vector<AbstractSDF*> &objects);
    void intersection(const float3 &ray_origin, const float3 &ray_dir, hitInfo &hit) const;
    virtual void render(uint32_t width, uint32_t height, std::vector<uint32_t> &data __attribute__((size("width*height")))) const;

    //  Kernel Slicer frontend
    virtual void CommitDeviceData() {}
    virtual void GetExecutionTime(const char* a_funcName, float a_out[4]) {} 

protected:
    std::vector<AbstractSDF *> objects;
};
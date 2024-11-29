#pragma once

#include <vector>

#include "../sdf_structs/sdf_structs.hpp"

class Renderer
{
public:
    Renderer(const uint32_t width, const uint32_t height) : width(width), height(height) {}
    ~Renderer() 
    {
        objects.clear();
    }

    void load_objects(const std::vector<AbstractSDF*> &objects);
    void intersection(const float3 &ray_origin, const float3 &ray_dir, hitInfo &hit) const;
    void render(std::vector<uint32_t> &data) const;

private : 
    uint32_t width;
    uint32_t height;
    std::vector<AbstractSDF*> objects;
};
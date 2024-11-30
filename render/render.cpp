#include "render.hpp"

#include <algorithm>
#include <random>
#include <iostream>

void 
Renderer::load_objects(const std::vector<AbstractSDF*> &objects)
{
    std::copy(objects.begin(), objects.end(), back_inserter(this->objects));
}

void 
Renderer::intersection(const float3 &ray_origin, const float3 &ray_dir, hitInfo &hit) const
{
    float t = 0.001, dist = 1e5;
    uint32_t iter = 1;

    const uint32_t MAX_ITER = 500;
    const float EPS = 1e-3;

    while (!hit.isHit && dist > EPS && iter < MAX_ITER)
    {
        float3 Point = ray_origin + t * ray_dir;
        float min_dist = 1e5;
        uint32_t chosen_ind = 0;

        for (int i = 0; i < objects.size(); ++i)
        {
            dist = std::abs(objects[i]->get_distance(Point));
            
            if (dist < min_dist)
            {
                min_dist = dist;
                chosen_ind = i;
            }
        }

        dist = min_dist;

        if (dist < EPS)
        {
            hit.isHit = true;
            hit.t = t;
            hit.struct_index = chosen_ind;
        }

        t += dist + EPS;
        iter++;
    }
}

void 
Renderer::render(uint32_t width, uint32_t height, std::vector<uint32_t> &data) const
{
    const float AR = (float)width / height;
    std::cout << settings.spp << std::endl;
    for (float y = -1; y <= 1; y += 2.f / height)
    {
        for (float x = -AR; x <= AR; x += 2.f * AR / width)
        {
            LiteMath::float3 P{x, y, -1};
            LiteMath::float3 ray_origin{0.f, 0.f, 0.f};
            LiteMath::float3 ray_dir = LiteMath::normalize(P - ray_origin);

            uint32_t hit_count = 0;
            float3 color_vec;

            for (int sample = 0; sample < settings.spp; ++sample)
            {
                float3 new_dir = LiteMath::normalize(ray_dir + float3(2 * AR / float(width) * (float)rand() / (float)RAND_MAX, 2 * AR / float(width) * (float)rand() / (float)RAND_MAX, 2 * AR / float(width) * (float)rand() / (float)RAND_MAX));
                hitInfo hit{};
                
                intersection(ray_origin, new_dir, hit);

                if (hit.isHit)
                {
                    hit_count++;

                    uint32_t index = hit.struct_index;
                    float3 normal = objects[index]->get_normal(ray_origin + hit.t * new_dir);

                    color_vec += 255 * LiteMath::clamp(float3{LiteMath::max(0.1f, LiteMath::dot(normal, float3{10, 10, 10}))}, 0.f, 1.f);
                }
            }

            if (hit_count)
            {
                color_vec /= hit_count;
            }
            
            uint32_t color = (uint8_t)color_vec.x << 16 | (uint8_t)color_vec.y << 8 | (uint8_t)color_vec.z;
            data[(uint32_t)((y + 1) * (float)height / 2.f) * width + (uint32_t)((x + AR) * (float)width / 2.f)] = color;
        }
    }
}
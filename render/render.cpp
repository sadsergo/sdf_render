#include "render.hpp"
#include "render_settings.hpp"

#include <random>

using namespace LiteMath;

void 
Renderer::intersection(const float3 &ray_origin, const float3 &ray_dir, hitInfo &hit) const
{
    float t = 0.001, dist = 1e5;
    uint32_t iter = 1;

    const uint32_t MAX_ITER = 500;
    const float EPS = 1e-3;

    float3 Point = ray_origin;
    
    while (!hit.isHit && iter < MAX_ITER && hmax(abs(Point)) < 200.f)
    {
        Point = ray_origin + t * ray_dir;
        float min_dist = 1e5;
        ObjInfo info;

        for (int i = 0; i < objinfos.size(); ++i)
        {
            if (objinfos[i].type == SPHERE_TYPE)
            {
                SphereSDF sphere = spheres[objinfos[i].offset];
                dist = std::abs(sphere.get_distance(Point));
            }
            else if (objinfos[i].type == SIERPINSKIY_TYPE)
            {
                SierpinskiySDF tr = fractal_triangles[objinfos[i].offset];
                dist = std::abs(tr.get_distance(Point));
            }
            
            if (dist < min_dist)
            {
                min_dist = dist;
                
                info = objinfos[i];
            }
        }

        dist = min_dist;

        if (dist < EPS)
        {
            hit.isHit = true;
            hit.t = t;
            hit.objinfo = info;
        }

        t += dist + EPS;
        iter++;
    }
}

void 
Renderer::render(uint32_t width, uint32_t height, std::vector<uint32_t> &data) const
{
    const float AR = (float)width / height;
    float3 camera_dir = normalize(camera.target - camera.position);
    float3 up {0, 1, 0};
    float3 right = normalize(cross(camera_dir, up));
    
    up = normalize(cross(camera_dir, right));

    for (float y = 0; y < height; y++)
    {
        for (float x = 0; x < width; x++)
        {
             uint32_t hit_count = 0;
            float3 color_vec;
            
            for (int sample = 0; sample < settings.spp; ++sample)
            {
                LiteMath::float2 P{x + (float)rand() / RAND_MAX, y + (float)rand() / RAND_MAX};
                P /= float2(width, height);
                P = 2 * P - 1;

                LiteMath::float3 ray_origin = camera.position;
                LiteMath::float3 ray_dir = camera_dir + right * P.x * std::tan(camera.fov / 2) * camera.aspect + up * P.y * std::tan(camera.fov / 2);

                float3 new_dir = LiteMath::normalize(ray_dir + float3(2 * AR / float(width) * (float)rand() / (float)RAND_MAX, 2 * AR / float(width) * (float)rand() / (float)RAND_MAX, 2 * AR / float(width) * (float)rand() / (float)RAND_MAX));
                hitInfo hit{};
                
                intersection(ray_origin, new_dir, hit);

                if (hit.isHit)
                {
                    hit_count++;

                    ObjInfo info = hit.objinfo;
                    float3 normal (0, 0, 0);

                    if (info.type == SPHERE_TYPE)
                    {
                        normal = spheres[info.offset].get_normal(ray_origin + hit.t * new_dir); 
                    }
                     else if (info.type == SIERPINSKIY_TYPE)
                    {
                        normal = fractal_triangles[info.offset].get_normal(ray_origin + hit.t * new_dir); 
                    }

                    color_vec += 255 * LiteMath::clamp(float3{LiteMath::max(0.1f, LiteMath::dot(normal, float3{10, 10, 10}))}, 0.f, 1.f);
                    color_vec = float3{1, 1, 1} * 255.f;
                }
            }

            if (hit_count)
            {
                color_vec /= hit_count;
            }
            
            uint32_t color = (uint8_t)color_vec.x << 16 | (uint8_t)color_vec.y << 8 | (uint8_t)color_vec.z;
            data[(height - y - 1) * width + x] = color;
        }
    }
}
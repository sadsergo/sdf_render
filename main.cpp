#include <iostream>
#include <LiteMath.h>
#include <vector>

#include "bitmap.hpp"
#include "sdf_structs/sdf_structs.hpp"

using LiteMath::float3;
using LiteMath::float2;

float 
sphere_sdf(float3 P, float3 P0, float R)
{
    return LiteMath::length(P - P0) - R;
}

int
main()
{
    const uint32_t WIDTH = 500, HEIGHT = 500;
    const uint32_t MAX_ITER = 100;
    const float EPS = 1e-2;
    const float AP = (float)WIDTH / HEIGHT;

    uint32_t data[WIDTH * HEIGHT] = {};

    std::vector<AbstractSDF*> objects;
    SphereSDF* obj = new SphereSDF (float3{0, 0, -100}, 50); 
    objects.push_back(obj);

    for (float y = -1; y <= 1; y += 2.f / HEIGHT)
    {
        for (float x = -AP; x <= AP; x += 2.f * AP / WIDTH)
        {
            LiteMath::float3 P {x, y, -1};
            LiteMath::float3 ray_origin {0.f, 0.f, 0.f};
            LiteMath::float3 ray_dir = LiteMath::normalize(P - ray_origin);

            float t = 0.001, dist = 1e5;
            uint32_t iter = 1;

            while (dist > EPS && iter < MAX_ITER)
            {
                float3 Point = ray_origin + t * ray_dir;
                dist = std::abs(objects[0]->get_distance(Point));
                // std::cout << dist << std::endl;

                if (dist < EPS)
                {
                    float3 normal = objects[0]->get_normal(Point);

                    float3 color_vec = 255 * LiteMath::clamp(float3 {LiteMath::max(0.1f, LiteMath::dot(normal, float3 {10, 10, 10}))}, 0.f, 1.f);
                    uint32_t color =  (uint8_t)color_vec.x << 16 | (uint8_t)color_vec.y << 8 | (uint8_t)color_vec.z;
                    
                    data[(int)((y + 1) * (float)HEIGHT / 2.f) * WIDTH + (int)((x + AP) * (float)WIDTH / 2.f)] = color;
                }
                
                t += dist + EPS;
                iter++;
            }
        }
    }

    std::string name = "output.bmp";  
    SaveBMP(name.c_str(), data, WIDTH, HEIGHT);

    return 0;
}
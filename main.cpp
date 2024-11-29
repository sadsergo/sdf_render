#include <iostream>
#include <LiteMath.h>

#include "bitmap.hpp"

using LiteMath::float3;
using LiteMath::float2;

float 
sphere_sdf(float3 P, float3 P0, float R)
{
    return R - LiteMath::length(P - P0);
}

float tetrahedron_sdf(float3 v0, float3 v1, float3 v2, float3 v3, float3 p)
{       
    return LiteMath::max(
        LiteMath::max(
                LiteMath::dot(p, LiteMath::normalize(v0)),
                LiteMath::dot(p, LiteMath::normalize(v1))
        ),
        LiteMath::max(
                LiteMath::dot(p, LiteMath::normalize(v2)),
                LiteMath::dot(p, LiteMath::normalize(v3))
        )
    );
}

float sierpinski_triangle_sdf(float3 v0, float3 v1, float3 v2, float3 v3, float3 p, float max_iter)
{
    for (int i = 0; i < max_iter; ++i)
    {
        p = LiteMath::abs(p);

        if (p.x + p.y > 1.0)
        {
            p.x -= 1;
            p.y -= 1;
        }
        
        if (p.y + p.z > 1.0)
        {
            p.y -= 1;
            p.z -= 1;
        }

        if (p.z + p.x > 1)
        {
            p.z -= 1;
            p.x -= 1;
        }

        p *= 2.0;
    }

    return tetrahedron_sdf(v0, v1, v2, v3, p);
}

int
main()
{
    const uint32_t WIDTH = 500, HEIGHT = 500;
    const uint32_t MAX_ITER = 100;
    const float EPS = 1e-2;
    const float AP = (float)WIDTH / HEIGHT;
    float h = 0.001;

    uint32_t data[WIDTH * HEIGHT] = {};

    float3 v0 {10, 10, -40}, v1 {-10, -10, -40}, v2 {-10, 10, -60}, v3 {10, -10, -60};

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
                dist = std::abs(sphere_sdf(Point, float3(0, 0, -100), 50));
                // dist = std::abs(tetrahedron_sdf(v0, v1, v2, v3, Point));
                // std::cout << dist << std::endl;

                if (dist < EPS)
                {
                    float3 normal = LiteMath::normalize(float3 { 
                        (sphere_sdf(Point, float3(0, 0, -100) + float3(h, 0, 0), 50) - 
                        sphere_sdf(Point, float3(0, 0, -100) + float3(-h, 0, 0), 50)) / (2 * h),
                        (sphere_sdf(Point, float3(0, 0, -100) + float3(0, h, 0), 50) - 
                        sphere_sdf(Point, float3(0, 0, -100) + float3(0, -h, 0), 50)) / (2 * h),
                        (sphere_sdf(Point, float3(0, 0, -100) + float3(0, 0, h), 50) - 
                        sphere_sdf(Point, float3(0, 0, -100) + float3(0, 0, -h), 50)) / (2 * h)
                    });

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
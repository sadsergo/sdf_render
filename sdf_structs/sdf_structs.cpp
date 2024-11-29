#include "sdf_structs.hpp"

float 
SphereSDF::get_distance(const float3 &p) const
{
    return LiteMath::length(p - position) - radius;
}


float3
SphereSDF::get_normal(const float3 &P) const
{
    float h = 0.001;

    return LiteMath::normalize(float3{
        (get_distance(P + float3(h, 0, 0)) -
         get_distance(P + float3(-h, 0, 0))) / (2 * h),
        (get_distance(P + float3(0, h, 0)) -
         get_distance(P + float3(0, -h, 0))) / (2 * h),
        (get_distance(P + float3(0, 0, h)) -
         get_distance(P + float3(0, 0, -h))) / (2 * h)});
}

void 
SphereSDF::intersection(const float3 &ray_origin, const float3 &ray_dir, hitInfo &hit) const
{
    float t = 0.001, dist = 1e5;
    uint32_t iter = 1;
    
    const uint32_t MAX_ITER = 100;
    const float EPS = 1e-2;

    while (dist > EPS && iter < MAX_ITER)
    {
        float3 Point = ray_origin + t * ray_dir;
        dist = std::abs(get_distance(Point));

        if (dist < EPS)
        {
            hit.isHit = true;
            hit.t = t;
        }

        t += dist + EPS;
        iter++;
    }
}
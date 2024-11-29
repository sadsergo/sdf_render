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
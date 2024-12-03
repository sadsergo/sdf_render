#include "sdf_structs.hpp"

using namespace LiteMath;

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

float RoundBoxSDF::get_distance(const float3 &p) const
{
    float3 q = abs(p) - b + r;
    return length(max(float3(0.0f), q)) + min(max(q.x, max(q.y, q.z)), 0.f) - r;
}

float3
RoundBoxSDF::get_normal(const float3 &P) const
{
    float h = 0.001;

    return LiteMath::normalize(float3{
        (get_distance(P + float3(h, 0, 0)) -
         get_distance(P + float3(-h, 0, 0))) /
            (2 * h),
        (get_distance(P + float3(0, h, 0)) -
         get_distance(P + float3(0, -h, 0))) /
            (2 * h),
        (get_distance(P + float3(0, 0, h)) -
         get_distance(P + float3(0, 0, -h))) /
            (2 * h)});
}

float TorusSDF::get_distance(const float3 &p) const
{
    float2 q = float2(length(float2(p.x, p.z)) - t.x, p.y);
    return length(q) - t.y;
}

float3
TorusSDF::get_normal(const float3 &P) const
{
    float h = 0.001;

    return LiteMath::normalize(float3{
        (get_distance(P + float3(h, 0, 0)) -
         get_distance(P + float3(-h, 0, 0))) /
            (2 * h),
        (get_distance(P + float3(0, h, 0)) -
         get_distance(P + float3(0, -h, 0))) /
            (2 * h),
        (get_distance(P + float3(0, 0, h)) -
         get_distance(P + float3(0, 0, -h))) /
            (2 * h)});
}
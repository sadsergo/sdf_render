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

float 
SierpinskiySDF::get_distance(const float3 &p) const
{
    float3 a1 = float3(1,1,1);
	float3 a2 = float3(-1,-1,1);
	float3 a3 = float3(1,-1,-1);
	float3 a4 = float3(-1,1,-1);
    float3 z = p;
	float3 c;

	int n = 0;
	float dist, d;

	while (n < iterations) {
		 c = a1; dist = length(z-a1);
	        d = length(z-a2); if (d < dist) { c = a2; dist=d; }
		 d = length(z-a3); if (d < dist) { c = a3; dist=d; }
		 d = length(z-a4); if (d < dist) { c = a4; dist=d; }
		z = scale*z-c*(scale-1.0);
		n++;
	}

	return length(z) * pow(scale, float(-n));
}

float3 SierpinskiySDF::get_normal(const float3 &P) const
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
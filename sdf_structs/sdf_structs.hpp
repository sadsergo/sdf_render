#pragma once

#include <LiteMath.h>

using LiteMath::float3;

struct ObjInfo
{
    uint32_t type;
    uint32_t offset;
};

struct hitInfo
{
    float t = 0;
    ObjInfo objinfo;
    bool isHit = false;
};

struct SphereSDF
{
public:
    SphereSDF(const float3 &pos, const float R) : position(pos), radius(R) {}
    ~SphereSDF() {};

    float get_distance(const float3 &p) const;
    float3 get_normal(const float3 &P) const;

private: 
    float3 position;
    float radius;
};

struct SierpinskiySDF
{
public:
    SierpinskiySDF(const float3 &a1, const float3 &a2, const float3 &a3, const float3 &a4, int iterations, float scale) : a1(a1), a2(a2), a3(a3), a4(a4), iterations(iterations), scale(scale) {}
    ~SierpinskiySDF() {};

    float get_distance(const float3 &p) const;
    float3 get_normal(const float3 &P) const;

private:
    float3 a1;
    float3 a2;
    float3 a3;
    float3 a4;

    float scale;
    int iterations;
};

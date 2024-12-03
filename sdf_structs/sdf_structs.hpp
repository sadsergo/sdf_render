#pragma once

#include <LiteMath.h>

using namespace LiteMath;

struct ObjInfo
{
    uint32_t type;
    uint32_t offset;
};

struct hitInfo
{
    float t = 0;

    ObjInfo objinfo;
    float3 normal;
    bool isHit = false;
};

struct SphereSDF
{
public:
    SphereSDF(const float3 &pos, const float R) : position(pos), radius(R) {}
    ~SphereSDF() {}

    float get_distance(const float3 &p) const;
    float3 get_normal(const float3 &P) const;

private: 
    float3 position;
    float radius;
};

struct RoundBoxSDF
{
public:
    RoundBoxSDF(const float3 &b, const float r) : b(b), r(r) {}
    ~RoundBoxSDF() {}

    float get_distance(const float3 &p) const;
    float3 get_normal(const float3 &P) const;

private:
    float3 b;
    float r;
};

struct TorusSDF
{
public:
    TorusSDF(const float2 &t) : t(t) {}
    ~TorusSDF() {}

    float get_distance(const float3 &p) const;
    float3 get_normal(const float3 &P) const;

private:
    float2 t;
};
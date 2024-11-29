#pragma once

#include <LiteMath.h>

using LiteMath::float3;

struct AbstractSDF
{
    virtual float get_distance(const float3 &p) const;
    virtual float3 get_normal(const float3 &P) const;
};

struct SphereSDF : public AbstractSDF
{
public:
    SphereSDF(const float3 &pos, const float R) : position(pos), radius(R) {}
    ~SphereSDF();

    float get_distance(const float3 &p) const override = 0;
    float3 get_normal(const float3 &P) const override = 0;

private:
    float3 position;
    float radius;
};
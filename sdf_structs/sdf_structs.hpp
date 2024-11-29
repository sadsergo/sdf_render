#pragma once

#include <LiteMath.h>

using LiteMath::float3;

struct AbstractSDF
{
    virtual float get_distance(const float3 &p) const = 0;
    virtual float3 get_normal(const float3 &P) const = 0;
};

struct SphereSDF : public AbstractSDF
{
public:
    SphereSDF(const float3 &pos, const float R) : position(pos), radius(R) {}
    ~SphereSDF() {};

    float get_distance(const float3 &p) const override;
    float3 get_normal(const float3 &P) const override;

private:
    float3 position;
    float radius;
};
#include <iostream>
#include <vector>
#include <memory>

#include "bitmap.hpp"
#include "sdf_structs/sdf_structs.hpp"
#include "render/render.hpp"

#include "render/render_settings.hpp"

using namespace LiteMath;

int
main()
{
    const uint32_t WIDTH = 500, HEIGHT = 500;
    
    Settings settings {};
    settings.spp = 1;

    Camera camera;
    camera.position = float3(3, 0, 5);
    camera.target = float3(0, 0, 0);
    camera.aspect = (float)WIDTH / HEIGHT;
    camera.fov = M_PI / 4.0;

    Light light1 {{3, 0, 100}};
    
    std::vector<uint32_t> data(WIDTH * HEIGHT, 0);
    
    SphereSDF obj1 (float3{0, 0, 0}, 1);
    SphereSDF obj2 (float3{0, 0, 2}, 0.5);

    RoundBoxSDF obj3 (float3(0.5, 0.5, 1), 0.1);

    TorusSDF obj4 (float2(0.6, 0.3));

    auto pImpl = std::make_shared<Renderer> (settings);

    pImpl->camera = camera;

    // pImpl->roundboxes.push_back(obj3);
    // pImpl->objinfos.push_back({ROUNDBOX_TYPE, 0});

    // pImpl->toruses.push_back(obj4);
    // pImpl->objinfos.push_back({TORUS_TYPE, 0});

    pImpl->spheres.push_back(obj1);
    pImpl->spheres.push_back(obj2);

    pImpl->objinfos.push_back({SPHERE_TYPE, 0});
    pImpl->objinfos.push_back({SPHERE_TYPE, 1});

    pImpl->lights.push_back(light1);
    
    pImpl->CommitDeviceData();
    pImpl->render(WIDTH, HEIGHT, data);

    std::string name = "output.bmp";
    SaveBMP(name.c_str(), data.data(), WIDTH, HEIGHT);

    return 0;
}
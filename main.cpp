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
    settings.spp = 4;

    Camera camera;
    camera.position = float3(-100, 2, -100);
    camera.target = float3(0, 0, 0);
    camera.aspect = (float)WIDTH / HEIGHT;
    camera.fov = M_PI / 4.0;
    
    std::vector<uint32_t> data(WIDTH * HEIGHT, 0);
    
    SphereSDF obj1 (float3{0, 0, 0}, 1);
    SphereSDF obj2 (float3{0, 0, 1}, 0.5);

    SierpinskiySDF obj3 (float3{1,1,1}, float3{-1,-1,1}, float3{1,-1,-1}, float3{-1,1,-1}, 4, 2);

    auto pImpl = std::make_shared<Renderer> (settings);

    pImpl->camera = camera;

    // pImpl->spheres.push_back(obj1);
    // pImpl->spheres.push_back(obj2);

    pImpl->fractal_triangles.push_back(obj3);
    pImpl->objinfos.push_back({SIERPINSKIY_TYPE, 0});

    // pImpl->objinfos.push_back({SPHERE_TYPE, 0});
    // pImpl->objinfos.push_back({SPHERE_TYPE, 1});
    
    pImpl->CommitDeviceData();
    pImpl->render(WIDTH, HEIGHT, data);

    std::string name = "output.bmp";
    SaveBMP(name.c_str(), data.data(), WIDTH, HEIGHT);

    return 0;
}
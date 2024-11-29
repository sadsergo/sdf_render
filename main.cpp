#include <iostream>
#include <vector>
#include <memory>

#include "bitmap.hpp"
#include "sdf_structs/sdf_structs.hpp"
#include "render/render.hpp"

using LiteMath::float3;
using LiteMath::float2;

int
main()
{
    const uint32_t WIDTH = 500, HEIGHT = 500;

    std::vector<uint32_t> data(WIDTH * HEIGHT, 0);

    std::vector<AbstractSDF*> objects;
    
    SphereSDF* obj1 = new SphereSDF (float3{0, 0, -100}, 50);
    SphereSDF* obj2 = new SphereSDF(float3{0, 50, -100}, 30);
    objects.push_back(obj1);
    objects.push_back(obj2);

    auto pImpl = std::make_shared<Renderer> ();
    pImpl->CommitDeviceData();
    pImpl->load_objects(objects);
    pImpl->render(WIDTH, HEIGHT, data);

    std::string name = "output.bmp";
    SaveBMP(name.c_str(), data.data(), WIDTH, HEIGHT);

    return 0;
}
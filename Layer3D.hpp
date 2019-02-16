#ifndef layer3d
#define layer3d
#include <iostream>
#include <array3d.hpp>
using namespace std;

class Layer3D
{
    virtual void initialize() = 0;
    virtual Array3d compute(const Array3d&) = 0;
    virtual Array3d activate(const Array3d&) = 0;
    virtual Array3d forward(const Array3d&) = 0;
    virtual Array3d get_layer_err(const Array3d&, const Array3d&) = 0;
    virtual Array3d backward(const Array3d&) = 0;
    virtual void update(const Array3d&, const Array3d&, double) = 0;
};

#endif

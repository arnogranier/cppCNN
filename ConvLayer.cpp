#include "ConvLayer.hpp"

ConvLayer::ConvLayer(int, int, int, int)
{
    
};

void ConvLayer::initialize()
{
    
};

Array3d ConvLayer::compute(const Array3d&)
{
    cout << "Conv" <<endl;
    return Array3d();
};

Array3d ConvLayer::activate(const Array3d&)
{
    return Array3d();
};

Array3d ConvLayer::forward(const Array3d&)
{
    return Array3d();
};

Array3d ConvLayer::get_layer_err(const Array3d&, const Array3d&)
{
    return Array3d();
};

Array3d ConvLayer::backward(const Array3d&)
{
    return Array3d();
};

void ConvLayer::update(const Array3d&, const Array3d&, double)
{
    
};

#ifndef convlayer
#define convlayer
#include <iostream>
#include <ReLU.hpp>
#include <Layer3D.hpp>
using namespace std;


class ConvLayer : public Layer3D
{
private:
    Array3d filters;
    ReLU fun;
public:
    int F, K, S, P;
    ConvLayer(int, int, int, int);
    virtual ~ConvLayer(){};
    virtual void initialize() ;
    virtual Array3d compute(const Array3d&) ;
    virtual Array3d activate(const Array3d&) ;
    virtual Array3d forward(const Array3d&) ;
    virtual Array3d get_layer_err(const Array3d&, const Array3d&) ;
    virtual Array3d backward(const Array3d&) ;
    virtual void update(const Array3d&, const Array3d&, double)  ;   
};

#endif


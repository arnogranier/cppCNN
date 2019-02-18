#ifndef maxpoollayer
#define maxpoollayer
#include <iostream>
#include <Layer3D.hpp>
using namespace std;

class MaxPoolLayer : public Layer3D
{
public:
    int K, S;
    MaxPoolLayer(int, int);
    virtual ~MaxPoolLayer(){};
    virtual void initialize();
    virtual Array3d compute(const Array3d&) ;
    virtual Array3d activate(const Array3d&) ;
    virtual Array3d forward(const Array3d&) ;
    virtual Array3d get_layer_err(const Array3d&, const Array3d&) ;
    virtual Array3d backward(const Array3d&) ;
    virtual void update(const Array3d&, const Array3d&, double) ;    
};

#endif


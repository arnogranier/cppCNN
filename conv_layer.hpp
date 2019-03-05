#ifndef convlayer
#define convlayer
#include <iostream>
#include <relu.hpp>
#include <layer3d.hpp>
#include <list>
using namespace std;


class ConvLayer : public Layer3D
{
private:
    ReLU fun;
    uint F, K, S, P;
    uint prev_depth;
public:
    vector<Array3d> filters;
    ConvLayer(int, int, int, int, int);
    virtual ~ConvLayer(){};
    virtual void initialize() ;
    virtual Array3d compute(const Array3d&) ;
    virtual Array3d activate(const Array3d&) ;
    virtual Array3d forward(const Array3d&) ;
    virtual Array3d get_layer_err(const Array3d&, const Array3d&) ;
    virtual Array3d backward(const Array3d&, const Array3d&) ;
    virtual void update(const Array3d&, const Array3d&, double)  ; 
    virtual vector<vector<double> > get_learnable_parameters();
    virtual void set_learnable_parameters(vector<vector<double> >); 
    virtual bool is_learnable(){return true;};
};

#endif


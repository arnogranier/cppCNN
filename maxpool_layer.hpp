#ifndef maxpoollayer
#define maxpoollayer
#include <iostream>
#include <layer3d.hpp>
using namespace std;

class MaxPoolLayer : public Layer3D
{
private:
    uint F, S;
public:
    MaxPoolLayer(int, int);
    virtual ~MaxPoolLayer(){};
    virtual void initialize(){};
    virtual Array3d compute(const Array3d&) ;
    virtual Array3d activate(const Array3d&) ;
    virtual Array3d forward(const Array3d&) ;
    virtual Array3d get_layer_err(const Array3d&, const Array3d&) ;
    virtual Array3d backward(const Array3d&, const Array3d&) ;
    virtual void update(const Array3d&, const Array3d&, double){};
    virtual vector<vector<double> > get_learnable_parameters()
    {vector<vector<double> > v;return v;};
    virtual void set_learnable_parameters(vector<vector<double> > v){}; 
    virtual bool is_learnable(){return false;};
};

#endif


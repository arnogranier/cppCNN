#ifndef CPPCNN_MAXPOOL_LAYER_H_
#define CPPCNN_MAXPOOL_LAYER_H_
#include <iostream>
#include <layer3d.hpp>
using namespace std;

namespace cppcnn{
    
class MaxPoolLayer : public Layer3D
{
private:
    uint F, S;
public:
    MaxPoolLayer(int, int);
    virtual ~MaxPoolLayer(){};
    virtual void initialize(){};
    virtual Array3d compute(const Array3d&) const ;
    virtual Array3d activate(const Array3d&) const ;
    virtual Array3d forward(const Array3d&) const ;
    virtual Array3d get_layer_err(const Array3d&, const Array3d&) const ;
    virtual Array3d backward(const Array3d&, const Array3d&) const ;
    virtual void update(const Array3d&, const Array3d&, double){};
    virtual vector<vector<double> > get_learnable_parameters() const
    {vector<vector<double> > v;return v;};
    virtual void set_learnable_parameters(vector<vector<double> > v){}; 
    virtual bool is_learnable() const {return false;};
};

} // namespace

#endif // CPPCNN_MAXPOOL_LAYER_H_


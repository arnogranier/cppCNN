#ifndef CPPCNN_CONV_LAYER_H_
#define CPPCNN_CONV_LAYER_H_
#include <iostream>
#include <relu.hpp>
#include <layer3d.hpp>
#include <list>
using namespace std;

namespace cppcnn{

class ConvLayer : public Layer3D
{
private:
    ReLU fun;
    uint size_filter, num_filters, size_stride, size_padding;
    uint prev_depth;
public:
    vector<Array3d> filters;
    ConvLayer(uint, uint, uint, uint, uint);
    virtual ~ConvLayer(){};
    virtual void initialize() ;
    virtual Array3d compute(const Array3d&) const;
    virtual Array3d activate(const Array3d&) const;
    virtual Array3d forward(const Array3d&) const;
    virtual Array3d get_layer_err(const Array3d&, const Array3d&) const;
    virtual Array3d backward(const Array3d&, const Array3d&) const;
    virtual void update(const Array3d&, const Array3d&, double)  ; 
    virtual vector<vector<double> > get_learnable_parameters() const;
    virtual void set_learnable_parameters(vector<vector<double> >); 
    virtual bool is_learnable() const {return true;};
};

} // namespace

#endif // CPPCNN_CONV_LAYER_H_


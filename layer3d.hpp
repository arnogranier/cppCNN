#ifndef layer3d
#define layer3d
#include <iostream>
#include <array3d.hpp>
#include <vector>
using namespace std;


class Layer3D
{
public:
    virtual void initialize() = 0;
    virtual ~Layer3D(){};
    virtual Array3d compute(const Array3d&) = 0;
    virtual Array3d activate(const Array3d&) = 0;
    virtual Array3d forward(const Array3d&) = 0;
    virtual Array3d get_layer_err(const Array3d&, const Array3d&) = 0;
    virtual Array3d backward(const Array3d&, const Array3d&) = 0;
    virtual void update(const Array3d&, const Array3d&, double) = 0;
    virtual vector<vector<double> > get_learnable_parameters() = 0;
    virtual void set_learnable_parameters(vector<vector<double> >) = 0;
    virtual bool is_learnable() = 0;
};

#endif

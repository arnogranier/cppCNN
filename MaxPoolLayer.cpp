#include "MaxPoolLayer.hpp"

MaxPoolLayer::MaxPoolLayer(int f, int s)
{
    F=f;S=s;
};

double max(double a, double b, double c, double d){
    double out = a;
    if (b > out) out = b;
    if (c > out) out = c;
    if (d > out) out = d;
    return out;
}

Array3d MaxPoolLayer::compute(const Array3d& inputs)
{
    int n_out = (inputs.n-F)/S+1;
    int m_out = (inputs.m-F)/S+1;
    Array3d out(n_out, m_out, inputs.h);
    
    for (uint k=0;k<inputs.h;++k){
        for (int i=0;i<n_out;++i){
            for (int j=0;j<m_out;++j){
                out(i, j, k) = max(inputs(F*i, F*j, k),
                                   inputs(F*i, F*j+1, k),
                                   inputs(F*i+1, F*j, k),
                                   inputs(F*i+1, F*j+1, k)); //plus à faire sur F!=2
            }
        }
    }
    return out;
};

Array3d MaxPoolLayer::activate(const Array3d& Z)
{
    return Z;
};

Array3d MaxPoolLayer::forward(const Array3d& inputs)
{
    return compute(inputs);
};

Array3d MaxPoolLayer::get_layer_err(const Array3d& Z, const Array3d& Backwarded_error)
{
    return Backwarded_error;
};

Array3d MaxPoolLayer::backward(const Array3d& Layer_err, const Array3d& Z)
{
    Array3d out(S*(Layer_err.n-1)+F,S*(Layer_err.m-1)+F,Layer_err.h);
    for (uint k=0;k<Layer_err.h;++k){
        for (uint i=0;i<Layer_err.n;++i){
            for (uint j=0;j<Layer_err.m;++j){
                double _max = max(Z(F*i, F*j, k),
                                   Z(F*i, F*j+1, k),
                                   Z(F*i+1, F*j, k),
                                   Z(F*i+1, F*j+1, k));
                if (Z(F*i, F*j, k) == _max) out(F*i, F*j, k) = Layer_err(i,j,k);
                else if (Z(F*i, F*j+1, k) == _max) out(F*i, F*j+1, k) = Layer_err(i,j,k);
                else if (Z(F*i+1, F*j, k) == _max) out(F*i+1, F*j, k) = Layer_err(i,j,k);
                else if (Z(F*i+1, F*j+1, k) == _max) out(F*i+1, F*j+1, k) = Layer_err(i,j,k);
            }
        }
    }
    return out;
};


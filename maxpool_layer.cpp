#include "maxpool_layer.hpp"

namespace cppcnn{

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

Array3d MaxPoolLayer::compute(const Array3d& inputs) const
{
    int n_out = (inputs.height-F)/S+1;
    int m_out = (inputs.width-F)/S+1;
    
    vector<double> out;
    out.reserve(n_out*m_out*inputs.depth);
    for (uint k=0;k<inputs.depth;++k){
        for (int i=0;i<n_out;++i){
            for (int j=0;j<m_out;++j){
                out.push_back(max(inputs(F*i, F*j, k),
                                   inputs(F*i, F*j+1, k),
                                   inputs(F*i+1, F*j, k),
                                   inputs(F*i+1, F*j+1, k)));
            }
        }
    }
    return Array3d(n_out, m_out, inputs.depth, out);
};

Array3d MaxPoolLayer::activate(const Array3d& Z) const
{
    return Z;
};

Array3d MaxPoolLayer::forward(const Array3d& inputs) const
{
    return compute(inputs);
};

Array3d MaxPoolLayer::get_layer_err(const Array3d& Z,
                                    const Array3d& Backwarded_error) const
{
    return Backwarded_error;
};

Array3d MaxPoolLayer::backward(const Array3d& Delta,const Array3d& Z) const
{
    Array3d out(S*(Delta.height-1)+F,S*(Delta.width-1)+F,Delta.depth);
    out.fill_with_zeros();
    for (uint k=0;k<Delta.depth;++k){
        for (uint i=0;i<Delta.height;++i){
            for (uint j=0;j<Delta.width;++j){
                double _max = max(Z(F*i, F*j, k), Z(F*i, F*j+1, k),
                                   Z(F*i+1, F*j, k), Z(F*i+1, F*j+1, k));
                if (Z(F*i, F*j, k) == _max){
                    out(F*i, F*j, k) = Delta(i,j,k);
                }
                else if (Z(F*i, F*j+1, k) == _max){
                    out(F*i, F*j+1, k) = Delta(i,j,k);
                }
                else if (Z(F*i+1, F*j, k) == _max){
                    out(F*i+1, F*j, k) = Delta(i,j,k);
                }
                else {
                    out(F*i+1, F*j+1, k) = Delta(i,j,k);
                }
            }
        }
    }
    return out;
};

} // namespace
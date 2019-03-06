#include "relu.hpp"

namespace cppcnn{

Array3d ReLU::compute(const Array3d &X) const
{
    vector<double> out_values;
    uint out_size = X.values.size();
    out_values.reserve(out_size);
    double val;
    for (uint it=0;it<out_size;++it){
        val = X.values[it];
        out_values.push_back((val > 0.0)? val : 0.0);
    }
    return Array3d(X.height, X.width, X.depth, out_values);
}

Array3d ReLU::deriv(const Array3d &X) const
{
    vector<double> out_values;
    uint out_size = X.values.size();
    out_values.reserve(out_size);
    for (uint it=0;it<out_size;++it){
        out_values.push_back((X.values[it] > 0.0)? 1.0 : 0.0);
    }
    return Array3d(X.height, X.width, X.depth, out_values);
}

} // namespace
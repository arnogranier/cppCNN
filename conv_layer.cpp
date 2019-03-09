#include "conv_layer.hpp"

namespace cppcnn{

ConvLayer::ConvLayer(uint F, uint prev_K, uint K, uint S, uint P)
{
    size_filter = F;
    prev_depth = prev_K;
    num_filters = K;
    size_stride = S;
    size_padding = P;
    initialize();
}

void ConvLayer::initialize()
{
    for (uint it = 0 ; it < num_filters ; ++it){
        Array3d filter(size_filter, size_filter, prev_depth);
        filter.fill_with_random_normal(0.0, 3.0/(2*size_filter+prev_depth));
        filters.push_back(filter);
    }
}

Array3d ConvLayer::compute(const Array3d& inputs) const
{
    uint n_out = (inputs.height-size_filter+2*size_padding)/size_stride + 1;
    uint m_out = (inputs.width-size_filter+2*size_padding)/size_stride + 1;
    Array3d out(n_out, m_out, num_filters);
    out.fill_with_zeros();
    
    uint start_i, start_j;
    for (uint i = 0; i < n_out; ++i){
        start_i = i * size_stride;
        for (uint j = 0; j < m_out; ++j){
            start_j = j * size_stride;
            for (uint k = 0; k < num_filters; ++k){
                out(i, j, k) = inputs.convolve(filters[k], start_i, start_j);
            }
        }
    }
    return out;
}

Array3d ConvLayer::activate(const Array3d& Z) const
{
    return fun.compute(Z);
}

Array3d ConvLayer::forward(const Array3d& inputs) const
{
    return activate(compute(inputs));
}

Array3d ConvLayer::get_layer_err(const Array3d& Z,
                                 const Array3d& Backwarded_error) const
{
    return Backwarded_error * fun.deriv(Z);
}

Array3d ConvLayer::backward(const Array3d& Delta, const Array3d& Z) const
{
    uint height = Delta.height;
    uint width = Delta.width;
    
    Array3d out(size_stride*(Delta.height-1)+size_filter-2*size_padding,
                size_stride*(Delta.width-1)+size_filter-2*size_padding,
                prev_depth);
    out.fill_with_zeros();
    
    uint h_shift, w_shift, x_out, y_out;
    double err;
    Array3d filter;
    
    for (uint r = 0; r < num_filters; ++r){
        filter = filters[r];
        for (uint i=0;i<height;++i){
            h_shift = i * size_stride;
            for (uint j=0;j<width;++j){
                w_shift = j * size_stride;
                err = Delta(i,j,r);
                for (uint p=0;p<size_filter;++p){
                    x_out = p+h_shift;
                    for (uint q=0;q<size_filter;++q){
                        y_out = q+w_shift;
                        for (uint t=0;t<prev_depth;++t){
                            out(x_out,y_out,t) += filter(p,q,t)*err;
                        }
                    }
                }
            }
        }
    }
    
    return out;
}

void ConvLayer::update(const Array3d& Delta, const Array3d& Z, double lr)
{
    double temp;
    int x_out;
    uint height =Delta.height;
    uint width =Delta.width;
    for (uint p=0;p<size_filter;++p){
        for (uint q=0;q<size_filter;++q){
            for (uint t=0;t<prev_depth;++t){
                for (uint r=0;r<num_filters;++r){ 
                    temp=0;
                    for (uint i=0;i<height;++i){
                        x_out = p+ i * size_stride;
                        for (uint j=0;j<width;++j){ 
                            temp += Z(x_out, q + j * size_stride,t)*Delta(i,j,r);
                        }
                    }
                    filters[r](p,q,t) -= lr*temp;
                }
            }
        }
    }
}


vector<vector<double> > ConvLayer::get_learnable_parameters() const
{
    vector<vector<double> > parameters;
    for (auto filter:filters){
        parameters.push_back(filter.values);
    }
    return parameters;
}

void ConvLayer::set_learnable_parameters(vector<vector<double> > parameters)
{
    for (uint i=0;i<num_filters;++i){
        filters[i].values = parameters[i]; 
    }
}

} // namespace
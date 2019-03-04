#include "ConvLayer.hpp"

ConvLayer::ConvLayer(int f, int prev, int k, int s, int p)
{
    F=f;K=k;S=s;P=p;
    prev_depth=prev;
    initialize();
};

void ConvLayer::initialize()
{
    for (uint i=0;i<K;++i){
        Array3d tempfilter(F, F, prev_depth);
        tempfilter.fill_random();
        filters.push_back(tempfilter);
    }
};


Array3d ConvLayer::compute(const Array3d& inputs)
{
    
    int n_out = (inputs.n-F+2*P)/S+1;
    int m_out = (inputs.m-F+2*P)/S+1;
    Array3d out(n_out, m_out, K);
    
    for (uint k=0;k<K;++k){
        for (int i=0;i<n_out;++i){
            for (int j=0;j<m_out;++j){
                out(i, j, k) = inputs.convolve(filters[k], i*S, j*S);
            }
        }
    }
    return out;
};

Array3d ConvLayer::activate(const Array3d& Z)
{
    return fun.compute(Z);
};

Array3d ConvLayer::forward(const Array3d& inputs)
{
    return activate(compute(inputs));
};

Array3d ConvLayer::get_layer_err(const Array3d& Z, const Array3d& Backwarded_error)
{
    return Backwarded_error * fun.deriv(Z);
};

Array3d ConvLayer::backward(const Array3d& Layer_err, const Array3d& Z)
{
    Array3d out(S*(Layer_err.n-1)+F-2*P,S*(Layer_err.m-1)+F-2*P,prev_depth);
    for (uint r=0;r<S;++r){
        for (uint t=0;t<prev_depth;++t){
            for (uint i=0;i<Layer_err.n;++i){
                int h_shift = i * S;
                for (uint j=0;j<Layer_err.m;++j){
                    int w_shift = j * S;
                    for (uint p=0;p<F;++p){
                        for (uint q=0;q<F;++q){
                            out(p+h_shift,q+w_shift,t) += filters[r](p,q,t)*Layer_err(i,j,r);
                        }
                    }
                }
            }
        }
    }
    return out;
};

void ConvLayer::update(const Array3d& Layer_err, const Array3d& Z, double lr)
{
        for (uint r=0;r<S;++r){
            for (uint t=0;t<prev_depth;++t){
                for (uint i=0;i<Layer_err.n;++i){
                    int h_shift = i * S;
                    for (uint j=0;j<Layer_err.m;++j){
                        int w_shift = j * S;
                        for (uint p=0;p<F;++p){
                            for (uint q=0;q<F;++q){
                                filters[r](p,q,t) -= 0.0005*Z(p+h_shift,q+w_shift,t)*Layer_err(i,j,r);
                        }
                    }
                }
            }
        }
    }
};

#include "conv_layer.hpp"

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
    int h_shift, w_shift, x_out, y_out;
    uint n =Layer_err.n;
    uint m =Layer_err.m;
    double err;
    Array3d filter;
    for (uint r=0;r<K;++r){
        filter = filters[r];
            for (uint i=0;i<n;++i){
                h_shift = i * S;
                for (uint j=0;j<m;++j){
                    w_shift = j * S;
                    err=Layer_err(i,j,r);
                        for (uint p=0;p<F;++p){
                            x_out = p+h_shift;
                            for (uint q=0;q<F;++q){
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
};

void ConvLayer::update(const Array3d& Layer_err, const Array3d& Z, double lr)
{
    double temp;
    int x_out;
    uint n =Layer_err.n;
    uint m =Layer_err.m;
    for (uint p=0;p<F;++p){
        for (uint q=0;q<F;++q){
            for (uint t=0;t<prev_depth;++t){
                for (uint r=0;r<K;++r){ 
                    temp=0;
                    for (uint i=0;i<n;++i){
                        x_out = p+ i * S;
                        for (uint j=0;j<m;++j){ 
                            temp += Z(x_out, q + j * S,t)*Layer_err(i,j,r);
                        }
                    }
                    filters[r](p,q,t) -= lr*temp;
                }
            }
        }
    }
};


vector<vector<double> > ConvLayer::get_learnable_parameters()
{
    vector<vector<double> > parameters;
    for (auto filter:filters){
        parameters.push_back(filter.val);
    }
    return parameters;
}

void ConvLayer::set_learnable_parameters(vector<vector<double> > parameters)
{
    for (uint i=0;i<K;++i){
        filters[i].val = parameters[i]; 
    }
}
#include "FCLayer.hpp"

FCLayer::FCLayer(int l, int L)
{
    nb_in=l;
    nb_out=L;  
    initialize();
};

void FCLayer::initialize()
{
    Array2d tempW(nb_out, nb_in);
    W = std::move(tempW);
};

vector<double> FCLayer::activate(const vector<double>& z)
{
    return fun.compute(z);
};

vector<double> FCLayer::compute(const vector<double>& inputs)
{
    return W.dot(inputs);
};

vector<double> FCLayer::forward(const vector<double>& inputs)
{
    return activate(compute(inputs));
};

vector<double> FCLayer::get_layer_err(const vector<double>& z, const vector<double>& backw_err)
{
    vector<double> dz = fun.deriv(z);
    std::transform(dz.begin(), dz.end(), backw_err.begin(), dz.begin(),
              multiplies<double>());
    return dz;
};

vector<double> FCLayer::backward(const vector<double>& layer_err)
{
    vector<double> res = W.Tdot(layer_err);
    return res;
};

void FCLayer::update(const vector<double>& u, const vector<double>& v, double lr)
{
    uint usize=u.size();
    uint vsize=v.size();
    for (unsigned int i=0;i<usize;++i){
        for (unsigned int j=0;j<vsize;++j){
            W.val[i*nb_in+j] -= u[i]*v[j]*lr;
        }
    } 
};
#include "fc_layer.hpp"

namespace cppcnn{

FCLayer::FCLayer(uint _num_in, uint _num_out)
{
    num_in =_num_in;
    num_out =_num_out;  
    initialize();
};

void FCLayer::initialize()
{
    W = Array2d(num_out, num_in);
    W.fill_with_random_normal(0.0, 2.0/(num_in+num_out));
};

vector<double> FCLayer::activate(const vector<double>& z) const
{
    return fun.compute(z);
};

vector<double> FCLayer::compute(const vector<double>& inputs) const
{
    return W.dot(inputs);
};

vector<double> FCLayer::forward(const vector<double>& inputs) const
{
    return activate(compute(inputs));
};

vector<double> FCLayer::get_layer_err(const vector<double>& z,
                                      const vector<double>& backwrd_err) const
{
    vector<double> out = fun.deriv(z);
    std::transform(out.begin(), out.end(), backwrd_err.begin(), out.begin(),
                   multiplies<double>());
    return out;
};

vector<double> FCLayer::backward(const vector<double>& delta) const
{
    return W.Tdot(delta);
};

void FCLayer::update(const vector<double>& delta, const vector<double>& z,
                     double lr)
{
    uint err_size = delta.size();
    uint z_size = z.size();
    double current_err;
    for (uint i=0;i<err_size;++i){
        current_err = delta[i];
        for (uint j=0;j<z_size;++j){
            W.values[i*num_in+j] -= current_err*z[j]*lr;
        }
    } 
};

vector<double> FCLayer::get_learnable_parameters() const
{
    return W.values;
}

void FCLayer::set_learnable_parameters(vector<double> learnable_parameters)
{
    W.values = learnable_parameters;
}

} // namespace
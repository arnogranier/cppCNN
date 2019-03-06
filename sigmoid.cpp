#include "sigmoid.hpp"

namespace cppcnn{

vector<double> Sigmoid::compute(const vector<double> &v) const
{
    vector<double> vout;
    for (auto x : v) vout.push_back(1.0/(1.0+exp(x)));
    return vout;
}

vector<double> Sigmoid::deriv(const vector<double> &v) const
{
    vector<double> vout = compute(v);
    transform(vout.begin(), vout.end(), vout.begin(),
              [](double x){return x*(1.0-x) ;});
    return vout;
}

} // namespace
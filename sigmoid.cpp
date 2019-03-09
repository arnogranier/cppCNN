#include "sigmoid.hpp"

namespace cppcnn{

vector<double> Sigmoid::compute(const vector<double>& X) const
{
    vector<double> out;
    for (auto x : X) out.push_back(1.0/(1.0+exp(x)));
    return out;
}

vector<double> Sigmoid::deriv(const vector<double>& X) const
{
    vector<double> out = compute(X);
    transform(out.begin(), out.end(), out.begin(),
              [](double x){return x*(1.0-x) ;});
    return out;
}

} // namespace
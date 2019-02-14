#include "Sigmoid.hpp"

vector<double> Sigmoid::compute(const vector<double> &v)
{
    vector<double> vout;
    for (auto x : v) vout.push_back(1.0/(1.0+exp(x)));
    return vout;
}

vector<double> Sigmoid::deriv(const vector<double> &v)
{
    vector<double> vout = compute(v);
    transform(vout.begin(), vout.end(), vout.begin(), [](double x){return x*(1.0-x) ;});
    return vout;
}

vector<double> Sigmoid::deriv2(const vector<double> &already_computed_Sigmoid)
{
    vector<double> vout;
    for (auto x : already_computed_Sigmoid) vout.push_back(1-pow(x,2));
    return vout;
}
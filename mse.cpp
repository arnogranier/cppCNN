#include "mse.hpp"

vector<double> MSE::deriv(const vector<double> &x, int8_t truth)
{
    vector<double> y(10);
    y[truth] = 1.0;
    vector<double> err = x;
    transform(err.begin(), err.end(), y.begin(), err.begin(), std::minus<double>());
    return err;
}
#ifndef CPPCNN_MSE_H_
#define CPPCNN_MSE_H_

#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "loss.hpp"
using namespace std;

namespace cppcnn{

// Handling Mean Squared Error loss calculation   
class MSE : public Loss{
    
public :

    // Compute the sum of (prediction-expected)^2
    virtual double compute(const vector<double>& prediction,
                           int8_t expected_int) const;
                           
    // Compute prediction-expected elementwise
    virtual vector<double> deriv(const vector<double>& prediction,
                         int8_t expected_int) const;
                         
}; // MSE

} // namespace
#endif // CPPCNN_MSE_H_

#ifndef CPPCNN_SIGMOID_H_
#define CPPCNN_SIGMOID_H_

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

namespace cppcnn{

// Sigmoid activation function, used to activate fully-connected layers
// in this project
class Sigmoid{

    public :
    
    // sigmoid(X) = [1.0/(1.0+exp(-X_i)) for i = 1..N]
    vector<double> compute(const vector<double>& X) const;
    
    // sigmoid'(X) = sigmoid(X)*(1-sigmoid(X))
    vector<double> deriv(const vector<double>& X) const;

}; // Sigmoid

} // namespace
#endif // CPPCNN_SIGMOID_H_

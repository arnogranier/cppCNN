#ifndef CPPCNN_RELU_H_
#define CPPCNN_RELU_H_

#include <iostream>
#include <array3d.hpp>
#include <algorithm>
using namespace std;

namespace cppcnn{

// ReLU (Rectified linear unit) activation function, used in 
// convolutional layers in this project
class ReLU{
    
    public :
    
    // ReLU(X) = max(0,X) elementwise  
    Array3d compute(const Array3d& X) const;
    
    // ReLU'(X) = [1 if Xi > 0 else 0 for i = 1..N]
    Array3d deriv(const Array3d& X) const;   

}; //ReLU

} // namespace
#endif // CPPCNN_RELU_H_

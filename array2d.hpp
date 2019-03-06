#ifndef CPPCNN_ARRAY2D_H_
#define CPPCNN_ARRAY2D_H_

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <assert.h>

namespace cppcnn{

// Light implementation of matrix, only implementing useful feature to hold 
// weights for fully-connected layers
class Array2d{
    
public :
    uint num_rows, num_cols;
    std::vector<double> values;
    
    Array2d(){num_rows=0; num_cols=0;};
    Array2d(uint _num_rows, uint _num_cols);
    void print() const;
    
    Array2d& operator*=(double x);
    Array2d& operator-=(const Array2d& other_array);
    
    void fill_with_zeros();
    void fill_with_random_normal(double mean, double var);
    
    // Matrix-vector multiplication
    std::vector<double> dot(const std::vector<double>& extern_vector) const;
    
    // Compute the dot product between the transpose of this matrix and a 
    // vector, without actually storing the transpose 
    std::vector<double> Tdot(const std::vector<double>& extern_vector) const;
    
}; // array2d

} // namespace
#endif // CPPCNN_ARRAY2D_H_

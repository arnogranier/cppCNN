#ifndef CPPCNN_ARRAY3D_H_
#define CPPCNN_ARRAY3D_H_

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <assert.h>

using namespace std;

namespace cppcnn{

// Light implementation of 3d-array (cube), only implementing useful features 
// for holding weights of convolutional layers filters and images
class Array3d{
    
public:
    
    uint height, width, depth;
    vector<double> values;
    
    Array3d(uint _height, uint _width, uint _depth);
    
    Array3d(){height=0;width=0;depth=0;};
    Array3d(const Array3d & A)
        {height=A.height;width=A.width;depth=A.depth;values=A.values;};
    Array3d(uint _height, uint _width, uint _depth, vector<double> _values)
        {height=_height;width=_width;depth=_depth;values=_values;};
    Array3d operator=(const Array3d & A)
        {height=A.height;width=A.width;depth=A.depth;values=A.values;
         return *this;};
    void fill_with_random_normal(double mean, double var);
    void fill_with_zeros();
    
    inline double operator()(uint i, uint j, uint k) const 
    {return values[height*width*k+width*i+j];};
    inline double& operator()(uint i, uint j, uint k) 
    {return values[height*width*k+width*i+j];};
    
    // Resize the 3d array into a 1d vector
    vector<double> flatten() const {return values;};
    
    // Return the product of convolution of a subset of this (from top left 
    // corner at (start_i, start_j) and determined by size of the filter) 
    // and a filter (another array3d of size < to this)
    double convolve(const Array3d & filter, uint start_i, uint start_j) const;
    
    void zero_padding(uint size_padding);
    
    Array3d& operator*=(double x);
    Array3d& operator-=(const Array3d& other_array);
    Array3d& operator+=(const Array3d& other_array);
    Array3d operator*(const Array3d& other_array) const;
    
    void print();
    
}; // Array3d

} // namespace
#endif // CPPCNN_ARRAY3D_H_

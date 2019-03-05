#ifndef relu
#define relu
#include <iostream>
#include <array3d.hpp>
#include <math.h>
#include <algorithm>
using namespace std;

class ReLU{
public :
Array3d compute(const Array3d&);
Array3d deriv(const Array3d&);   
};

#endif
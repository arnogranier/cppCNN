#ifndef sigmoid
#define sigmoid
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <array3d.hpp>
using namespace std;

class Sigmoid{
public :
vector<double> compute(const vector<double>&);
vector<double> deriv(const vector<double>&);
vector<double> deriv2(const vector<double>&);

Array3d compute(const Array3d&);
Array3d deriv(const Array3d&); 
};

#endif

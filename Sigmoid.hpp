#ifndef sigmoid
#define sigmoid
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

class Sigmoid{
public :
vector<double> compute(const vector<double>&);
vector<double> deriv(const vector<double>&);
vector<double> deriv2(const vector<double>&);    
};

#endif
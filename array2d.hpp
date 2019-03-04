#ifndef array2d
#define array2d

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <assert.h>

using namespace std;

class Array2d{
private :
    uint n, m;
    
public :
    vector<double> val;
    Array2d(){n=0;m=0;};
    Array2d(uint, uint);
    void set(int, int, int, double);
    Array2d& operator*=(double);
    Array2d& operator-=(const Array2d&);
    vector<double> dot(const vector<double>&);
    vector<double> Tdot(const vector<double>&);
    
    void print();
};

#endif

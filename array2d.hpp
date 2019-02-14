#ifndef array2d

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
    Array2d(uint rows, uint cols, vector<double> v){n=rows;m=cols;val=v;};
    Array2d(const Array2d& A){n = A.n; m = A.m; val = A.val;};
    Array2d operator=(const Array2d& A){n = A.n; m = A.m; val = A.val;return *this;};
    
    Array2d(uint, uint, bool);
    
    Array2d& operator*=(double);
    Array2d& operator-=(const Array2d&);
    Array2d& operator+=(const Array2d&);
    vector<double> dot(const vector<double>&);
    vector<double> Tdot(const vector<double>&);
    
    void print();
};

#endif

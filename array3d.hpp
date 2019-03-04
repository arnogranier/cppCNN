#ifndef array3d
#define array3d

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <assert.h>

using namespace std;

class Array3d{
public:
    uint n, m, h;
    vector<double> val;
    Array3d(){n=0;m=0;h=0;};
    Array3d(const Array3d & B){n=B.n;m=B.m;h=B.h;val=B.val;};
    Array3d(uint, uint, uint);
    Array3d(uint rows, uint cols, uint height, vector<double> v){n=rows;m=cols;h=height;val=v;};
    void fill_random();
    
    double convolve(const Array3d &, int, int) const;
    
    void set(int, int, int, double);
    
    void zero_padding(int);
    Array3d operator=(const Array3d & B){n=B.n;m=B.m;h=B.h;val=B.val;return *this;};
    vector<double> flatten(){return val;};
    double operator()(uint, uint, uint) const;
    double& operator()(uint, uint, uint);
    Array3d& operator*=(double);
    Array3d& operator-=(const Array3d&);
    Array3d& operator+=(const Array3d&);
    Array3d operator*(const Array3d&) const;
    void print();
};

#endif

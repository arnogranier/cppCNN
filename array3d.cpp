#include "array3d.hpp"

Array3d::Array3d(uint rows, uint cols, uint height)
{
    n=rows;m=cols;h=height;
    uint size = n * m * h;
    val.reserve(size);
    for (uint i=0;i<size;i++){
        val.push_back(0);
    };
};

void Array3d::fill_random()
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::normal_distribution<double> distribution(0.01, 1.0/((n+m+h)));
    val.clear();
    uint size = n * m * h;
    val.reserve(size);
    for (uint i=0;i<size;i++){
        val.push_back(distribution(generator));
    }
};

void Array3d::zero_padding(int P)
{
    //todo
}

Array3d& Array3d::operator*=(double d)
{
    transform(val.begin(), val.end(), val.begin(),
              bind1st(multiplies<double>(), d));
    return *this;
};

Array3d& Array3d::operator-=(const Array3d & A)
{
    transform(val.begin(), val.end(), A.val.begin(), val.begin(),
              minus<double>());
    return *this;
};

Array3d& Array3d::operator+=(const Array3d & A)
{
    transform(val.begin(), val.end(), A.val.begin(), val.begin(),
              plus<double>());
    return *this;
};

Array3d Array3d::operator*(const Array3d & A) const
{
    Array3d out(*this);
    transform(out.val.begin(), out.val.end(), A.val.begin(), out.val.begin(),
              multiplies<double>());
    return out;
};

double Array3d::convolve(const Array3d & CONV, int start_i, int start_j) const
{
    double res = 0.0;
    assert((CONV.h == this->h));
    
    for (uint k=0;k<h;++k){
        for (uint i=0;i<CONV.n;++i){
            for (uint j=0;j<CONV.m;++j){
                res += CONV(i,j,k) * (*this)(i+start_i,j+start_j,k);
            }
        }
    }
    return res;
}


double Array3d::operator()(uint i, uint j, uint k) const
{
    return val[n*m*k+m*i+j];
}

double& Array3d::operator()(uint i, uint j, uint k)
{
    return val[n*m*k+m*i+j];
}


void Array3d::set(int i, int j, int k, double v)
{
    val[k*m*n+i*m+j] = v;
}

void Array3d::print()
{
    for (uint k=0;k<h;++k){
        for (uint i=0;i<n;i++){
            for (uint j=0;j<m;j++){
                std::cout << val[k*m*n+i*m+j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "-----" << endl;
    }
};

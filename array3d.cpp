#include "array3d.hpp"

namespace cppcnn{

Array3d::Array3d(uint rows, uint cols, uint h)
{
    height=rows;
    width=cols;
    depth=h;
}

void Array3d::fill_with_zeros(){
    uint size = height * width * depth;
    values.reserve(size);
    for (uint it=0;it<size;it++){
        values.push_back(0);
    };  
}

void Array3d::fill_with_random_normal(double mean, double var)
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::normal_distribution<double> distribution(mean, var);
    values.clear();
    uint size = height * width * depth;
    values.reserve(size);
    for (uint i=0;i<size;i++){
        values.push_back(distribution(generator));
    }
}

void Array3d::zero_padding(uint size_padding)
{
    //todo
}

Array3d& Array3d::operator*=(double d)
{
    transform(values.begin(), values.end(), values.begin(),
              bind1st(multiplies<double>(), d));
    return *this;
};

Array3d& Array3d::operator-=(const Array3d & A)
{
    assert((A.height == height) && (A.width == width) && (A.depth == depth));
    
    transform(values.begin(), values.end(), A.values.begin(), values.begin(),
              minus<double>());
    return *this;
};

Array3d& Array3d::operator+=(const Array3d & A)
{
    assert((A.height == height) && (A.width == width) && (A.depth == depth));
    
    transform(values.begin(), values.end(), A.values.begin(), values.begin(),
              plus<double>());
    return *this;
};

Array3d Array3d::operator*(const Array3d & A) const
{
    assert((A.height == height) && (A.width == width) && (A.depth == depth));
    
    Array3d out(*this);
    transform(out.values.begin(), out.values.end(), A.values.begin(),
              out.values.begin(), multiplies<double>());
    return out;
};

double Array3d::convolve(const Array3d & filter,
                         uint start_i, uint start_j) const
{
    assert((filter.depth == this->depth));
    assert((start_i+filter.height<= height) && (start_j+filter.width<= width));
    
    double res = 0.0;
    for (uint k=0;k<depth;++k){
        for (uint i=0;i<filter.height;++i){
            for (uint j=0;j<filter.width;++j){
                res += filter(i,j,k) * (*this)(i+start_i,j+start_j,k);
            }
        }
    }
    return res;
}

void Array3d::print()
{
    for (uint k=0;k<depth;++k){
        for (uint i=0;i<height;i++){
            for (uint j=0;j<width;j++){
                std::cout << values[k*width*height+i*width+j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "-----" << endl;
    }
};

} // namespace
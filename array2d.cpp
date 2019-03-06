#include "array2d.hpp"

namespace cppcnn{

Array2d::Array2d(uint _num_rows, uint _num_cols)
{
    num_rows=_num_rows;
    num_cols=_num_cols;
}

void Array2d::fill_with_zeros()
{
    values.clear();
    uint size = num_rows * num_cols;
    values.reserve(size);
    for (uint it=0;it<size;it++){
        values.push_back(0.0);
    };
}

void Array2d::fill_with_random_normal(double mean, double var)
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::normal_distribution<double> distribution(mean, var);
    values.clear();
    uint size = num_rows * num_cols;
    values.reserve(size);
    for (uint it=0;it<size;it++){
        values.push_back(distribution(generator));
    };
}

Array2d& Array2d::operator*=(double x)
{
    transform(values.begin(), values.end(), values.begin(),
              bind1st(std::multiplies<double>(), x));
    return *this;
}

Array2d& Array2d::operator-=(const Array2d & other_array)
{
    assert((other_array.num_rows == num_rows) &&
           (other_array.num_cols == num_cols));
    
    transform(values.begin(), values.end(), other_array.values.begin(),
              values.begin(), std::minus<double>());
    return *this;
}

std::vector<double> Array2d::dot(const std::vector<double>& extern_vec) const
{
    assert(extern_vec.size() == num_cols);
    
    std::vector<double> out_vector;
    out_vector.reserve(extern_vec.size());
    
    double temp;
    uint size = num_rows*num_cols;
    for (uint it=0;it<size;){
        temp = 0;
        for (auto val:extern_vec){
            temp += values[it] * val;
            ++it;
        }
        out_vector.push_back(temp);
    };
    return out_vector;
}

std::vector<double> Array2d::Tdot(const std::vector<double>& extern_vec) const
{
    assert(extern_vec.size() == num_rows);
    
    std::vector<double> out_vector;
    out_vector.reserve(extern_vec.size());
    
    double temp;
    for (uint i=0;i<num_cols;++i){
        temp = 0;
        for (uint j=0;j<num_rows;++j){
            temp += values[j*num_cols+i] * extern_vec[j];
        }
        out_vector.push_back(temp);
    };
    return out_vector;
}


void Array2d::print() const
{
    for (uint i=0;i<num_rows;i++){
        for (uint j=0;j<num_cols;j++){
            std::cout << values[i*num_cols+j] << " ";
        }
        std::cout << std::endl;
    }
}

} // namespace
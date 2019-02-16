#include "array2d.hpp"

Array2d::Array2d(uint rows, uint cols, bool initrandom)
{
    n=rows;m=cols;
    if (initrandom){
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::normal_distribution<double> distribution(0, 1.0/m);
        int size = n * m;
        val.reserve(size);
        for (int i=0;i<size;i++){
            val.push_back(distribution(generator));
        };
    }
    else{
        int size = n * m;
        val.reserve(size);
        for (int i=0;i<size;i++){
            val.push_back(0.0);
        };
    }
};

Array2d& Array2d::operator*=(double d)
{
    transform(val.begin(), val.end(), val.begin(),
              bind1st(multiplies<double>(), d));
    return *this;
};

Array2d& Array2d::operator-=(const Array2d & A)
{
    transform(val.begin(), val.end(), A.val.begin(), val.begin(),
              minus<double>());
    return *this;
};

Array2d& Array2d::operator+=(const Array2d & A)
{
    transform(val.begin(), val.end(), A.val.begin(), val.begin(),
              plus<double>());
    return *this;
};

vector<double> Array2d::dot(const vector<double>& v)
{
    vector<double> vout;
    vout.reserve(v.size());
    assert(v.size() == m);
    
    double temp;
    uint size = n*m;
    //for (vector<double>::iterator va =val.begin();va!=val.end();){
    for (uint i=0;i<size;){
        temp = 0;
        for (auto x:v){
            temp += val[i] * x;
            ++i;
        }
        vout.push_back(temp);
    };
    return vout;
}

vector<double> Array2d::Tdot(const vector<double>& v)
{
    vector<double> vout;
    vout.reserve(v.size());
    assert(v.size() == n);
    
    double temp;
    for (uint i=0;i<m;++i){
        temp = 0;
        for (uint j=0;j<n;++j){
            temp += val[j*m+i] * v[j];
        }
        vout.push_back(temp);
    };
    return vout;
}


void Array2d::print()
{
    for (uint i=0;i<n;i++){
        for (uint j=0;j<m;j++){
            std::cout << val[i*m+j] << " ";
        }
        std::cout << std::endl;
    }
};

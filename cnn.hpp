#ifndef CPPCNN_CNN_H_
#define CPPCNN_CNN_H_

#include <iostream>
#include <list>
#include <stack>
#include <iterator>
#include <ctime>
#include <fstream>

#include "array3d.hpp"
#include "db_handler.hpp"
#include "mse.hpp"
#include "fc_layer.hpp"
#include "conv_layer.hpp"
#include "maxpool_layer.hpp"
using namespace std;

namespace cppcnn{

class CNN
{
private:
    MSE loss;
    double c_lr, fd_lr;
    vector<Array3d> train_db_images;
    vector<unsigned int8_t > train_db_labels;
    vector<Array3d> test_db_images;
    vector<unsigned int8_t > test_db_labels;
public:
    list<Layer3D*> feature_detector;
    list<FCLayer> classifier;
    CNN(list<Layer3D*>, list<FCLayer>, double, double);
    void initialize();
    vector<unsigned int8_t> predict(vector<Array3d>);
    void train(uint);
    double test_accuracy();
    void set_train_db(vector<Array3d>&, vector<unsigned int8_t >&);
    void set_test_db(vector<Array3d>&, vector<unsigned int8_t >&);
    void set_db(string, string, string, string);
    friend ostream& operator<<(ostream&, const CNN&);
    friend istream& operator>>(istream&, CNN&);
    
}; // CNN

} // namespace
#endif // cppCNN_CNN_H_


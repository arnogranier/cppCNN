#ifndef _cnn
#define _cnn

#include <FCLayer.hpp>
#include <db_handler.hpp>
#include <MSE.hpp>
#include <ConvLayer.hpp>
#include <MaxPoolLayer.hpp>
#include <array3d.hpp>

#include <iostream>
#include <list>
#include <algorithm>
#include <random>
#include <stack>
#include <iterator>
#include <ctime>
#include <array>

using namespace std;

class CNN
{
private:
    list<Layer3D*> feature_detector;
    list<FCLayer> classifier;
    MSE loss;
    double c_lr, fd_lr;
    vector<Array3d> train_db_images;
    vector<unsigned int8_t > train_db_labels;
    vector<Array3d> test_db_images;
    vector<unsigned int8_t > test_db_labels;
public:
    CNN(list<Layer3D*>, list<FCLayer>, double, double);
    void initialize();
    vector<unsigned int8_t> predict(vector<Array3d>);
    void train(uint);
    double test_accuracy();
    void set_train_db(vector<Array3d>&, vector<unsigned int8_t >&);
    void set_test_db(vector<Array3d>&, vector<unsigned int8_t >&);
    void set_db(string, string, string, string);
};

#endif

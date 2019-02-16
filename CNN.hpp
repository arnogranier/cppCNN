#ifndef CNN


#include <FCLayer.hpp>
#include <db_handler.hpp>
#include <MSE.hpp>
#include <Layer3D.hpp>

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
    list<FCLayer> classifier;
    MSE loss;
    double lr;
    vector<vector<double> > train_db_images;
    vector<unsigned int8_t > train_db_labels;
    vector<vector<double> > test_db_images;
    vector<unsigned int8_t > test_db_labels;
public:
    CNN(list<FCLayer>, double);
    void initialize();
    vector<unsigned int8_t> feedforward(vector<vector<double> >);
    void train(uint);
    double test_accuracy();
    void set_train_db(vector<vector<double> >&, vector<unsigned int8_t >&);
    void set_test_db(vector<vector<double> >&, vector<unsigned int8_t >&);
    void set_db(string, string, string, string);
};

#endif

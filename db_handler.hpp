#ifndef db_handler
#include <vector>
#include <fstream>
#include <math.h>
#include <assert.h>
#include <iostream>
using namespace std;

class DBHandler
{
public:
    vector<vector<double> > read_mnist_image(string);
    vector<unsigned int8_t> read_mnist_label(string);
};

void show_image(vector<double>);
#endif

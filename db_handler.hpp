#ifndef db_handler
#include <vector>
#include <fstream>
#include <assert.h>
#include <math.h>
#include <iostream>
using namespace std;

class DBHandler
{
public:
    vector<vector<unsigned int8_t> > read_mnist_image(string);
    vector<unsigned int8_t > read_mnist_label(string);
};
#endif

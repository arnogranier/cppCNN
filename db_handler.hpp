#ifndef db_handler
#define db_handler
#include <vector>
#include <fstream>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <array3d.hpp>
using namespace std;

class DBHandler
{
public:
    vector<Array3d> read_mnist_image(string);
    vector<unsigned int8_t> read_mnist_label(string);
};

void show_image(Array3d);
#endif

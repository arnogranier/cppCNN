#ifndef CPPCNN_DB_HANDLER_H_
#define CPPCNN_DB_HANDLER_H_
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

#endif //CPPCNN_DB_HANDLER_H_

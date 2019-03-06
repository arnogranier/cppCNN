#ifndef CPPCNN_DB_HANDLER_H_
#define CPPCNN_DB_HANDLER_H_
#include <vector>
#include <fstream>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <array3d.hpp>
using namespace std;

namespace cppcnn{

// Handle the MNIST database 
// the database can be found on http://yann.lecun.com/exdb/mnist/
// together with an explanation on the file formats
class MNIST_DBHandler
{

public:    
    vector<Array3d> read_mnist_image(string) const;
    vector<unsigned int8_t> read_mnist_label(string) const;

}; // MNIST_DBHandler

void show_image(Array3d);

} // namespace
#endif // CPPCNN_DB_HANDLER_H_

#include <iostream>
#include <db_handler.hpp>
using namespace std;

int main()
{
    string filename_im = "../../MNIST/t10k-images.idx3-ubyte";
    DBHandler db;
    vector<vector<unsigned int8_t> > vec = db.read_mnist_image(filename_im);
    cout<<vec.size()<<endl;
    for (int y=0; y<28; ++y) {
        for (int x=0; x<28; ++x) {
            std::cout << ((vec[0][y*28+x] == 0)? ' ' : '*');
        }
        std::cout << std::endl;
    }
    string filename_l = "../../MNIST/t10k-labels-idx1-ubyte";
    vector<unsigned int8_t> labels = db.read_mnist_label(filename_l);
    std::cout << labels[0];
    return 0;
}
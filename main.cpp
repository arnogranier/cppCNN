#include <iostream>
#include <db_handler.hpp>
using namespace std;

void show_image(vector<double> im, int label)
{
    for (int y=0; y<28; ++y) {
        for (int x=0; x<28; ++x) {
            std::cout << ((im[y*28+x] == 0)? ' ' : '*');
        }
        std::cout << std::endl;
    }    
    std::cout << "Label : " << label << endl;
}

int main()
{
    DBHandler db;
    string filename_train_images = "../../MNIST/train-images-idx3-ubyte";
    string filename_train_labels = "../../MNIST/train-labels-idx1-ubyte";
    string filename_test_images = "../../MNIST/t10k-images-idx3-ubyte";
    string filename_test_labels = "../../MNIST/t10k-labels-idx1-ubyte";
    
    vector<vector<double> > vec = db.read_mnist_image(filename_train_images);
    vector<unsigned int8_t> labels = db.read_mnist_label(filename_train_labels);
    cout << vec.size();
    show_image(vec[0], labels[0]);
    return 0;
}
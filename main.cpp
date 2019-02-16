#include <iostream>
#include <list>
#include <ctime>
#include <CNN.hpp>
using namespace std;

int main()
{
    
    /* * PARAMETERS * */
    
    // path to database
    string filename_train_images = "../../MNIST/train-images-idx3-ubyte";
    string filename_train_labels = "../../MNIST/train-labels-idx1-ubyte";
    string filename_test_images = "../../MNIST/t10k-images-idx3-ubyte";
    string filename_test_labels = "../../MNIST/t10k-labels-idx1-ubyte";
    
    // Classifier architecture
    // You need to build a list of FCLayer, with the syntax
    // FCLayer l(number of inputs, number of outputs)
    // list<FCLayer> layers{l1, ... ln}
    // number of inputs of the first layer must be the size of 
    // the inputs vector, 28*28 for an MNIST image for example
    // number of outputs of the last layer must be the number of classes
    FCLayer l1(28*28, 16);
    FCLayer l2(16, 10);
    list<FCLayer> layers{l1, l2};
    
    // Learning rate
    double lr = 0.1;
    
    // Number of epochs
    uint n_epoch = 1;
    
    
    /* * MAIN * */
    
    // Building the classifier
    CNN net(layers, lr);
    
    // Read and set the database
    net.set_db(filename_test_images, filename_test_labels, 
               filename_test_images, filename_test_labels);
    
    // Training phase
    net.train(n_epoch);
    
    // Accuracy test
    double acc = net.test_accuracy();
    cout << "Accuracy on test dataset: " << acc << " % " << endl;
    
    
    return 0;
}
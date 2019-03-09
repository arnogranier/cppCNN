#include <iostream>
#include <list>
#include <ctime>
#include <cnn.hpp>
#include <mse.hpp>
using namespace std;
using namespace cppcnn;
    
int main()
{
    
    // * PARAMETERS * 
    
    // path to database
    string filename_train_images = "../../MNIST/train-images-idx3-ubyte";
    string filename_train_labels = "../../MNIST/train-labels-idx1-ubyte";
    string filename_test_images = "../../MNIST/t10k-images-idx3-ubyte";
    string filename_test_labels = "../../MNIST/t10k-labels-idx1-ubyte";
    
    // Feature detector architecture
    Layer3D* f1 = new ConvLayer(5, 1, 6, 1, 0);
    Layer3D* p1 = new MaxPoolLayer(2, 2);
    Layer3D* f2 = new ConvLayer(5, 6, 16, 1, 0);
    Layer3D* p2 = new MaxPoolLayer(2, 2);
    list<Layer3D*> feature_detector{f1, p1, f2, p2};
    
    // Classifier architecture
    FCLayer l1(4*4*16, 84);
    FCLayer l2(84, 10);
    list<FCLayer> classifier{l1, l2};
    
    // Learning rates
    double classifier_lr = 0.03;
    double feature_detector_lr = 0.0003;
    
    Loss* loss = new MSE;
    
    // Number of epochs
    uint n_epoch = 1;
    
    
    // * MAIN * 
    
    // Building the network
    CNN net(feature_detector, classifier, loss,
            feature_detector_lr, classifier_lr);
    
    // Read and set the database
    MNIST_Handler database_loader;
    vector<Array3d> train_database_images = 
                     database_loader.read_mnist_image(filename_train_images);
    vector<int8_t> train_database_labels =
                    database_loader.read_mnist_label(filename_train_labels);
    vector<Array3d> test_database_images = 
                     database_loader.read_mnist_image(filename_test_images);
    vector<int8_t> test_database_labels = 
                    database_loader.read_mnist_label(filename_test_labels);
    net.set_train_database(&test_database_images, &test_database_labels);
    net.set_test_database(&test_database_images, &test_database_labels);
  
    // Training phase
    //net.train(n_epoch);
    
    // Accuracy test
    net.load("notrain");
    cout << "Accuracy on test dataset: " << net.test_accuracy() << endl;
    //net.save("notrain");
    
    for (auto pointer:feature_detector) delete pointer;
    return 0;
}
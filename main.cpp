#include <iostream>
#include <list>
#include <ctime>
#include <cnn.hpp>
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
    
    // Number of epochs
    uint n_epoch = 1;
    
    
    // * MAIN * 
    
    // Building the network
    CNN net(feature_detector, classifier, classifier_lr, feature_detector_lr);
    
    // Read and set the database
    net.set_db(filename_test_images, filename_test_labels, 
               filename_test_images, filename_test_labels); 
  
    // Training phase
    clock_t t;
    t = clock();
    net.train(n_epoch);
    cout << 1000*(clock()-t)/CLOCKS_PER_SEC;
    //std::ifstream ifs("saved.txt");
    //ifs >> net;
    
    // Accuracy test
    cout << "Accuracy on test dataset: " << net.test_accuracy() << endl;
    
    //std::ofstream ofs("saved.txt");
    //ofs << net;
    //ofs.close();
    
    for (auto pointer:feature_detector) delete pointer;
    return 0;
}
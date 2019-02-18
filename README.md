# cpp CNN
## Final project for [ENSTA's SIM202 course](https://synapses.ensta-paristech.fr/catalogue/2018-2019/ue/3021/SIM202-projet-de-simulation-numerique)

# **WORK IN PROGRESS ...**
A c++ implementation of Convolutional neural network, with an application on MNIST hand-written digits recognition.

You can find the proposed subject together with a brief introductive survey of CNN's theory here : [Subject](https://www.cjoint.com/doc/19_01/IADnLhx7Ve0_Arno-Granier-sujet.pdf)

## Architecture
![alt text](https://image.noelshack.com/fichiers/2019/08/1/1550521768-cppcnn-2.png)

## Example of usage
```c++
#include <iostream>
#include <list>
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
    
    // Feature detector architecture
    Layer3D* f1 = new ConvLayer(20, 3, 1, 1);
    Layer3D* p1 = new MaxPoolLayer(2, 2);
    list<Layer3D*> feature_detector{f1, p1};
    
    // Classifier architecture
    FCLayer l1(28*28, 16);
    FCLayer l2(16, 10);
    list<FCLayer> classifier{l1, l2};
    
    // Learning rate
    double lr = 0.1;
    
    // Number of epochs
    uint n_epoch = 1;
    
    
    /* * MAIN * */
    
    // Building the classifier
    CNN net(feature_detector, classifier, lr);
    
    // Read and set the database
    net.set_db(filename_test_images, filename_test_labels, 
               filename_test_images, filename_test_labels);
    
    // Training phase
    net.train(n_epoch);
    
    // Accuracy test
    double acc = net.test_accuracy();
    cout << "Accuracy on test dataset: " << acc << " % " << endl;
    
    
    for (auto pointer:feature_detector) delete pointer;
    return 0;
}
```

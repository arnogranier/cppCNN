# cpp CNN
## Final project for [ENSTA's SIM202 course](https://synapses.ensta-paristech.fr/catalogue/2018-2019/ue/3021/SIM202-projet-de-simulation-numerique)

# **WORK IN PROGRESS ...**
A c++ implementation of Convolutional neural network, with an application on MNIST hand-written digits recognition.

You can find the proposed subject together with a brief introductive survey of CNN's theory here : [Subject](https://www.cjoint.com/doc/19_01/IADnLhx7Ve0_Arno-Granier-sujet.pdf)

Currently training at 96% on a dirty implementation of LeNet after 10 epochs. (LeNet is a classical architecture for OCR introduced in _LeCun, Y., Bottou, L., Bengio, Y., & Haffner, P. (1998). Gradient-based learning applied to document recognition. Proceedings of the IEEE, 86(11), 2278-2324._ [pdf](http://www.dengfanxin.cn/wp-content/uploads/2016/03/1998Lecun.pdf) 

## To-do list:

Mandatory :
  -  clean up the code
  -  comment
  -  learnable parameters saving and retrieving 
  
Optional:
  +  minibatch learning
  +  padding
  +  parallelism (threads)
  +  easier way of passing the net architecture
  +  other optimisation methods (adam, adagrad, momentum gradient descent)
  +  cross entropy loss
  +  other applications

## Architecture
   ![alt text](https://image.noelshack.com/fichiers/2019/08/1/1550521768-cppcnn-2.png)

## Example of usage
```c++
#include <iostream>
#include <list>
#include <ctime>
#include <CNN.hpp>
using namespace std;

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
    double classifier_lr = 0.01;
    double feature_detector_lr = 0.0005;
    
    // Number of epochs
    uint n_epoch = 10;
    
    
    // * MAIN * 
    
    // Building the network
    CNN net(feature_detector, classifier, classifier_lr, feature_detector_lr);
    
    // Read and set the database
    net.set_db(filename_train_images, filename_train_labels, 
               filename_test_images, filename_test_labels);

    // Accuracy test
    double acc;
    acc = net.test_accuracy();
    cout << "Accuracy on test dataset: " << acc << " % " << endl;
    
    // Training phase
    net.train(n_epoch);
    
    // Accuracy test
    acc = net.test_accuracy();
    cout << "Accuracy on test dataset: " << acc << " % " << endl;
    
    
    for (auto pointer:feature_detector) delete pointer;

    
    return 0;
}
```

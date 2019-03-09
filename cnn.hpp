#ifndef CPPCNN_CNN_H_
#define CPPCNN_CNN_H_

#include <iostream>
#include <list>
#include <stack>
#include <iterator>
#include <ctime>
#include <fstream>
#include <assert.h>

#include "array3d.hpp"
#include "db_handler.hpp"
#include "loss.hpp"
#include "fc_layer.hpp"
#include "conv_layer.hpp"
#include "maxpool_layer.hpp"
using namespace std;

namespace cppcnn{

// Instantiate a Convolutional neural network as a feature_detector (a list
// of convolutional layers and max pooling layers) and a classifier (a list 
// of fully connected layers)
// Provide the methods for the user to interact with the network (set database,
// train, predict)
class CNN
{
    
private:
    list<Layer3D*> feature_detector;
    list<FCLayer> classifier;
    Loss* loss;
    double classifier_lr, feature_detector_lr; //learning rates
    vector<Array3d>* train_database_images;
    vector<int8_t >* train_database_labels;
    vector<Array3d>* test_database_images;
    vector<int8_t >* test_database_labels;
public:
    CNN(list<Layer3D*> _feature_detector, list<FCLayer> _classifier,
        Loss* _loss, double _feature_detector_lr, double _classifier_lr);
    
    // Call the initialize method of all layers
    void initialize();
    
    void set_train_database(vector<Array3d>* images, vector<int8_t >* labels);
    void set_test_database(vector<Array3d>* images, vector<int8_t >* labels);
    
    // Takes as input a vector if images and return the corresponding vector
    // of predicted labels
    vector<int8_t> predict(vector<Array3d> inputs);
    
    // Train the network for n_peoch epochs on the train database
    void train(uint n_peoch);
    
    // Test accuracy of the network on the test database
    double test_accuracy();
    
    // Save learnable parameters of the network into os (usually a file)
    friend ostream& operator<<(ostream& os , const CNN& net);
    void save(string name);
    
    // Retrieve learnable parameters
    friend istream& operator>>(istream& is, CNN& net);
    void load(string name);
    
}; // CNN

} // namespace
#endif // cppCNN_CNN_H_


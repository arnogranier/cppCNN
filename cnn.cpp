#include "cnn.hpp"

namespace cppcnn{
    
CNN::CNN(list<Layer3D*> _feature_detector, list<FCLayer> _classifier,
         Loss* _loss, double _feature_detector_lr, double _classifier_lr)
{
    feature_detector = _feature_detector;
    classifier = _classifier;
    loss = _loss;
    feature_detector_lr = _feature_detector_lr;
    classifier_lr = _classifier_lr;
    initialize();
}

void CNN::initialize()
{
    for (auto l:feature_detector) l->initialize();
    for (auto l:classifier) l.initialize();
}

void CNN::set_train_database(vector<Array3d>* images,
                             vector<int8_t>* labels)
{
    train_database_images = images;
    train_database_labels = labels;
};

void CNN::set_test_database(vector<Array3d>* images,
                            vector<int8_t>* labels)
{
    test_database_images = images;
    test_database_labels = labels;
}

vector<int8_t> CNN::predict(vector<Array3d> inputs)
{
    vector<int8_t> outputs;
    outputs.reserve(inputs.size());
    
    // We will use classical notation from the theory of CNN, especially for
    // this method : A is the state of a 3D Layer after activation has been
    // performed, and a is the state of a 1D layer after activation has been
    // performed
    Array3d A;
    vector<double> a;
    
    // For all image in the inputs
    for (auto image:inputs){
        
        // We forward pass the image though all feature_detector's layers
        A = image;
        for(auto l:feature_detector) A = l->forward(A);
        
        // We then flatten the output of the last 3D layer and feed it to
        // the classifier, and forward pass though all the classifier's layers
        a = A.flatten();
        for (auto l:classifier) a = l.forward(a);
        
        // The output label is just the index of the most activated neuron
        // in the last layer
        int8_t output = std::distance(a.begin(),
                                      std::max_element(a.begin(), a.end()));
        
        outputs.push_back(output);
    }
    
    return outputs;
}

void CNN::train(uint n_epoch)
{
    assert(!train_database_images.empty() && !train_database_labels.empty());
    
    // Initialize the vector of indexes that will be used to loop through
    // the train database (it will be shuffled at each epoch)
    std::random_device rd;
    std::default_random_engine generator(rd());
    uint rand_indxs[train_database_images->size()];
    std::iota(&rand_indxs[0], &rand_indxs[train_database_images->size()], 0);
    
    std::cout << "Start training for " << n_epoch << " epochs" << std::endl;
    
    // We will use classical notation from the theory of CNN, especially for
    // this method : 
    //  - z is the state of a 1D layer before activation
    //  - a is the state of a 1D layer after activation
    //  - delta is the current layer error for a 1D layer
    //  - backwrd_err is the error passed from the previous layer, before
    //    multiplying by the derivate of the activation function for a 1D layer
    //  - zs is a stack to store the state of layers before activation for 1D
    //    layers during the forward pass, they are then used in backpropagation
    // The same names are used with the first letter on uppercase for 3D layers
    stack<vector<double> > zs;
    vector<double> a, z, backwrd_err, delta;
    stack<Array3d> Zs;
    Array3d A, Z, Backwrd_err, Delta;
    
    // Loop through all epochs
    for (uint n = 0; n < n_epoch; ++n){
        std::cout << "\r" << "Epoch " << n+1 << std::flush;
        
        // Random shuffle the vector of indexes
        std::shuffle(&rand_indxs[0],&rand_indxs[train_database_images->size()],
                     generator);
        
        // Loop through all images in train database in random order
        for (const auto& i:rand_indxs){ 
            A = (*train_database_images)[i];
            
            // Forward pass the image through the feature detector, storing 
            // state of layers before activation in a stack
            Zs.push(A);
            for(auto l:feature_detector){
                Z = l->compute(A);
                Zs.push(Z);
                A = l->activate(Z);
            }
                       
            a = A.flatten();
            
            // Forward pass the image through the classifier, storing 
            // state of layers before activation in a stack 
            zs.push(a);
            for(auto &l:classifier){
                z = l.compute(a);
                zs.push(z);
                a = l.activate(z);
            }
            
            // Compute the error of the output layer
            backwrd_err = loss->deriv(a, (*train_database_labels)[i]);
            
            // Backward pass though classifier
            // For each layer we compute  the layer error from next layer 
            // (in the forward way) error, we backpropagate this error to 
            // previous layer and we update the weights of current layer
            for(list<FCLayer>::reverse_iterator l=classifier.rbegin();
                  l!=classifier.rend();++l){
                delta = l->get_layer_err(zs.top(), backwrd_err);
                zs.pop();
                backwrd_err = l->backward(delta);
                l->update(delta, zs.top(), classifier_lr);
            }
            zs.pop();
            assert(zs.empty());
            
            Array3d Backwrd_err(Zs.top().height,Zs.top().width,
                                Zs.top().depth,backwrd_err);
            
            // Backward pass though feature detector
            for(list<Layer3D*>::reverse_iterator l=feature_detector.rbegin();
                  l!=feature_detector.rend();++l){
                Delta = (*l)->get_layer_err(Zs.top(), Backwrd_err);
                Zs.pop();
                Backwrd_err = (*l)->backward(Delta, Zs.top());
                (*l)->update(Delta, Zs.top(), feature_detector_lr);
            }
            Zs.pop();
            assert(Zs.empty());
        }
    }
}

double CNN::test_accuracy()
{
    assert(!test_database_images.empty() && !test_database_labels.empty());
    
    // We compute the predicted label for all the images in the test dataset
    vector<int8_t> out = predict(*test_database_images);
    
    // We then count the percentage of good match between the predicted labels
    // and the actual given labels
    uint size = test_database_labels->size();
    uint count_good_pred = 0;
    for (uint it = 0; it < size; ++it){
        if (out[it] == (*test_database_labels)[it]){
            ++count_good_pred;
        }
    }
    
    return (double)count_good_pred/(double)size;
}

ostream& operator<<(ostream& os, const CNN& net)
{
    // Save all the learnable parameters of the network
    // Looping through all layers and writing weights to a txt file
    
    for(auto l:net.feature_detector){
        if (l->is_learnable()){
            for(auto vec:l->get_learnable_parameters()){
                for (auto param:vec){
                    os << param << '\n';
                }
            }
        }
    }
    
    for(auto l:net.classifier){
        for(auto parameter:l.get_learnable_parameters()){
            os << parameter << '\n';
        }
    }
    
    return os;
}

void CNN::save(string name)
{
    std::ofstream ofs(name+".txt");
    ofs << (*this);
    ofs.close();
}

istream& operator>>(istream& is, CNN& net)
{
    // Loading learnable parameters from a previously saved network
    // Looping though all layers in the same manner as in the saving operation,
    // reading the txt file and setting weights
    
    double p;
    vector<vector<double> > parameters3d;
    vector<double> tempvec;
    vector<double> parameters2d;
    
    vector<vector<double> > actual_parameters3d;
    vector<double> actual_parameters2d;
    
    uint n_vec, length3d, length2d;
    
    
    for(auto l:net.feature_detector){
        if (l->is_learnable()){
            actual_parameters3d = l->get_learnable_parameters();
            n_vec = actual_parameters3d.size();
            length3d = actual_parameters3d[0].size();
            parameters3d.clear();
            for(uint n=0;n<n_vec;++n){
                tempvec.clear();
                for(uint s=0;s<length3d;++s){
                    is >> p;
                    tempvec.push_back(p);
                }
                parameters3d.push_back(tempvec);
            }
            l->set_learnable_parameters(parameters3d);
        }
    }
    
    for(auto &l:net.classifier){
        actual_parameters2d = l.get_learnable_parameters();
        length2d = actual_parameters2d.size();
        parameters2d.clear();
        for(uint s=0;s<length2d;++s){
            is >> p;
            parameters2d.push_back(p);
        }
        l.set_learnable_parameters(parameters2d);
    }
    
    return is;
}

void CNN::load(string name)
{
    std::ifstream ifs(name+".txt");
    ifs >> *this;
    ifs.close();
}

} // namespace
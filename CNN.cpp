#include "CNN.hpp"

CNN::CNN(list<Layer3D*> F, list<FCLayer> L, double x)
{
    feature_detector = F;
    classifier = L;
    lr = x;
}

void CNN::set_train_db(vector<vector<double> >& ims, vector<unsigned int8_t >& labels)
{
    train_db_images = ims ; train_db_labels = labels;
};

void CNN::set_test_db(vector<vector<double> >& ims, vector<unsigned int8_t >& labels)
{
    test_db_images = ims ; test_db_labels = labels;
}

void CNN::set_db(string filename_train_images, 
                 string filename_train_labels, 
                 string filename_test_images, 
                 string filename_test_labels)
{
    DBHandler db;
    train_db_images = db.read_mnist_image(filename_train_images);
    train_db_labels = db.read_mnist_label(filename_train_labels);
    test_db_images = db.read_mnist_image(filename_test_images);
    test_db_labels = db.read_mnist_label(filename_test_labels);
}

vector<unsigned int8_t> CNN::feedforward(vector<vector<double> > inputs)
{
    vector<unsigned int8_t> outputs;
    outputs.reserve(inputs.size());
    for (vector<vector<double> >::iterator input = inputs.begin();input != inputs.end();++input){
        
        // TODO- feedforward thrugh 3d layers
        
        vector<double> A(*input);
        for (list<FCLayer>::iterator l = classifier.begin();l != classifier.end();++l){
            A = l->forward(A);
            A.shrink_to_fit();
        };
        int8_t output = std::distance(A.begin(), std::max_element(A.begin(), A.end()));
        outputs.push_back(output);
    }
    return outputs;
}

void CNN::train(uint n_epoch)
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    uint rand_indxs[train_db_images.size()];
    std::iota(&rand_indxs[0], &rand_indxs[train_db_images.size()], 0);
    std::cout<<"Start training for "<<n_epoch<<" epochs"<<std::endl;
    stack<vector<double> > zs;
    vector<double> A, z, lz, backwrd_err, layer_err;
    
    //Little test
    Array3d Aoy;
    for (auto l:feature_detector) l->compute(Aoy);
    
    for (uint n=0; n<n_epoch;++n){
        std::cout<<"\r"<<"Epoch "<<n+1<<std::flush;
        std::shuffle(&rand_indxs[0], &rand_indxs[train_db_images.size()], generator);
        
        for (const auto& i:rand_indxs){
            
            // TODO- feedforward through 3d layers
            
            A = train_db_images[i];
            zs.push(A);
            for(list<FCLayer>::iterator l=classifier.begin();
                  l!=classifier.end();++l){
                z = l->compute(A);
                zs.push(z);
                A = l->activate(z);
            }
        
            backwrd_err = loss.deriv(A, train_db_labels[i]);
            lz = zs.top();
            zs.pop();
            for(list<FCLayer>::reverse_iterator l=classifier.rbegin();
                  l!=classifier.rend();++l){
                layer_err = l->get_layer_err(lz, backwrd_err);
                lz = zs.top();
                zs.pop();
                backwrd_err = l->backward(layer_err);
                l->update(layer_err, lz, lr);
            }
            assert(zs.empty());
            
            // TODO- backpropagate and update through 3d layers
        }
    }
    std::cout<<std::endl;
}

double CNN::test_accuracy()
{
    int size = test_db_labels.size();
    vector<unsigned int8_t> out = feedforward(test_db_images);
    int count_good_pred = 0;
    for (int i=0;i<size;++i){
        if (out[i]==test_db_labels[i]){
            ++count_good_pred;
        }
    }
    return (double)count_good_pred/(double)size;
}
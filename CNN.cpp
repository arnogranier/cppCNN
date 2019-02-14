#include "CNN.hpp"

CNN::CNN(list<FCLayer> L, double x)
{
    layers = L;
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
    for (vector<vector<double> >::iterator input = inputs.begin();input != inputs.end();++input){
        vector<double> A(*input);
        for (list<FCLayer>::iterator l = layers.begin();l != layers.end();++l){
            A = (*l).forward(A);
            A.shrink_to_fit();
        };
        int8_t output;
        output = std::distance(A.begin(), std::max_element(A.begin(), A.end()));
        outputs.push_back(output);
    }
    return outputs;
}

void CNN::train(uint n_epoch)
{
    std::cout<<"Start training for "<<n_epoch<<" epochs"<<std::endl;
    for (uint n=0; n<n_epoch;++n){
        std::cout<<"\r"<<"Epoch "<<n+1<<std::flush;
        std::random_device rd;
        std::default_random_engine generator(rd());
        vector<int> rand_indxs(train_db_images.size());
        std::iota(rand_indxs.begin(), rand_indxs.end(), 0);
        std::shuffle(rand_indxs.begin(), rand_indxs.end(), generator);

        stack<vector<double> > zs;
        vector<double> A, z;
        for (vector<int>::iterator i=rand_indxs.begin();i!=rand_indxs.end();++i){
            A = train_db_images[*i];
            zs.push(A);
            for(list<FCLayer>::iterator l=layers.begin();
                  l!=layers.end();++l){
                z = (*l).compute(A);
                z.shrink_to_fit();
                zs.push(z);
                A = (*l).activate(z);
            }
        
            vector<double> backwrd_err = loss.deriv(A, train_db_labels[*i]);
            vector<double> lz = zs.top();
            zs.pop();
            vector<double> layer_err;
            for(list<FCLayer>::reverse_iterator l=layers.rbegin();
                  l!=layers.rend();++l){
                layer_err = (*l).get_layer_err(lz, backwrd_err);
                layer_err.shrink_to_fit();
                lz = zs.top();
                zs.pop();
                backwrd_err = (*l).backward(layer_err);
                
                (*l).update(layer_err, lz, lr);
            }
            assert(zs.empty());
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
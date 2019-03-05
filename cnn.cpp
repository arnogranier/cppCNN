#include "cnn.hpp"
#include <ctime>

CNN::CNN(list<Layer3D*> F, list<FCLayer> L, double x, double y)
{
    feature_detector = F;
    classifier = L;
    c_lr = x;
    fd_lr = y;
}

void CNN::set_train_db(vector<Array3d>& ims, vector<unsigned int8_t >& labels)
{
    train_db_images = ims ; train_db_labels = labels;
};

void CNN::set_test_db(vector<Array3d>& ims, vector<unsigned int8_t >& labels)
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

vector<unsigned int8_t> CNN::predict(vector<Array3d> inputs)
{
    vector<unsigned int8_t> outputs;
    outputs.reserve(inputs.size());
    Array3d A;
    vector<double> a;
    for (vector<Array3d>::iterator input = inputs.begin();input != inputs.end();++input){
        
        A = *input;
        for(auto l:feature_detector){
                A = l->forward(A);
                
            }
        a = A.flatten();
        
        for (list<FCLayer>::iterator l = classifier.begin();l != classifier.end();++l){
            a = l->forward(a);
            a.shrink_to_fit();
        };
        int8_t output = std::distance(a.begin(), std::max_element(a.begin(), a.end()));
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
    
    stack<Array3d> Zs;
    Array3d A, Z, LZ, Backwrd_err, Layer_err;
    
    stack<vector<double> > zs;
    vector<double> a, z, lz, backwrd_err, layer_err;
    
    for (uint n=0; n<n_epoch;++n){
        std::cout<<"\r"<<"Epoch "<<n+1<<std::flush;
        std::shuffle(&rand_indxs[0], &rand_indxs[train_db_images.size()], generator);
        
        for (const auto& i:rand_indxs){ 
            A = train_db_images[i];
            
            
            Zs.push(A);
            for(auto l:feature_detector){
                Z = l->compute(A);
                Zs.push(Z);
                A = l->activate(Z);
            }
            
            
            a = A.flatten();

            zs.push(a);
            for(list<FCLayer>::iterator l=classifier.begin();
                  l!=classifier.end();++l){
                z = l->compute(a);
                zs.push(z);
                a = l->activate(z);
            }
        
            backwrd_err = loss.deriv(a, train_db_labels[i]);
            
            lz = zs.top();
            zs.pop();
            for(list<FCLayer>::reverse_iterator l=classifier.rbegin();
                  l!=classifier.rend();++l){
                layer_err = l->get_layer_err(lz, backwrd_err);
                lz = zs.top();
                zs.pop();
                backwrd_err = l->backward(layer_err);
                l->update(layer_err, lz, c_lr);
            }
            assert(zs.empty());
            
            
            LZ = Zs.top();
            Zs.pop();
            
            Array3d Backwrd_err(LZ.n,LZ.m,LZ.h,backwrd_err);
            
            for(list<Layer3D*>::reverse_iterator l=feature_detector.rbegin();
                  l!=feature_detector.rend();++l){
                Layer_err = (*l)->get_layer_err(LZ, Backwrd_err);
                LZ = Zs.top();
                Zs.pop();
                Backwrd_err = (*l)->backward(Layer_err, LZ);
                (*l)->update(Layer_err, LZ, fd_lr);
            }
            assert(Zs.empty());
        }
    }
}

double CNN::test_accuracy()
{
    int size = test_db_labels.size();
    vector<unsigned int8_t> out = predict(test_db_images);
    int count_good_pred = 0;
    for (int i=0;i<size;++i){
        if (out[i]==test_db_labels[i]){
            ++count_good_pred;
        }
    }
    return (double)count_good_pred/(double)size;
}

ostream& operator<<(ostream& os, const CNN& s)
{
    for(auto l:s.feature_detector){
        if (l->is_learnable()){
            for(auto vec:l->get_learnable_parameters()){
                for (auto param:vec){
                    os << param << '\n';
                }
            }
        }
    }
    
    for(auto l:s.classifier){
        for(auto parameter:l.get_learnable_parameters()){
            os << parameter << '\n';
        }
    }
    
    return os;
}

istream& operator>>(istream& is, CNN& s)
{
    
    double p;
    vector<vector<double> > parameters3d;
    vector<double> tempvec;
    vector<double> parameters2d;
    
    vector<vector<double> > actual_parameters3d;
    vector<double> actual_parameters2d;
    
    uint n_vec, length3d, length2d;
    
    
    for(auto l:s.feature_detector){
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
    
    for(auto &l:s.classifier){
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

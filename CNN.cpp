#include "CNN.hpp"
#include "db_handler.hpp"

void CNN::set_train_db(vector<vector<double> > ims, vector<int8_t > labels)
{
    train_db_images = ims ; train_db_labels = labels;
};

void CNN::set_test_db(vector<vector<double> > ims, vector<int8_t > labels)
{
    test_db_images = ims ; test_db_labels = labels;
}

void CNN::set_db(string filename_train_images, 
                 string filename_train_labels, 
                 string filename_test_images, 
                 string filename_test_labels)
{
    DBHandler db;
    vector<vector<double> > train_db_images = db.read_mnist_image(filename_train_images);
    vector<unsigned int8_t> train_db_labels = db.read_mnist_label(filename_train_labels);
    vector<vector<double> > test_db_images = db.read_mnist_image(filename_test_images);
    vector<unsigned int8_t> test_db_labels = db.read_mnist_label(filename_test_labels);
}
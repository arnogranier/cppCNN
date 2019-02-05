#ifndef CNN

#include <iostream>
#include <vector>
using namespace std;

class CNN
{
private:
    vector<vector<double> > train_db_images;
    vector<int8_t > train_db_labels;
    vector<vector<double> > test_db_images;
    vector<int8_t > test_db_labels;
public:
    void set_train_db(vector<vector<double> >, vector<int8_t >);
    void set_test_db(vector<vector<double> >, vector<int8_t >);
    void set_db(string, string, string, string);
};

#endif

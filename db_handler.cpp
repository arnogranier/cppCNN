#include "db_handler.hpp"

int char4_to_int(char* p)
{
    return ((int)p[0]*pow(2,24)+(int)p[1]*pow(2,16)
           +(int)p[2]*pow(2,8)+(int)p[3]);
}

vector<vector<unsigned int8_t> > DBHandler::read_mnist_image(string filename)
{
    ifstream file(filename, ios::binary);
    vector<vector<unsigned int8_t> > vec;
    assert(file.is_open());
    int8_t size_of_int32 = sizeof(int32_t);
    char temphead[size_of_int32];
    file.read(temphead, size_of_int32);
    int32_t magic_number = char4_to_int(temphead);
    assert(magic_number == 0x803);
    file.read(temphead, size_of_int32);
    int32_t number_of_images = char4_to_int(temphead);
    file.read(temphead, size_of_int32);
    int32_t nrows = char4_to_int(temphead);
    file.read(temphead, size_of_int32);
    int32_t ncols = char4_to_int(temphead);
    int size=nrows*ncols;
    char* temp = new char[size];
    for(int n = 0; n < number_of_images; ++n)
    {
        vector<unsigned int8_t> im;
        file.read(temp, size);
        for(int i = 0; i < size; ++i)
        {
            im.push_back((unsigned int8_t) temp[i]);
        }
        vec.push_back(im);
    }
    delete [] temp;
    return vec;
}

vector<unsigned int8_t> DBHandler::read_mnist_label(string filename)
{
    ifstream file(filename, ios::binary);
    vector<unsigned int8_t> vec;
    assert(file.is_open());
    int8_t size_of_int32 = sizeof(int32_t);
    char temphead[size_of_int32];
    file.read(temphead, size_of_int32);
    int32_t magic_number = char4_to_int(temphead);
    assert(magic_number == 0x801);
    file.read(temphead, size_of_int32);
    int32_t number_of_labels = char4_to_int(temphead);
    int8_t size_of_byte = 8;
    char* temp = new char[1];
    for(int n = 0; n < number_of_labels; ++n)
    {
        file.read(temp, size_of_byte);
        vec.push_back((unsigned int8_t) temp[0]);
    }
    return vec;
}
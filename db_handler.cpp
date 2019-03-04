#include "db_handler.hpp"

int char4_to_int(char* p)
{
    return   (unsigned int8_t)p[0] * std::pow(2,24) 
           + (unsigned int8_t)p[1] * std::pow(2,16)
           + (unsigned int8_t)p[2] * std::pow(2,8)
           + (unsigned int8_t)p[3];
}

vector<Array3d> DBHandler::read_mnist_image(string filename)
{
    std::ifstream file(filename, ios::binary);
    vector<Array3d> vec;
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
        vector<double> im;
        file.read(temp, size);
        for(int i = 0; i < size; ++i)
        {
            im.push_back((temp[i]==0)? 0:1);
        }
        vec.push_back(Array3d(nrows, ncols, 1, im));
    }
    delete [] temp;
    return vec;
};

vector<unsigned int8_t> DBHandler::read_mnist_label(string filename)
{
    std::ifstream file(filename, ios::binary);
    vector<unsigned int8_t> vec;
    assert(file.is_open());
    int8_t size_of_int32 = sizeof(int32_t);
    char temphead[size_of_int32];
    file.read(temphead, size_of_int32);
    int32_t magic_number = char4_to_int(temphead);
    assert(magic_number == 0x801);
    file.read(temphead, size_of_int32);
    int32_t number_of_labels = char4_to_int(temphead);
    char temp;
    for(int n = 0; n < number_of_labels; ++n)
    {
        file.read(&temp, 1);
        vec.push_back((unsigned int8_t) temp);
    }
    return vec;
}

void show_image(Array3d im)
{
    for (uint y=0; y<28; ++y) {
        for (uint x=0; x<28; ++x) {
            std::cout << ((im(y,x,0) == 0)? ' ' : '*');
        }
        std::cout << std::endl;
    }    
}
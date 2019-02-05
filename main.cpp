#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>

using namespace std;

int char4_to_int(char* p)
{
    return ((int)p[0]*pow(2,24)+(int)p[1]*pow(2,16)
           +(int)p[2]*pow(2,8)+(int)p[3]);
}

vector<vector<unsigned int8_t> > read_Mnist(string filename)
{
    vector<vector<unsigned int8_t> > vec;
    ifstream file(filename, ios::binary);
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

int main()
{
    string filename = "../../MNIST/t10k-images.idx3-ubyte";
    vector<vector<unsigned int8_t> > vec = read_Mnist(filename);
    cout<<vec.size()<<endl;
    for (int y=0; y<28; ++y) {
        for (int x=0; x<28; ++x) {
            std::cout << ((vec[0][y*28+x] == 0)? ' ' : '*');
        }
        std::cout << std::endl;
    }
    return 0;
}
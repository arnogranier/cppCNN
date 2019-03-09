#include "db_handler.hpp"

namespace cppcnn{
 
// Translate a 4-length char into the corresponding int   
int char4_to_int(char* p)
{
    return   (int8_t)p[0] * std::pow(2,24) 
           + (int8_t)p[1] * std::pow(2,16)
           + (int8_t)p[2] * std::pow(2,8)
           + (int8_t)p[3];
}

vector<Array3d> MNIST_Handler::read_mnist_image(string filename) const
{
    std::ifstream file(filename, ios::binary);
    assert(file.is_open());
    
    vector<Array3d> vec;
    
    int8_t size_of_int32 = sizeof(int32_t);
    char temphead[size_of_int32];
    
    // Get magic number and assert if file format is appropriate
    file.read(temphead, size_of_int32);
    int32_t magic_number = char4_to_int(temphead);
    assert(magic_number == 0x803); (void)magic_number;
    
    // Get number of images
    file.read(temphead, size_of_int32);
    int32_t number_of_images = char4_to_int(temphead);
    
    // Get number of rows per image
    file.read(temphead, size_of_int32);
    int32_t nrows = char4_to_int(temphead);
    
    // Get number of columns per image
    file.read(temphead, size_of_int32);
    int32_t ncols = char4_to_int(temphead);
    
    
    // Get images
    
    int size=nrows*ncols;
    char* temp = new char[size];
    
    // We loop through all images
    for(int n = 0; n < number_of_images; ++n)
    {
        // Read a single image and temporary store it as a vector of double
        file.read(temp, size);
        vector<double> im;
        for(int it = 0; it < size; ++it)
        {
            im.push_back((temp[it] == 0)? 0:1);
        }
        
        // Instantiate the image as an Array3d ans store it in a vector
        vec.push_back(Array3d(nrows, ncols, 1, im));
    }
    
    delete [] temp;
    return vec;
};

vector<int8_t> MNIST_Handler::read_mnist_label(string filename) const
{
    std::ifstream file(filename, ios::binary);
    assert(file.is_open());
    
    vector<int8_t> vec;
    
    int8_t size_of_int32 = sizeof(int32_t);
    char temphead[size_of_int32];
    
    // Get magic number and assert if file format is appropriate
    file.read(temphead, size_of_int32);
    int32_t magic_number = char4_to_int(temphead);
    assert(magic_number == 0x801); (void)magic_number;
    
    // Get number of labels
    file.read(temphead, size_of_int32);
    int32_t number_of_labels = char4_to_int(temphead);
    
    // We loop through all labels and store them as 8 bits int in a vector
    char temp;
    for(int n = 0; n < number_of_labels; ++n)
    {
        file.read(&temp, 1);
        vec.push_back((int8_t) temp);
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

} // namespace
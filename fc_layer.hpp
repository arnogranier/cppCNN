#ifndef fclayer 
#define fclayer
#include <array2d.hpp>
#include <Sigmoid.hpp>
using namespace std;

class FCLayer
{
private:
    Array2d W;
    Sigmoid fun;
public:
    uint nb_in, nb_out;
    FCLayer(int, int);
    void initialize();
    vector<double> forward(const vector<double>&);
    vector<double> compute(const vector<double>&);
    vector<double> activate(const vector<double>&);
    vector<double> get_layer_err(const vector<double>&, const vector<double>&);
    vector<double> backward(const vector<double>&);
    void update(const vector<double>&, const vector<double>&, double);
};

#endif


#ifndef CPPCNN_FC_LAYER_H_
#define CPPCNN_FC_LAYER_H_
#include <array2d.hpp>
#include <sigmoid.hpp>
using namespace std;

namespace cppcnn{
    
class FCLayer
{
private:
    Sigmoid fun;
public:
    Array2d W;
    uint num_in, num_out;
    FCLayer(uint _num_in, uint _num_out);
    void initialize();
    vector<double> forward(const vector<double>& inputs) const;
    vector<double> compute(const vector<double>& inputs) const;
    vector<double> activate(const vector<double>& z) const;
    vector<double> get_layer_err(const vector<double>& z,
                                 const vector<double>& backwrd_err) const;
    vector<double> backward(const vector<double>& layer_err) const;
    void update(const vector<double>& layer_err, const vector<double>& z,
                double lr);
    vector<double> get_learnable_parameters() const;
    void set_learnable_parameters(vector<double> learnable_parameters);
    
}; //FCLayer

} // namespace
#endif // CPPCNN_FC_LAYER_H_


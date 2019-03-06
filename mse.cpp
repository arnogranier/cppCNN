#include "mse.hpp"

namespace cppcnn{

double MSE::compute(const vector<double>& prediction,
                           int8_t expected_int) const
{
    double loss=0.0;
    
    // We receive the expected result as an int between 0 and 9 (equivalent to
    // a label). The expected activation of the output layer of the network
    // is the one-hot encoding of this int. i.e for 
    // 0 : [1, 0, 0, 0, 0, 0, 0, 0, 0, 0] 
    // 3 : [0, 0, 0, 1, 0, 0, 0, 0, 0, 0]
    // etc..
    
    // Here we compute the one-hot encoding
    uint output_layer_size = prediction.size();
    vector<double> expected_vector(output_layer_size, 0.0);
    expected_vector[expected_int] = 1.0;
    
    // Compute mean squared-error
    for (uint it=0;it<output_layer_size;++it){
        loss += std::pow(prediction[it]-expected_vector[it], 2);
    }
    
    return loss;
}
    
vector<double> MSE::deriv(const vector<double>& prediction,
                          int8_t expected_int) const
{
    // Here we compute the one-hot encoding
    uint output_layer_size = prediction.size();
    vector<double> expected_vector(output_layer_size, 0.0);
    expected_vector[expected_int] = 1.0;
    
    // Gradient of mean squared errror for vector X and Y is just
    // [0.5*(X_i-Y_i) for i in 1..N]
    // We can discard the 0.5 because it does not change proportionality 
    transform(prediction.begin(), prediction.end(),
              expected_vector.begin(), expected_vector.begin(),
              std::minus<double>());
              
    return expected_vector;
}

} // namespace
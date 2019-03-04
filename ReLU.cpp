#include "ReLU.hpp"

Array3d ReLU::compute(const Array3d &v)
{
    Array3d out(v);
    for (uint i=0;i<out.val.size();++i){
        if (out.val[i] <= 0.0) out.val[i] = 0.0;
    }
    return out;
}

Array3d ReLU::deriv(const Array3d &v)
{
    Array3d out(v);
    for (uint i=0;i<out.val.size();++i){
        if (out.val[i] <= 0.0) out.val[i] = 0.0;
        else out.val[i] = 1.0;
    }
    return out;
}
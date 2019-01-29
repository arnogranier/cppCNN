
#include <iostream>
# include "header.hpp"
using namespace std;

void print (const points& P){

    cout <<"("<<P.x<<","<<P.y<<","<<P.z<<")";

}

bool equal(const points& P1 , const points& P2){

    if (P1.x != P2.x || P1.y != P2.y || P1.z != P2.z ){
        return false;
    }else{
        return true;
    }
}

#include "array3d.hpp"
#include <iostream>
using namespace std;
#include <vector>

/*****CONSTRUCTEURS ET DESTRUCTEUR*******/
Array3d::Array3d(){
    height = 0;
    width = 0;
    depth = 0;
    val = NULL;
}

Array3d::Array3d(int h , int w ,int d, double v){
    height = h;
    width = w;
    depth = d;
    val = new double ** [height];
    for (int i=0; i<height; i++){
        val[i] = new double * [width];
        for(int j=0; j<width; j ++){
            val[i][j] = new double [depth];
            for(int k=0; k<depth; k ++){
                val[i][j][k] = v;
            }
        }

    }
}

Array3d::~Array3d(){
   for(int i=0; i<height; i ++){
        for(int j=0;j<width;j++){
            delete[] val[i][j];
        }
        delete[] val[i];
    }
    delete[] val;
}

Array3d::Array3d(const Array3d & A){
    height = A.height;
    width = A.width;
    depth = A.depth;

    val = new double** [height];
    for (int i = 0; i < height; i++){
        val[i] = new double*[width];
        for (int j = 0; j < width; j++){
            val[i][j] = new double [depth];
            for(int k=0; k<depth; k ++){
                val[i][j][k] = A.val[i][j][k];
            }
        }
   }
}

Array3d::Array3d(const vector<double> & v, int h, int w, int d){
    height = h;
    width = w;
    depth = d;
    val = new double** [height];
    for (int i = 0; i < height; i++){
        val[i] = new double*[width];
        for (int j = 0; j < width; j++){
            val[i][j] = new double [depth];
            for(int k=0; k<depth; k ++){
                val[i][j][k] = v.at((i*width+j)*depth+k);
            }
        }
   }

}

vector<double> Array3d::to_vector(){
    int taille = height*width*depth;
    vector<double> v(taille);
    for (int i = 0; i < height; i++){
        val[i] = new double*[width];
        for (int j = 0; j < width; j++){
            val[i][j] = new double [depth];
            for(int k=0; k<depth; k ++){
                v.at((i*width+j)*depth+k)= val[i][j][k] ;
            }
        }
   }
   return v;
}


/****************OPERATEURS*************/
double & Array3d::operator()(int i,int j,int k)
{
  return val[i][j][k];
}

Array3d & Array3d::operator*=( double x){
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            for(int k=0; k<depth; k++){
                val[i][j][k] *= x;
            }
        }
    }
    return *this;
}

Array3d & Array3d::operator+=( double x){
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            for(int k=0; k<depth; k++){
                val[i][j][k] += x;
            }
        }
    }
    return *this;
}
Array3d & Array3d::operator-=( double x){
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            for(int k=0; k<depth; k++){
                val[i][j][k] -= x;
            }
        }
    }
    return *this;
}

Array3d & Array3d::operator/=( double x){
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            for(int k=0; k<depth; k++){
                val[i][j][k] /= x;
            }
        }
    }
    return *this;
}

Array3d & Array3d::operator+=(const Array3d &A){
   for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            for(int k=0; k<depth; k++){
                val[i][j][k] += A.val[i][j][k];
            }
        }
    }
    return *this;
}
Array3d & Array3d::operator-=(const Array3d &A){
   for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            for(int k=0; k<depth; k++){
                val[i][j][k] -= A.val[i][j][k];
            }
        }
    }
    return *this;
}

Array3d & Array3d::operator*=(const Array3d &A){
   for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            for(int k=0; k<depth; k++){
                val[i][j][k] *= A.val[i][j][k];
            }
        }
    }
    return *this;
}

bool Array3d::operator ==(const Array3d &A){
    if(height != A.height || width != A.width || depth != A.depth){
        return false;
    }
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            for(int k=0;k<depth;k++){
                if(val[i][j][k] != A.val[i][j][k]){
                    return false;
                }
            }
        }
    }
    return true;
}

bool Array3d::operator != (const Array3d &A){
    if(height != A.height || width != A.width || depth != A.depth){
        return true;
    }
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            for(int k=0;k<depth;k++){
                if(val[i][j][k] != A.val[i][j][k]){
                    return true;
                }
            }
        }
    }
    return false;
}

Array3d & Array3d::operator=(const Array3d &A){
    if(height != A.height || width != A.width || depth != A.depth) {
        for(int i=0; i<height; i ++){
            for(int j=0;j<width;j++){
                delete[] val[i][j];
            }
            delete[] val[i];
        }
        delete[] val;
    }

    height = A.height;
    width = A.width;
    depth = A.depth;
    val = new double ** [height];

    for (int i=0; i<height; i++){
        val[i] = new double * [width];
        for(int j=0; j<width; j ++){
            val[i][j] = new double [depth];
            for(int k=0; k<depth; k ++){
                val[i][j][k] = A.val[i][j][k];
            }
        }

    }
}

Array3d operator + (const Array3d &  A , double x){
    Array3d res(A);
	return (res+=x);

}
Array3d operator - (const Array3d &  A , double x){
    Array3d res(A);
	return (res-=x);
}
Array3d operator /(const Array3d &  A , double x){
    Array3d res(A);
	return (res/=x);
}
Array3d operator *(const Array3d &  A , double x){
    Array3d res(A);
	return (res*=x);
}

Array3d operator + (double x , const Array3d &  A ){
    Array3d res(A);
	return (res+x);
}
Array3d operator - (double x , const Array3d &  A){
    Array3d res(A);
	return (res-x);
}
Array3d operator *(double x , const Array3d &  A){
    Array3d res(A);
	return (res*x);
}


Array3d operator + (const Array3d & A,const Array3d & B){
    Array3d res(A);
	return (res+=B);
}
Array3d operator - (const Array3d & A,const Array3d & B){
    Array3d res(A);
	return (res-=B);
}
Array3d operator *(const Array3d &  A , const Array3d &  B){
    Array3d res(A);
	return (res*=B);
}
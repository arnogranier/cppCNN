#ifndef array3d

#include <iostream>
using namespace std;

class Array3d{
private :
    int height,width,depth;
public :

    Array3d();
    int &  operator () (int i);
    int  operator () const (int i);
    Array3d & operator + (const Array3d & A);
    Array3d & operator - (const Array3d & A);


}


Array3d & operator + (const Array3d & A,const Array3d & B);
Array3d & operator - (const Array3d & A,const Array3d & B);
Array3d operator + (const Array3d &  A , int x);
Array3d operator - (const Array3d &  A , int x);
Array3d operator /(constArray3d &  A , int x);
Array3d operator *(const Array3d &  A , int x);
Array3d operator *(const Array3d &  A , const Array3d &  B);
Array3d operator *(int x, const Array3d &  A);
bool operator ==(const Array3d & A, const Array3d & B);
bool operator !=(const Array3d & A, const Array3d & B);
#endif


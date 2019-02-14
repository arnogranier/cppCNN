#ifndef array2d

#include <iostream>
using namespace std;
#include <vector>

class Array3d{
private :
    double *** val;
    int height;
    int width;
    int depth;
public :
    //constructeurs et destructeur
    Array3d();
    Array3d(int h , int w ,int d, double v=0);
    Array3d(const Array3d & A);
    Array3d(const vector<double> & v,int h , int w ,int d);
    ~Array3d();
    //array3d to vector
    vector<double> to_vector();
    // getters and setters
    int nb_lignes() const {return height;}
    int & nb_lignes(){return height;}
    int nb_colonnes() const {return width;}
    int & nb_colonnes() {return width;}
    int profondeur() const {return depth;}
    int & profondeur() {return depth;}

    //operateurs internes
    Array3d &operator=(const Array3d &A);
    double &operator()(int i, int j, int k);
    Array3d & operator*=( double x);
    Array3d & operator+=( double x);
    Array3d & operator-=( double x);
    Array3d & operator/=( double x);
    Array3d & operator+=(const Array3d &A);
    Array3d & operator-=(const Array3d &A);
    Array3d & operator*=(const Array3d &A);
    bool operator ==(const Array3d &A);
    bool operator !=(const Array3d &A);
};


//operateurs externes
Array3d operator + (const Array3d &  A , double x);
Array3d operator - (const Array3d &  A , double x);
Array3d operator /(const Array3d &  A , double x);
Array3d operator *(const Array3d &  A , double x);

Array3d operator + (double x , const Array3d &  A );
Array3d operator - (double x , const Array3d &  A);
Array3d operator *(double x , const Array3d &  A);


Array3d operator + (const Array3d & A,const Array3d & B);
Array3d operator - (const Array3d & A,const Array3d & B);
Array3d operator *(const Array3d &  A , const Array3d &  B);



#endif


#ifndef array2d

#include <iostream>
using namespace std;
#include <vector>

class Array2d{
private :
    double ** val;
    int height; //nombre de lignes
    int width; //nombre de colonnes
public :
    //constructeurs et destructeur
    Array2d();
    Array2d(int h , int w , double v=0);
    Array2d( const Array2d & A);
    ~Array2d();
    // getters and setters
    int nb_lignes() const {return height;}
    int & nb_lignes(){return height;}
    int nb_colonnes() const {return width;}
    int & nb_colonnes() {return width;}
    //operateurs internes
    Array2d &operator=(const Array2d &A);
    double &operator()(int i, int j);
    friend Array2d operator*( double d,const Array2d &A);
    Array2d & operator*=( double d);
    Array2d & operator+=( double d);
    Array2d & operator-=( double d);
    Array2d & operator/=( double d);
    Array2d & operator+=(const Array2d &A);
    Array2d & operator-=(const Array2d &A);
    Array2d & operator*=(const Array2d &A);
    bool operator ==(const Array2d &A);
    bool operator !=(const Array2d &A);
    friend ostream & operator<<(ostream &os,const Array2d &A);

};


//operateurs externes
Array2d operator + (const Array2d &  A , double x);
Array2d operator - (const Array2d &  A , double x);
Array2d operator /(const Array2d &  A , double x);
Array2d operator *(const Array2d &  A , double x);

Array2d operator + (double x , const Array2d &  A );
Array2d operator - (double x , const Array2d &  A);
Array2d operator *(double x , const Array2d &  A);


Array2d & operator + (const Array2d & A,const Array2d & B);
Array2d & operator - (const Array2d & A,const Array2d & B);
Array2d operator *(const Array2d &  A , const Array2d &  B);



#endif

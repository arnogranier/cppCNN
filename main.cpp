#include "MaillageH.hpp"
int main()
{
  //test de la classe Point
  //Point O, P(0,1), Q(1,1), R(1);
  //Point A = O+P+2.*Q-R/2.;
  //cout<<"O+P+2.*Q-R/2.="<<A <<endl;
  //cout<<"O!=P -> "<<(O!=P)<<"O==P -> "<<(O==P)<<endl;

  Maillage mail(3,2);
  Maillage mail2(3,3,8,8,11,11);
  Maillage mail3 = mail+mail2;
  mail3.affiche();
}

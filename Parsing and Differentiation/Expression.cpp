#include "Expression.h"

using namespace std;



void Expression::psevd_Const(string sign){
   this->p=nullptr;
   this->sign=sign;
};
Expression::~Expression(){
  delete [] p;
};
Expression** Expression:: get_p(){
        return this->p;
      };

      
string Expression:: get_sign(){
        return this->sign;
      };      
string Expression:: get_sign_constantly()const{
        string copy=this->sign;
        return copy;
      };      
Expression** Expression:: get_p_constantly() const{
        return this->p;
      };

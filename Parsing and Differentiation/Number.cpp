#include "Number.h"
   void Number::Copy(Expression const * exp) {  
         psevd_Const(exp->get_sign_constantly()) ;
       };
    void Number:: Clean(){
         p[0]->Clean();
         delete [] p;
      };
      /*Конструкторы*/
     Number:: Number(double exp_1){
         this->psevd_Const(to_string(exp_1)) ;     
      };
     Number:: Number(string exp_1){
         this->psevd_Const(exp_1) ;     
      };
      /*Конструктор копирования*/
     Number:: Number(Number const& exp){
        if(this!=&(exp)){
            Clean();
        }
        this->Copy(&exp);
      };
     Number::~Number(){
        Clean();
      };



     /*Перегрузка оператора присваивания*/
     Number& Number:: operator=(Number const& B){
         this->Clean();
         this->Copy(&B);
        return *this;
     }


      /*Метод дифференцирования, который является основополагающим для задачи вообще*/
      Expression* Number:: derivative(string variable){
            Expression* exp=new Number("0");
            return exp;
      };
       
      void Number:: print() const{
        cout<<sign;
      };
     double Number::eval(string meaning){
        return ::atof(this->sign.c_str());
        /*double temp = ::atof(    .c_str());*/
     };
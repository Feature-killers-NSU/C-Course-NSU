#include "Div.h"
      /*Методы Copy() и Clean() для конструктора копирования и деструктора, к сожалению не получилось спрятать в приватные или защищенные*/
      void Div:: Copy( Expression const * exp){  
           p[0]->Copy(exp->get_p_constantly()[0]);
           p[1]->Copy(exp->get_p_constantly()[1]);
       };
      void Div::Clean(){
          
           p[0]->Clean();
           p[1]->Clean();
           delete [] p;
      };
      /*Конструкторы*/
      Div::Div(Expression* exp_1,Expression*exp_2){
         p=new Expression*[2];
         p[0]=exp_1;
         p[1]=exp_2;
         this->sign="/";
      };
      /*Конструктор копирования*/
     Div:: Div(Div const& exp){
        if(this!=&(exp)){
            Clean();
        }
        this->Copy(&exp);
        this->sign="*";
      };
      Div::~Div(){
        Clean();
      };



     /*Перегрузка оператора присваивания*/
    Div& Div::operator=(Div const& B){
         this->Clean();
         this->Copy(&B);
        return *this;
     }


      /*Метод дифференцирования, который является основополагающим для Задачи вообще*/
      Expression* Div:: derivative(string variable){
           Expression* exp=new Div(new Sub(new Mul(p[0]->derivative(variable),p[1]),new Mul(p[0],p[1]->derivative(variable))),new Mul(p[1],p[1]));
            return exp;
      };
    void Div::print() const{
        cout<<"(";
        p[0]->print();
        cout<<sign;
        p[1]->print();
        cout<<")";
    };
   double Div::eval(string meaning){
     return p[0]->eval(meaning)/p[1]->eval(meaning);
   };  
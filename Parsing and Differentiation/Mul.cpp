#include "Mul.h"
      /*Методы Copy() и Clean() для конструктора копирования и деструктора, к сожалению не получилось спрятать в приватные или защищенные*/
      void Mul:: Copy( Expression const * exp){  
           p[0]->Copy(exp->get_p_constantly()[0]);
           p[1]->Copy(exp->get_p_constantly()[1]);
       };
      void Mul::Clean(){
          
           p[0]->Clean();
           p[1]->Clean();
           delete [] p;
      };
      /*Конструкторы*/
      Mul::Mul(Expression* exp_1,Expression*exp_2){
         p=new Expression*[2];
         p[0]=exp_1;
         p[1]=exp_2;
         this->sign="*";
      };
      /*Конструктор копирования*/
     Mul:: Mul(Mul const& exp){
        if(this!=&(exp)){
            Clean();
        }
        this->Copy(&exp);
        this->sign="*";
      };
      Mul::~Mul(){
        Clean();
      };



     /*Перегрузка оператора присваивания*/
    Mul& Mul::operator=(Mul const& B){
         this->Clean();
         this->Copy(&B);
        return *this;
     }


      /*Метод дифференцирования, который является основополагающим для Задачи вообще*/
      Expression* Mul:: derivative(string variable){
            Expression* exp=new Add(new Mul(p[0]->derivative(variable),p[1]),new Mul(p[0],p[1]->derivative(variable)));
            return exp;
      };
    void Mul::print() const{
        cout<<"(";
        p[0]->print();
        cout<<sign;
        p[1]->print();
        cout<<")";
    };
   double Mul::eval(string meaning){
     return p[0]->eval(meaning)*p[1]->eval(meaning);
   };  
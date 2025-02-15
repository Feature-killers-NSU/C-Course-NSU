#include "Sub.h"
      
      /*Методы Copy() и Clean() для конструктора копирования и деструктора, к сожалению не получилось спрятать в приватные или защищенные*/
void Sub::Copy( Expression const * exp){  
           p[0]->Copy(exp->get_p_constantly()[0]);
           p[1]->Copy(exp->get_p_constantly()[1]);
       };
void Sub::Clean(){
          
           p[0]->Clean();
           p[1]->Clean();
           delete [] p;
      };
      /*Конструкторы*/
Sub::Sub(Expression* exp_1,Expression*exp_2){
         p= new Expression*[2];
         p[0]=exp_1;
         p[1]=exp_2;
         this->sign="-";
      };
      /*Конструктор копирования*/
Sub::Sub(Sub const& exp){
        if(this!=&(exp)){
            Clean();
        }
        this->Copy(&exp);
        this->sign="-";
      };
Sub::~Sub(){
        Clean();
      };



     /*Перегрузка оператора присваивания*/
Sub& Sub::operator=(Sub const& B){
         this->Clean();
         this->Copy(&B);
        return *this;
     }


      /*Метод дифференцирования, который является основополагающим для Задачи вообще*/
      Expression* Sub::derivative(string variable){
            Expression* exp=new Sub(p[0]->derivative(variable),p[1]->derivative(variable));
            return exp;
      };
      void Sub::print()const{
        cout<<"(";
        p[0]->print();
        cout<<sign;
        p[1]->print();
        cout<<")";
      };
     double Sub::eval(string meaning){
     return p[0]->eval(meaning)-p[1]->eval(meaning);
   };  
       
   
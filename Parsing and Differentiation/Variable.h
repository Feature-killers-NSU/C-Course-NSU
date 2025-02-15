#include "Expression.h"
class Variable:public Expression{
    public:
      /*Методы Copy() и Clean() для конструктора копирования и деструктора, к сожалению не получилось спрятать в приватные или защищенные*/
      virtual void Copy( Expression const * exp);
      virtual void Clean();
      /*Конструкторы*/
      Variable(string exp_1);
      /*Конструктор копирования*/
      Variable(Variable const& exp);
      ~Variable();



     /*Перегрузка оператора присваивания*/
     Variable& operator=(Variable const& B);


      /*Метод дифференцирования, который является основополагающим для задачи вообще*/
     virtual Expression* derivative(string variable);
     virtual void print() const;
     virtual double eval(string meaning);
      
};
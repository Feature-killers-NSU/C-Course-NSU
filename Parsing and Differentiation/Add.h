#pragma once
#include "Expression.h"
class Add:public Expression{
    public:
      
      /*Методы Copy() и Clean() для конструктора копирования и деструктора, к сожалению не получилось спрятать в приватные или защищенные*/
      virtual void Copy( Expression const * exp);
      virtual void Clean();
      /*Конструкторы*/
      Add(Expression* exp_1,Expression*exp_2);
      /*Конструктор копирования*/
      Add(Add const& exp);
      ~Add();

     /*Перегрузка оператора присваивания*/
     Add& operator=(Add const& B);

      /*Метод дифференцирования, который является основополагающим для Задачи вообще*/
     virtual Expression* derivative(string variable);
     virtual void print() const;
     virtual double eval(string meaning);
      
};
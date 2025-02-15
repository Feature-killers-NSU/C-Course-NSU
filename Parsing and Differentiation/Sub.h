#pragma once
#include "Expression.h"
class Sub:public Expression{
    public:
      
      /*Методы Copy() и Clean() для конструктора копирования и деструктора, к сожалению не получилось спрятать в приватные или защищенные*/
     virtual void Copy( Expression const * exp);
     virtual void Clean();
      /*Конструкторы*/
      Sub(Expression* exp_1,Expression*exp_2);
      /*Конструктор копирования*/
      Sub(Sub const& exp);
      ~Sub();

     /*Перегрузка оператора присваивания*/
     Sub& operator=(Sub const& B);


      /*Метод дифференцирования, который является основополагающим для Задачи вообще*/
     virtual Expression* derivative(string variable);
     virtual void print()const;
     virtual double eval(string meaning);
      
};
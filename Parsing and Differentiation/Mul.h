#pragma once
#include "Expression.h"
#include "Add.h"
class Mul:public Expression{
    public:
      
      /*Методы Copy() и Clean() для конструктора копирования и деструктора, к сожалению не получилось спрятать в приватные или защищенные*/
     virtual void Copy( Expression const * exp);
     virtual void Clean();
      /*Конструкторы*/
      Mul(Expression* exp_1,Expression*exp_2);
      /*Конструктор копирования*/
      Mul(Mul const& exp);
      ~Mul();
     /*Перегрузка оператора присваивания*/
      Mul& operator=(Mul const& B);

      /*Метод дифференцирования, который является основополагающим для Задачи вообще*/
      virtual Expression* derivative(string variable);     
      virtual void print() const; 
      virtual double eval(string meaning);
};
/*#pragma once*/
#include "Expression.h"

class Number:public Expression{
    public:
      /*Методы Copy() и Clean() для конструктора копирования и деструктора, к сожалению не получилось спрятать в приватные или защищенные*/
      virtual void Copy(Expression const* exp);
      virtual void Clean();
      /*Конструкторы*/
      Number(double exp_1);
      Number(string exp_1);
      /*Конструктор копирования*/
      Number(Number const& exp);
      ~Number();



     /*Перегрузка оператора присваивания*/
     Number& operator=(Number const& B);
      /*Метод дифференцирования, который является основополагающим для задачи вообще*/
     virtual Expression* derivative(string variable);
       
     virtual void print() const;
     virtual double eval(string meaning);

};
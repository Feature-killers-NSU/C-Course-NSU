#pragma once
#include <iostream>

/*#include "Tree_derivate.h"*/
using namespace std;
class Expression{
    protected:
        Expression** p;
        string sign;
        /*void Copy(Expression const* exp);
        void Clean();*/
    public:
      /*конструктор и деструктор*/
     
      void psevd_Const(string sign);
      virtual ~Expression();
      
      /*Expression** get_p_constantly()const;*/
      string get_sign_constantly()const;
      string get_sign();
      Expression** get_p();
      Expression** get_p_constantly()const;
      virtual void Copy(Expression const* exp)=0;
      virtual void Clean()=0;
      virtual Expression* derivative(string variable)=0;
      virtual void print() const=0;
      virtual double eval(string meaning)=0;
     

};

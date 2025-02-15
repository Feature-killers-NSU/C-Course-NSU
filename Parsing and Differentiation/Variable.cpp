#include "Variable.h"

/*Методы Copy() и Clean() для конструктора копирования и деструктора, к сожалению не получилось спрятать в приватные или защищенные*/
      void Variable::Copy( Expression const * exp){  
           p[0]=nullptr;
           sign=exp->get_sign_constantly();
       };
      void Variable:: Clean(){
           p[0]->Clean();
           delete [] p;
      };
      /*Конструкторы*/
      Variable:: Variable(string exp_1){
         p=nullptr;
         this->sign=exp_1;
      };
      /*Конструктор копирования*/
     Variable:: Variable(Variable const& exp){
        if(this!=&(exp)){
            Clean();
        }
        this->Copy(&exp);
      };
      Variable::~Variable(){
        Clean();
      };



     /*Перегрузка оператора присваивания*/
     Variable& Variable::operator=(Variable const& B){
         this->Clean();
         this->Copy(&B);
        return *this;
     }


      /*Метод дифференцирования, который является основополагающим для задачи вообще*/
      Expression* Variable::derivative(string variable){
            Expression* exp;
            if(this->get_sign()==variable){
               exp=new Variable("1");
            }
            else  exp=new Variable("0");
            return exp;
      };
     void Variable::print()const{
        cout<<sign;
     }
  double Variable::eval(string meaning){
        
        string Name;
        double term;
        int start=0;
        for(int i=0;i<meaning.size();i++){
          if(meaning[i]=='<'){
             Name=string(meaning,start,i-start);
             start=i+2;
            
          }
          if(i==(meaning.size()-1)||meaning[i]==';'){
            string Q = string(meaning,start,i-start+1*(i==(meaning.size()-1)));
            term=::atof(Q.c_str());
            if(Name==this->sign){
              return term;
            }
            start=i+1;
          }
          
        }
        
        /*double temp = ::atof(    .c_str());*/
     };
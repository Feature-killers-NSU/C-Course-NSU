
#include <iostream>

#include "Number.h"
#include "Add.h"
#include "Sub.h"
#include "Variable.h"
#include "Mul.h"
#include "Div.h"
#include <vector>
using namespace std;


int MddExpr(string D){
     int N=D.size();
     int BEG[N];
     /*vector<int> END=vector<int>(N,0);*/
     int number=0;
     BEG[0]=0;
     for(int i=1;i<N-1;i++){
       BEG[i]=BEG[i-1]+1*(D[i]=='(')-1*(D[i]==')');
       if(BEG[i]==0 && (D[i]=='*'|| D[i]=='/' || D[i]=='-'|| D[i]=='+')){
         number=i;
         return number;
       }
     }   
     return -1;
  };
  
Expression* parse_expr(string expr){
    int number=MddExpr(expr);
    if(number==-1){
      int t=0;
      for(int i=0;i<expr.size();i++){
        if((expr[i]< 48 || expr[i]>57) && expr[i]!=46){
            t=1;
            break;
        }
      }
      if(t==1) return new Variable(expr); 
      else return new Number(expr);
    }
    else{
      if(expr[number]=='+') return new Add(parse_expr(string(expr,1,number-1)),parse_expr(string(expr,number+1,expr.size()-2-number)));
    
     else if(expr[number]=='*') return new Mul(parse_expr(string(expr,1,number-1)),parse_expr(string(expr,number+1,expr.size()-2-number)));
    
     else if(expr[number]=='/') return new Div(parse_expr(string(expr,1,number-1)),parse_expr(string(expr,number+1,expr.size()-2-number)));
    
    else  if(expr[number]=='-') return new Sub(parse_expr(string(expr,1,number-1)),parse_expr(string(expr,number+1,expr.size()-2-number)));
    
}
};

int main() {
  
  Expression * e;
  string expression;
  
  cin>>expression;
  e=parse_expr(expression);
  e->derivative("x")->print();
  
}
#include <iostream>
#include <cmath>
using namespace std;





class Vector3D
{
 public:
   double X;double Y;double Z; 
   Vector3D(){
     this->X=0;
     this->Y=0;
     this->Z=0;  
  }

  //конструктор
  Vector3D(double X,double Y,double Z){
   this->X=X;
   this->Y=Y;
   this->Z=Z;  
 }


 //для удобства переопределил операцию вычитания
 Vector3D operator - (const Vector3D & v){
     return Vector3D(this->X-v.X,this->Y-v.Y,this->Z-v.Z);
 }


 // для удобства индексацию ввел  
 double operator [] (int v){
     if (v==0) return this->X;
     if (v==1) return this->Y;
     if (v==2) return this->Z;
     throw "Index out of range";
 }

 // модуль вектора
 double norm() const {
     return pow(this->X*this->X+this->Y*this->Y+this->Z*this->Z,0.5);
 }

 // для проверки коллинеарности 
 double cos(const Vector3D & v) const{
     return (this->X*v.X+v.Y*this->Y+v.Z*this->Z)/(this->norm()*v.norm());
 }

// вывод для удобства и проверки задачи
 void print() const{
   cout<<this->X<<" "<<this->Y<<" "<<this->Z;
   }
 };






class Segment3D
{
  Vector3D start;
  Vector3D end;
 public:
   //конструктор
   Segment3D(Vector3D start,Vector3D end){
     this->start=start;
     this->end=end;
   }
  // методы для обращения к начальной и конечной точке
  Vector3D get_start(){
     return this->start;
  }
  
  Vector3D get_end(){
     return this->end;
  }

};



// вспомогательная функция для решения подсистемы уравнений
Vector3D proof(Vector3D V1, Vector3D V2,Vector3D A1,Vector3D A2,double D,double f_1, double f_2,int r){
  int a=1*(r==2);
  int b=1+1*(r!=0);
  int c=2-r;
  double t1=(f_2*V2[a]-f_1*V2[b])/D;
  double t2=(V1[a]*f_2-V1[b]*f_1)/D;
  if (t1>=0 && t1<=1 && t2>=0 && t2<=1 && (abs((A1[c]+t1*V1[c])-(A2[c]+t2*V2[c]))<=0.000001)){
      return Vector3D(A1.X+V1.X*t1,A1.Y+V1.Y*t1,A1.Z+V1.Z*t1);
    }
    // Исключение в случае, если пересечений нет
  throw "No intersections!";
}



Vector3D Intersect(Segment3D l1,Segment3D l2){
  // Задаем точки отрезка параметрически Li=Ai+Vi*ti ti из [0,1]
  Vector3D V1= l1.get_end()-l1.get_start();
  Vector3D V2= l2.get_end()-l2.get_start();
  Vector3D A1=l1.get_start();
  Vector3D A2=l2.get_start();
  //для удобства
  double f_x=A2.X-A1.X;double f_y=A2.Y-A1.Y;double f_z=A2.Z-A1.Z;
  
  // приравниваем параметрические задания прямых A1+V1*t1=A2+V2*t2 и получаем переопределенную систему алгебраических уравнений
  //Найдем решение трех подсистем 
  
  double delta_xy=V1.Y*V2.X-V1.X*V2.Y;
  double delta_xz=V1.Z*V2.X-V1.X*V2.Z;
  double delta_yz=V1.Z*V2.Y-V1.Y*V2.Z;
  // если, хоть одна система разрешима, то найдем решение этой системы и проверим является ли оно решением переопределенной системы, если да, то это наша точка пересечения, если нет, то пересечения нет (proof)
  if (delta_xy!=0) return proof(V1,V2,A1,A2,delta_xy,f_x,f_y,0);
  if (delta_xz!=0) return proof(V1,V2,A1,A2,delta_xz,f_x,f_z,1);
  if (delta_yz!=0) return proof(V1,V2,A1,A2,delta_yz,f_y,f_z,2);
    
  // если ни одна из подсистем не имеет решения(определители=0), то отрезки либо не пересекаются, либо лежат на одной прямой и пересекаются в континууме точек.
    
    
    
    //данное условие проверяет лежат ли на одной прямой отрезки
  else if(abs(abs(V1.cos(A2-A1))-1)<=0.000001 || abs(abs(V1.cos(l2.get_end()-A1))-1)<=0.000001){ 
     // находим подотрезок пересечения отрезков, если он есть
     double tau1=(A2-A1).norm()/V1.norm();
     double tau2=(l2.get_end()-A1).norm()/V1.norm();
     double m=min(tau1,tau2);
     double M=max(tau1,tau2);

    
     // проверка: есть ли пересечение отрезков
     if ((0<=M && M<=1) || (m>=0 && m<=1)){
        m=max(0.,m);
        // Так как в задании не указали, что делать в таком случае, я решил выводить начало отрезка пересечения, т.к. это не противоречит условию задачи
        return Vector3D(A1.X+V1.X*m,A1.Y+V1.Y*m,A1.Z+V1.Z*m);
        //M=min(1.,M);
        // конец отрезка пересечения Vector3D(A1.X+V1.X*M,A1.Y+V1.Y*M,A1.Z+V1.Z*M);
     }
    
     // Исключение в случае, если отрезки лежат на одной прямой и пересечений нет
     throw "No intersections!"; 
  }
  
  // Исключение в случае, если прямые не лежат на одной прямой и пересечений нет
  throw "No intersections!";
}

int main() { 
  Segment3D l1=Segment3D(Vector3D(11,13,6),Vector3D(8,8.5,4.5));
  Segment3D l2=Segment3D(Vector3D(5,2,3),Vector3D(8,8.,4.5));
  try{
  Intersect(l1,l2).print();
  }catch(char const* ex){
    cerr<< ex ;
  }

}
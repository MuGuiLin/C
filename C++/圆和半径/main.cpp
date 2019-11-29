#include <iostream>

using namespace std;

//抽象基类
class Shape{
	public:
		virtual double Area() = 0;
};

//梯形类
class Trapezoid : Shape{

	public:
		Trapezoid(int t, int b, int h):Shape(){
			cout << (t + b) * h / 2;
		};
		//return (上 + 下) * 高 / 除2
};

//圆形类
class Circle : public Shape{
	//const PI  = 3.14159;

	//return PI * r temp

};

//三角形类
class Triangle : public Shape{
	 
};

//主函数
void main(){
	Trapezoid T(100, 120, 300);
};

 /*

#include <iostream> 
using namespace std;
 
class Shape {
   protected:
      int width, height;
   public:
      Shape( int a=0, int b=0)
      {
         width = a;
         height = b;
      }
      virtual int area()
      {
         cout << "Parent class area :" <<endl;
         return 0;
      }
};
class Rectangle: public Shape{
   public:
      Rectangle( int a=0, int b=0):Shape(a, b) { }
      int area ()
      { 
         cout << "Rectangle class area :" <<endl;
         return (width * height); 
      }
};
class Triangle: public Shape{
   public:
      Triangle( int a=0, int b=0):Shape(a, b) { }
      int area ()
      { 
         cout << "Triangle class area :" <<endl;
         return (width * height / 2); 
      }
};
// 程序的主函数
int main( )
{
   Shape *shape;
   Rectangle rec(10,7);
   Triangle  tri(10,5);
 
   // 存储矩形的地址
   shape = &rec;
   // 调用矩形的求面积函数 area
   shape->area();
 
   // 存储三角形的地址
   shape = &tri;
   // 调用三角形的求面积函数 area
   shape->area();
   
   return 0;
}*/
#include <iostream>
#include <iomanip> //c++头文件iomanip.h中的setw、setprecision、setfill和setbase函数

using namespace std;

// 1．定义盒子Box类，要求具有以下成员：长、宽、高分别为x,y,z，可设置盒子形状；可计算盒子体积；可计算盒子的表面积。
class Box{
	private:
		int length, width, height;

	public:
		Box(int x, int y, int z){
			length = x;
			width  = y;
			height = z;
		};
		//计算体积
		int Volume(){
			return length * width * height;
		};
		//计算表面积
		int Surface(){
			return (length * width + length * height + width * height) * 2;
		};
};

// 2．有两个长方柱，其长、宽、高分别为：（1）30，20，10；（2）12，10，20。分别求他们的体积。编一个基于对象的程序，在类中用带参数的构造函数。
class Box2{
	private:
		int l, w, h;

	public:
		Box2(int a = 0, int b = 0, int c = 0){
			l = a;
			w = b;
			h = c;
		};

		void Volume(){
			cout << "\n体积为：" << l * w * h;	
		};
};

// 3．声明一个类模板，利用它分别实现两个整数、浮点数和字符的比较，求出大数和小数。

template <class CT>

class MoBan{
	protected:
		CT a, b;

	public:
		MoBan(CT x, CT y){
			a = x;
			b = y;
		};

		CT Max(){
			return (a > b) ? a : b;
		};

		CT Min(){
			return (a < b) ? a : b;
		};
		//加减乘除 和差积商
		CT Sum(){
			return a + b;
		};
};

// 4．建立一个对象数组，内放5个学生的数据（学号、成绩），用指针指向数组首元素，输出第1，3，5个学生的数据。初值自拟。

class Student{
	protected:
		dlucb xhao, score;

	public:
		Stedent(int a, int b){
			xhao = a;
			score = b;
		};
};

class StuArr : public Student{
	public:
		Student std[] = {Student(80.5, 88.6)}
};

void main(){
	Box V(10, 20, 30);
	cout << "体积为：" << V.Volume() << endl;

	Box S(10, 20, 30);
	cout << "表面积为：" << V.Surface() << endl;

	Box2 V1(30, 20, 10);
	V1.Volume();

	Box2 V2(12, 10, 20);
	V2.Volume();

	MoBan<int> ct1(50, 100);
	cout << "\n\n整数int(50, 100) 大值：" << ct1.Max() << "，小值：" << ct1.Min() << endl;

	MoBan<double> ct2(3.1415926, 0.1314520);
	cout << "\n\n双精度double(3.1415926, 0.1314520) 大值：" << setprecision(10) << ct2.Max() << "，小值：" << setprecision(12) << ct2.Min() << endl; //【注：setprecision(12) 在设置输出长度时，这个要放在要输出的变量前面哦！还要记得加头文件 <iomanip> 】

	MoBan<char> ct3('A', 'a');
	cout << "\n\n字符char('A', 'a')大值：" << ct3.Max() << "，小值：" << ct3.Min() << endl;


};


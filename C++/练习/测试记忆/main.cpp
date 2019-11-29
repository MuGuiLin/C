#include "mytop.h";

#include <string> //字符串

#include <iomanip> //

class Sen{
	protected:
		int y, m, d;

	public:
		Sen(int a = 0, int b = 0, int c = 0); // 默认值只能在内部，不能在外部！！！

		void show(){
			cout << ", 出生日期：" << y << " 年 " << m << " 月 " << d << " 日 \n";
		};

		void chenfa(){
			for(int i = 1; i <= 9; i++){
				for(int j = 1; j <= i; j++){
					cout << j << " × " << i << " = " << i * j << "  ";
				}
				cout << endl << endl;
			}
		};
};

Sen::Sen(int a, int b, int c){
	y = a;
	m = b;
	d = c;
}

class Ren{
	private:
		string name;
		char *sex;
		Sen age;

	public:
		Ren(string n, char *s, int a, int b, int c):age(a, b, c){
			name = n;
			sex = s;
		};

		void print(){
			cout << "我叫 " << name << ", 性别 " << sex;
			age.show();

			cout << endl << endl;
			age.chenfa();
		};
		
};
/*
	定义一个图形类(figure)，其中有保护类型的成员数据：高度(height)帮宽度(width)，一个公有的构造函数。
	由该图形类建立两个派生类：矩形类和等腰三角形类。
	在每个派生类中都包含一个函数area()，分别用来计算矩形和等腰三角形的面积。
	其中，主函数已给出，请完成其他部分的代码。
*/

class figure{
	protected:
		double height, width;

	public:
		figure(double h = 0, double w = 0){
			width = w;
			height = h;
		};
};

//三角形
class triangle : public figure{
	public:
		
		triangle(double h, double w):figure(h, w){
			height = h;
			width = w;
			cout << "\n 注：继承后可以直接用 基类的保护成员数据 height width \n";
		}
		double area(){
			//三角形周长公式: C = a + b + c 公式描述：公式中a，b，c分别为三角形的三边。
			//return 0.5 * height * width;
			
			//三角形的面积 公式: 面积=底×高÷2  S＝a×h÷2
			return height * width / 2;
			
			//return 0.5 * height * width;

		};
};

//矩形
class rectangle : public figure{
	public:
		rectangle(double w, double h);
		double area();
};
rectangle :: rectangle(double w, double h):figure(w, h){
	height = h;
	width = w;
};
double rectangle :: area(){
	return width * height;
};

//圆形
class circle{
	private:
		int i;

	public:
		circle(int r = 0){
			
			cout <<endl << r << "我是C的构造函数！次数为：" << i++;
		}
};

//人员类
class Person{
	//private:
	protected:
		char *name;
		int age;
		char sex[8];

	public:
		Person(char *a = "", int b = 0, char *c = ""){
			name = a;
			age = b;
			strcpy(sex, c); //数组
		}
};

//雇员类
class Employee : public Person{
	private:
		char *department;
		double salary;

	public: 
		Employee(char *a = "", int b = 0, char *c = "", char *d = "", double e = 0.0):Person(a, b, c){
			department = d;
			salary = e;
		};

		void Display(){
			cout << "\n\n雇员姓名：" << name << " 年龄：" << age << " 性别：" << sex  << " 部门：" << department << " 薪水：" << salary << endl;
		};
};


template <typename T>

T max(T x, T y){
	return x > y ? x : y;
}

void main(){
	cout << "666";
	//Sen s(1,2);
	//s.show();
	
	Ren r("沐枫自然", "先生", 1991, 12, 04);
	r.print();

	triangle tir(2, 3);
	cout << "等腰三角形：" << tir.area() << endl;

	rectangle rec(2, 3);
	cout << "矩形长方形：" << rec.area() << endl;

	circle A(4), B(5), C[3], *P[2] = {&A, &B};

	int n = 2, *p = &n, *q = p;
	n = *q;
	//p = n;
	p = q;
	*q = *p;

	int i1 = 10, i2 = 56;
	cout << "\n\n 模板max整数：" << max(i1, i2) << endl;

	float f1 = 8.5, f2 = 5.6;
	cout << "\n\n 模板max单精度浮点数：" << max(f1, f2) << endl;

	double d1 = 3.1415926, d2 = 520.1314;
	cout << "\n\n 模板max双精度浮点数：" << max(d1, d2) << endl;

	char c1 = 'z', c2 = 'n';
	cout << "\n\n 模板max char 单字符：" << max(c1, c2) << endl;

	Employee E("沐枫自然", 28, "男士", "IT部", 12000.123456789);
	E.Display();

	double a1 = 3.1416926, b2 = 520.1314; // 注 个数包括整数部分 最后一位 四舍五入
	cout << setprecision(4) << a1 <<" , "<< setprecision(5) << b2 <<endl;

	system("pause");

};




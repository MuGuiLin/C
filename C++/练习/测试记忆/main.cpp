#include "mytop.h";

#include <string> //�ַ���

#include <iomanip> //

class Sen{
	protected:
		int y, m, d;

	public:
		Sen(int a = 0, int b = 0, int c = 0); // Ĭ��ֵֻ�����ڲ����������ⲿ������

		void show(){
			cout << ", �������ڣ�" << y << " �� " << m << " �� " << d << " �� \n";
		};

		void chenfa(){
			for(int i = 1; i <= 9; i++){
				for(int j = 1; j <= i; j++){
					cout << j << " �� " << i << " = " << i * j << "  ";
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
			cout << "�ҽ� " << name << ", �Ա� " << sex;
			age.show();

			cout << endl << endl;
			age.chenfa();
		};
		
};
/*
	����һ��ͼ����(figure)�������б������͵ĳ�Ա���ݣ��߶�(height)����(width)��һ�����еĹ��캯����
	�ɸ�ͼ���ཨ�����������ࣺ������͵����������ࡣ
	��ÿ���������ж�����һ������area()���ֱ�����������κ͵��������ε������
	���У��������Ѹ�����������������ֵĴ��롣
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

//������
class triangle : public figure{
	public:
		
		triangle(double h, double w):figure(h, w){
			height = h;
			width = w;
			cout << "\n ע���̳к����ֱ���� ����ı�����Ա���� height width \n";
		}
		double area(){
			//�������ܳ���ʽ: C = a + b + c ��ʽ��������ʽ��a��b��c�ֱ�Ϊ�����ε����ߡ�
			//return 0.5 * height * width;
			
			//�����ε���� ��ʽ: ���=�ס��ߡ�2  S��a��h��2
			return height * width / 2;
			
			//return 0.5 * height * width;

		};
};

//����
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

//Բ��
class circle{
	private:
		int i;

	public:
		circle(int r = 0){
			
			cout <<endl << r << "����C�Ĺ��캯��������Ϊ��" << i++;
		}
};

//��Ա��
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
			strcpy(sex, c); //����
		}
};

//��Ա��
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
			cout << "\n\n��Ա������" << name << " ���䣺" << age << " �Ա�" << sex  << " ���ţ�" << department << " нˮ��" << salary << endl;
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
	
	Ren r("�����Ȼ", "����", 1991, 12, 04);
	r.print();

	triangle tir(2, 3);
	cout << "���������Σ�" << tir.area() << endl;

	rectangle rec(2, 3);
	cout << "���γ����Σ�" << rec.area() << endl;

	circle A(4), B(5), C[3], *P[2] = {&A, &B};

	int n = 2, *p = &n, *q = p;
	n = *q;
	//p = n;
	p = q;
	*q = *p;

	int i1 = 10, i2 = 56;
	cout << "\n\n ģ��max������" << max(i1, i2) << endl;

	float f1 = 8.5, f2 = 5.6;
	cout << "\n\n ģ��max�����ȸ�������" << max(f1, f2) << endl;

	double d1 = 3.1415926, d2 = 520.1314;
	cout << "\n\n ģ��max˫���ȸ�������" << max(d1, d2) << endl;

	char c1 = 'z', c2 = 'n';
	cout << "\n\n ģ��max char ���ַ���" << max(c1, c2) << endl;

	Employee E("�����Ȼ", 28, "��ʿ", "IT��", 12000.123456789);
	E.Display();

	double a1 = 3.1416926, b2 = 520.1314; // ע ���������������� ���һλ ��������
	cout << setprecision(4) << a1 <<" , "<< setprecision(5) << b2 <<endl;

	system("pause");

};




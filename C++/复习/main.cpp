#include <iostream>
#include <string>

using namespace std;

class sr{
	private:
		int l, y, r;

	public:
		sr(int i, int j, int k){
			l = i;
			y = j;
			r = k;
		};
		void print(){
			cout << "���գ�" << l << "�꣬" << y << "�£�" << r << endl;
		}

};

class ren{
	private:
		string name;
		char *six;
		sr age;

	public:
		ren(string n, char *s, int a, int b, int c):age(a, b, c){
			name = n;
			six = s;
		};
		void show(){
			cout << name << six;
			age.print();
		}
};

class circle{
	private:
		float Radius;
	
	public:	
		circle(float r){
			Radius = r;
		}
		float GetArea(){
			return Radius * Radius * 3.14;
		};
};

void main(){
	ren R("�¹���", "��", 1991, 10, 29);
		R.show();

	circle c1(5.6);
	cout << "Բ�������" << c1.GetArea() << endl;
};

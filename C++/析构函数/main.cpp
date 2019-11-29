#include <iostream>

using namespace std;

class A{

	private:
		int a;

	public:
		A(int aa){
			a = aa;
		};

		~A(){
			cout << "Destuctor A!" << a << endl;
		};
};

class B : public A{
	private:
		int b;

	public:
		B(int aa = 0, int bb = 0):A(aa){
			b = bb;
		};

		~B(){
			cout << "Destuctor B!" << b << endl;
		};
};

int main(){
	B x(5), y(6, 7);
	//B x;
	
	const int num = 20;

	int scores[num];
	
  //for(int i = 1; i <= num; i + +){
	for(int i = 1; i <= num; i++){
		scores[i] = i;
		cout << scores[i] << endl;
	}

	cout << scores[10] << endl;

  //for(int a = I; a <= 4; a+=1)
	for(int a = 1; a <= 4; a+=1)
	for(int b = 2; b <= 4; b+=b)
	{
		if(a+b < 5){
			cout << "+";
		} else {
			cout << "*";
		}
	}
	system("pause");  //注：析构函数会在此之后执行
	return 0;
};

/*
	Destuctor B!7 
	Destuctor A!6
	Destuctor B!0
	Destuctor A!5
*/
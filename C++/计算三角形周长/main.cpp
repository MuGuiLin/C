
#include <iostream>

using namespace std;

//�궨�� PI
#define PI 3.1415926 // ע��������治Ҫ�� ; �� ��Ȼ�ᱨ��!!!

//��������
class Sjx{
	public:

		int zhouchang(int a, int b, int c){ //�������ܳ�	��ʽ :  �����������Σ�C=a+b+c �����������Σ�C=2a+b ���ȱ������Σ�C=3a
			return a + b + c;
		};
};

//Բ��
class Yuan{
	public:

		double zhouchang(double r){ //Բ�ܳ�	��ʽ��C��2��r 
			return 2 * PI * r;
		};

		double mieji(double r){//Բ���		��ʽ��S = ��r2 ͨ������3.14��Ϊ�е�ֵ Բ���:SԲ=�г���r��ƽ��; ��ʽ: S=��r2 
			return PI * r * r; 
		};
};

//������
void main(){
	//����������
	Sjx s;
	int x, y, z;
	
	cout << "�����������ε������ߣ�\n";
	cin >> x >> y >> z;

	cout << "�����ε��ܳ�Ϊ��" << s.zhouchang(x, y, z) << endl;


	//����Բ
	Yuan u;
	double r;

	cout << "������Բ�İ뾶��\n";
	cin >> r;

	cout << "Բ���ܳ�Ϊ��" << u.zhouchang(r) << endl;
	cout << "Բ�����Ϊ��" << u.mieji(r) << endl;

};
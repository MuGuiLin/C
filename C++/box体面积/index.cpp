#include <iostream>
#include <iomanip> //c++ͷ�ļ�iomanip.h�е�setw��setprecision��setfill��setbase����

using namespace std;

// 1���������Box�࣬Ҫ��������³�Ա���������߷ֱ�Ϊx,y,z�������ú�����״���ɼ������������ɼ�����ӵı������
class Box{
	private:
		int length, width, height;

	public:
		Box(int x, int y, int z){
			length = x;
			width  = y;
			height = z;
		};
		//�������
		int Volume(){
			return length * width * height;
		};
		//��������
		int Surface(){
			return (length * width + length * height + width * height) * 2;
		};
};

// 2�����������������䳤�����߷ֱ�Ϊ����1��30��20��10����2��12��10��20���ֱ������ǵ��������һ�����ڶ���ĳ����������ô������Ĺ��캯����
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
			cout << "\n���Ϊ��" << l * w * h;	
		};
};

// 3������һ����ģ�壬�������ֱ�ʵ���������������������ַ��ıȽϣ����������С����

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
		//�Ӽ��˳� �Ͳ����
		CT Sum(){
			return a + b;
		};
};

// 4������һ���������飬�ڷ�5��ѧ�������ݣ�ѧ�š��ɼ�������ָ��ָ��������Ԫ�أ������1��3��5��ѧ�������ݡ���ֵ���⡣

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
	cout << "���Ϊ��" << V.Volume() << endl;

	Box S(10, 20, 30);
	cout << "�����Ϊ��" << V.Surface() << endl;

	Box2 V1(30, 20, 10);
	V1.Volume();

	Box2 V2(12, 10, 20);
	V2.Volume();

	MoBan<int> ct1(50, 100);
	cout << "\n\n����int(50, 100) ��ֵ��" << ct1.Max() << "��Сֵ��" << ct1.Min() << endl;

	MoBan<double> ct2(3.1415926, 0.1314520);
	cout << "\n\n˫����double(3.1415926, 0.1314520) ��ֵ��" << setprecision(10) << ct2.Max() << "��Сֵ��" << setprecision(12) << ct2.Min() << endl; //��ע��setprecision(12) �������������ʱ�����Ҫ����Ҫ����ı���ǰ��Ŷ����Ҫ�ǵü�ͷ�ļ� <iomanip> ��

	MoBan<char> ct3('A', 'a');
	cout << "\n\n�ַ�char('A', 'a')��ֵ��" << ct3.Max() << "��Сֵ��" << ct3.Min() << endl;


};


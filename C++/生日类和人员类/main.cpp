#include <iostream>	//�������ͷ�ļ� iostream = istream + ostream;
#include <string>	//�ַ���ͷ�ļ�

using namespace std;	//�����ռ� std

//������
class Shengri{
	private:
		int y, m, d;	//����

	public:
		Shengri(int i, int j, int k){
			y = i;
			m = j; d = k;
		};

		void Show(){
			cout << "���գ�" << y << " �� " << m << " �� " << d << " �գ�\n\n";
		};
};

//��Ա��
class Renyuan{
	private:
		string name;	//�ַ���			����
		char *sex;		//�ַ�ָ��			�Ա�
		Shengri age;	//�����			����
		char job[20];	//�ַ�����			ְλ

	public:
		Renyuan(string n, char *s, char *z, int i, int j, int k);

		void Print(){
			cout << "�ҽУ�" << name << "���Ա� " << sex << "��ְλ��" << job << "���ҵ�";
			age.Show();
		}
};

//���ⲿʵ��Renyuan��Ĺ��캯���͸�ֵ������ΪShengri��� age����ֵ
Renyuan::Renyuan(string n, char *s, char *z, int i, int j, int k):age(i, j, k){
	name = n;
	sex = s;
	strcpy(job, z); //���鸳ֵ
};


void main(){
	Renyuan r("�����Ȼ", "�е�", "Webǰ��", 1991, 12, 04);
	r.Print();

	//��������ҽУ������Ȼ���Ա� �еģ�ְλ��Webǰ�ˣ��ҵ����գ�1991 �� 12 �� 4 �գ�
	system("pause"); //��Debug��������Ŀ��.exeʱ������
};


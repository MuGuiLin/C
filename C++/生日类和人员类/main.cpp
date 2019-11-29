#include <iostream>	//输入输出头文件 iostream = istream + ostream;
#include <string>	//字符串头文件

using namespace std;	//命名空间 std

//生日类
class Shengri{
	private:
		int y, m, d;	//整型

	public:
		Shengri(int i, int j, int k){
			y = i;
			m = j; d = k;
		};

		void Show(){
			cout << "生日：" << y << " 年 " << m << " 月 " << d << " 日；\n\n";
		};
};

//人员类
class Renyuan{
	private:
		string name;	//字符串			姓名
		char *sex;		//字符指针			性别
		Shengri age;	//类对象			生日
		char job[20];	//字符数组			职位

	public:
		Renyuan(string n, char *s, char *z, int i, int j, int k);

		void Print(){
			cout << "我叫：" << name << "，性别： " << sex << "，职位：" << job << "，我的";
			age.Show();
		}
};

//在外部实现Renyuan类的构造函数和赋值，并且为Shengri类的 age对象赋值
Renyuan::Renyuan(string n, char *s, char *z, int i, int j, int k):age(i, j, k){
	name = n;
	sex = s;
	strcpy(job, z); //数组赋值
};


void main(){
	Renyuan r("沐枫自然", "男的", "Web前端", 1991, 12, 04);
	r.Print();

	//【结果】我叫：沐枫自然，性别： 男的，职位：Web前端，我的生日：1991 年 12 月 4 日；
	system("pause"); //在Debug中运行项目名.exe时不闪退
};


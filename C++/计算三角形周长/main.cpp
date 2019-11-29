
#include <iostream>

using namespace std;

//宏定义 PI
#define PI 3.1415926 // 注：这里后面不要加 ; 号 不然会报错!!!

//三角形类
class Sjx{
	public:

		int zhouchang(int a, int b, int c){ //三角形周长	公式 :  不规则三角形：C=a+b+c ，等腰三角形：C=2a+b ，等边三角形：C=3a
			return a + b + c;
		};
};

//圆类
class Yuan{
	public:

		double zhouchang(double r){ //圆周长	公式：C＝2πr 
			return 2 * PI * r;
		};

		double mieji(double r){//圆面积		公式：S = πr2 通常采用3.14作为π的值 圆面积:S圆=π乘以r的平方; 公式: S=πr2 
			return PI * r * r; 
		};
};

//主函数
void main(){
	//计算三角形
	Sjx s;
	int x, y, z;
	
	cout << "请输入三角形的三条边：\n";
	cin >> x >> y >> z;

	cout << "三角形的周长为：" << s.zhouchang(x, y, z) << endl;


	//计算圆
	Yuan u;
	double r;

	cout << "请输入圆的半径：\n";
	cin >> r;

	cout << "圆的周长为：" << u.zhouchang(r) << endl;
	cout << "圆的面积为：" << u.mieji(r) << endl;

};
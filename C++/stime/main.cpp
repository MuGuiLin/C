#include "./head.h";

void PringMsg()
{
	cout  << " -> Hello \n";
};

int main()
{
	int i = 0;

	while(true)
	{
		i++;
		
		PringMsg();

		Sleep(1000);  //�ӳ�ִ�� 1000ms = 1s;

		cout << i;
	};
	return 0;
};
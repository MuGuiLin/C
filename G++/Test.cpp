#include <iostream>
#include <windows.h>

using namespace std;

// 乘法口决
int main(void)
{
    for (int i = 1; i <= 9; i++)
    {
        cout << endl << endl;
        for (int j = 1; j <= i; j++)
        {
            cout << j << "*" << i << "=" << i * j << "   ";
        }
    }
    cout << endl << endl;
    system("PAUSE");
    return 0;
}
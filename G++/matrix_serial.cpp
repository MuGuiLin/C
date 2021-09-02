#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>


const int L = 512;
const int C = 512;
const int K = 512;
int main(int argc)
{
    clock_t start, end;
    start = clock();
    double t; //计算程序运行时间
    int i, j, k;
    int(*a)[C] = new int[L][C];
    int(*b)[K] = new int[C][K];
    int(*c)[K] = new int[L][K];
    ;

    for (i = 0; i < L; i++)
        for (j = 0; j < C; j++)
            a[i][j] = 1;
    for (i = 0; i < L; i++)
        for (j = 0; j < C; j++)
            b[i][j] = 1;
    for (i = 0; i < L; i++)
    {
        for (j = 0; j < C; j++) //计算矩阵第i行第j个的值
        {
            c[i][j] = 0;
            for (k = 0; k < K; k++)
                c[i][j] += a[i][k] * b[k][j];
            printf("%d\t",c[i][j]);
        }
    }
    delete[] a;
    delete[] b;
    delete[] c;
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n Run time........%f\n ", t);
    system("pause");
    return 0;
}
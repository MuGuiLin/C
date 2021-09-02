#include <iostream>
#include <time.h>
#include <stdio.h>
#include <windows.h>
using namespace std;

// �����С
const int MAX = 1024;
const int TIME = 64;

// ���д���
const int LOOP = 5;

// ��������
float matrix_one[MAX][MAX];
float matrix_two[MAX][MAX];
float matrix_sum[MAX][MAX];

// ��������
double serial(int n, float a[][MAX], float b[][MAX], float c[][MAX]);
double cache(int n, float a[][MAX], float b[][MAX], float c[][MAX]);
double slices(int n, float a[][MAX], float b[][MAX], float c[][MAX]);
double sse_mul(int n, float a[][MAX], float b[][MAX], float c[][MAX]);

// ��ʼ����������
void initial(int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            matrix_one[i][j] = 0.0;
            matrix_sum[i][j] = (float) rand();
        }
        matrix_one[i][i] = 1.0;
    }
};

/**
 * ������� ֮ �������㷨��
 * ʱ�临�Ӷȣ�O(n) = n^3
 **/
double serial(int n, float a[][MAX], float b[][MAX], float c[][MAX])
{
    double time;
    clock_t start = clock(), end;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = 0.0;
            for (int k = 0; k < n; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    end = clock();
    time = (double)(end - start);
    cout << endl << " ���в�����ʱ��" << (time / CLOCKS_PER_SEC) << " ��" << endl;
    return time / CLOCKS_PER_SEC;
};

/**
 * ������� ֮ ��Cache������/�Ĵ������Ż��㷨��
 * ʱ�临�Ӷȣ�O(n) = n^3
 **/
double cache(int n, float a[][MAX], float b[][MAX], float c[][MAX])
{
    double time;
    clock_t start = clock(), end;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            swap(b[i][j], b[j][i]);
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            c[i][j] = 0.0;
            for (int k = 0; k < n; ++k)
            {
                c[i][j] += a[i][k] * b[j][k];
            }
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            swap(b[i][j], b[j][i]);
        }
    }
    end = clock();
    time = (double)(end - start);
    cout << endl << " ���������ʱ��" << (time / CLOCKS_PER_SEC) << " ��" << endl;
    return time / CLOCKS_PER_SEC;
};

/** 
 * ������� ֮ ����Ƭ�����㷨��
 * ʱ�临�Ӷȣ�O(n) = n^3
 **/
double slices(int n, float a[][MAX], float b[][MAX], float c[][MAX])
{
    float t;
    double time;
    __m128 t1, t2, sum;
    clock_t start = clock(), end;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            swap(b[i][j], b[j][i]);
        }
    }
    for (int r = 0; r < n / TIME; ++r)
    {
        for (int q = 0; q < n / TIME; ++q)
        {
            for (int i = 0; i < TIME; ++i)
            {
                for (int j = 0; j < TIME; ++j)
                {
                    c[r * TIME + i][q * TIME + j] = 0.0;
                }
            }
            for (int p = 0; p < n / TIME; ++p)
            {
                for (int i = 0; i < TIME; ++i)
                {
                    for (int j = 0; j < TIME; ++j)
                    {
                        sum = _mm_setzero_ps();
                        for (int k = 0; k < TIME; k += 4)
                        {
                            t1 = _mm_loadu_ps(a[r * TIME + i] + p * TIME + k);
                            t2 = _mm_loadu_ps(b[q * TIME + j] + p * TIME + k);
                            t1 = _mm_mul_ps(t1, t2);
                            sum = _mm_add_ps(sum, t1);
                        }
                        sum = _mm_hadd_ps(sum, sum);
                        sum = _mm_hadd_ps(sum, sum);
                        _mm_store_ss(&t, sum);
                        c[r * TIME + i][q * TIME + j] += t;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            swap(b[i][j], b[j][i]);
        }
    }
    end = clock();
    time = (double)(end - start);
    cout << endl << " ��Ƭ������ʱ��" << (time / CLOCKS_PER_SEC) << " ��" << endl;
    return time / CLOCKS_PER_SEC;
};

/**
 * ������� ֮ ��SSE��SIMD��̣��㷨��
 * ʱ�临�Ӷȣ�O(n) = n^3
 **/
double sse_mul(int n, float a[][MAX], float b[][MAX], float c[][MAX])
{
    double time;
    __m128 t1, t2, sum;
    clock_t start = clock(), end;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            swap(b[i][j], b[j][i]);
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            c[i][j] = 0.0;
            sum = _mm_setzero_ps();
            for (int k = n - 4; k >= 0; k -= 4)
            {
                t1 = _mm_loadu_ps(a[i] + k);
                t2 = _mm_loadu_ps(b[j] + k);
                t1 = _mm_mul_ps(t1, t2);
                sum = _mm_add_ps(sum, t1);
            }
            sum = _mm_hadd_ps(sum, sum);
            sum = _mm_hadd_ps(sum, sum);
            _mm_store_ss(c[i] + j, sum);
            for (int k = (n % 4) - 1; k >= 0; --k)
            {
                c[i][j] += a[i][k] * b[j][k];
            }
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            swap(b[i][j], b[j][i]);
        }
    }
    end = clock();
    time = (double)(end - start);
    cout << endl << " SSE ������ʱ��" << (time / CLOCKS_PER_SEC) << " ��" << endl;
    return time / CLOCKS_PER_SEC;
};

// ͳ��ƽ������
void average(double serial_time, double cache_time, double slices_time, double sse_mul_time)
{
    cout << endl << "ƽ������ʱ��:" << endl;
    cout << endl << " ���в��Ժ�ʱ:" << serial_time / LOOP << " ��" << endl;
    cout << endl << " ������Ժ�ʱ:" << cache_time / LOOP << " ��" << endl;
    cout << endl << " ��Ƭ���Ժ�ʱ:" << slices_time / LOOP << " ��" << endl;
    cout << endl << " SSE ���Ժ�ʱ:" << sse_mul_time / LOOP << " ��" << endl;
};

// ��������
void only(void)
{
    initial(MAX);
    serial(MAX, matrix_one, matrix_sum, matrix_two);
    cache(MAX, matrix_one, matrix_sum, matrix_two);
    slices(MAX, matrix_one, matrix_sum, matrix_two);
    sse_mul(MAX, matrix_one, matrix_sum, matrix_two);
};

// �������
void many(int l)
{
    double serial_time = 0.00;
    double cache_time = 0.00;
    double slices_time = 0.00;
    double sse_mul_time = 0.00;
    for (int i = 1; i <= l; i++)
    {
        cout << endl << "��" << i << "�����н����" << endl;
        initial(MAX);
        serial_time += serial(MAX, matrix_one, matrix_sum, matrix_two);
        cache_time += cache(MAX, matrix_one, matrix_sum, matrix_two);
        slices_time += slices(MAX, matrix_one, matrix_sum, matrix_two);
        sse_mul_time += sse_mul(MAX, matrix_one, matrix_sum, matrix_two);
    }
    average(serial_time, cache_time, slices_time, sse_mul_time);
};

// ������
int main(void)
{
    cout << "�������������У����Ժ�. . ." << endl;
    // ���õ������� 
    // only();
    // ���ö������
    many(LOOP);
    cout << endl << "���������н�����" ;
    system("PAUSE");
    return 0;
};
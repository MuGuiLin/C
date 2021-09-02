#include <iostream>
#include <time.h>
#include <stdio.h>
#include <windows.h>
using namespace std;

// 矩阵大小
const int MAX = 1024;
const int TIME = 64;

// 运行次数
const int LOOP = 5;

// 矩阵数组
float matrix_one[MAX][MAX];
float matrix_two[MAX][MAX];
float matrix_sum[MAX][MAX];

// 类型声明
double serial(int n, float a[][MAX], float b[][MAX], float c[][MAX]);
double cache(int n, float a[][MAX], float b[][MAX], float c[][MAX]);
double slices(int n, float a[][MAX], float b[][MAX], float c[][MAX]);
double sse_mul(int n, float a[][MAX], float b[][MAX], float c[][MAX]);

// 初始化矩阵数据
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
 * 矩阵相乘 之 【串行算法】
 * 时间复杂度：O(n) = n^3
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
    cout << endl << " 串行策略用时：" << (time / CLOCKS_PER_SEC) << " 秒" << endl;
    return time / CLOCKS_PER_SEC;
};

/**
 * 矩阵相乘 之 【Cache（缓存/寄存器）优化算法】
 * 时间复杂度：O(n) = n^3
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
    cout << endl << " 缓存策略用时：" << (time / CLOCKS_PER_SEC) << " 秒" << endl;
    return time / CLOCKS_PER_SEC;
};

/** 
 * 矩阵相乘 之 【分片策略算法】
 * 时间复杂度：O(n) = n^3
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
    cout << endl << " 分片策略用时：" << (time / CLOCKS_PER_SEC) << " 秒" << endl;
    return time / CLOCKS_PER_SEC;
};

/**
 * 矩阵相乘 之 【SSE（SIMD编程）算法】
 * 时间复杂度：O(n) = n^3
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
    cout << endl << " SSE 策略用时：" << (time / CLOCKS_PER_SEC) << " 秒" << endl;
    return time / CLOCKS_PER_SEC;
};

// 统计平均运行
void average(double serial_time, double cache_time, double slices_time, double sse_mul_time)
{
    cout << endl << "平均运行时长:" << endl;
    cout << endl << " 串行策略耗时:" << serial_time / LOOP << " 秒" << endl;
    cout << endl << " 缓存策略耗时:" << cache_time / LOOP << " 秒" << endl;
    cout << endl << " 分片策略耗时:" << slices_time / LOOP << " 秒" << endl;
    cout << endl << " SSE 策略耗时:" << sse_mul_time / LOOP << " 秒" << endl;
};

// 单次运行
void only(void)
{
    initial(MAX);
    serial(MAX, matrix_one, matrix_sum, matrix_two);
    cache(MAX, matrix_one, matrix_sum, matrix_two);
    slices(MAX, matrix_one, matrix_sum, matrix_two);
    sse_mul(MAX, matrix_one, matrix_sum, matrix_two);
};

// 多次运行
void many(int l)
{
    double serial_time = 0.00;
    double cache_time = 0.00;
    double slices_time = 0.00;
    double sse_mul_time = 0.00;
    for (int i = 1; i <= l; i++)
    {
        cout << endl << "第" << i << "次运行结果：" << endl;
        initial(MAX);
        serial_time += serial(MAX, matrix_one, matrix_sum, matrix_two);
        cache_time += cache(MAX, matrix_one, matrix_sum, matrix_two);
        slices_time += slices(MAX, matrix_one, matrix_sum, matrix_two);
        sse_mul_time += sse_mul(MAX, matrix_one, matrix_sum, matrix_two);
    }
    average(serial_time, cache_time, slices_time, sse_mul_time);
};

// 主函数
int main(void)
{
    cout << "程序正在运行中，请稍候. . ." << endl;
    // 调用单次运行 
    // only();
    // 调用多次运行
    many(LOOP);
    cout << endl << "程序已运行结束，" ;
    system("PAUSE");
    return 0;
};
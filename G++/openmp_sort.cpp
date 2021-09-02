#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <immintrin.h>
#include <windows.h>
#include <omp.h>

using namespace std;

const int ARR_NUM = 10000;                  // 待排序数组个数
const int ARR_LEN = 10000;                  // 每个数组长度
const int THREAD_NUM = 4;                   // 线程数
const int seg = ARR_NUM / THREAD_NUM;       // 每个线程负责数组个数

vector<int> arr[ARR_NUM];
long long head, freq, tail;        //timers

void arr_sort_s(void)
{
  for (int i = 0; i < ARR_NUM; i++)
    stable_sort(arr[i].begin(), arr[i].end());
}

void arr_sort_static(void)                  // 块划分：每个线程负责连续seg个数组的排序
{
#pragma omp parallel for num_threads(THREAD_NUM)
  for (int i = 0; i < ARR_NUM; i++)
    stable_sort(arr[i].begin(), arr[i].end());
}

void arr_sort_dynamic(void)             // 动态划分：每个线程每次获取50个(可调整粒度）数组进行排序
{
#pragma omp parallel for num_threads(THREAD_NUM) schedule(dynamic, 50)
  for (int i = 0; i < ARR_NUM; i++)
    stable_sort(arr[i].begin(), arr[i].end());
}

void arr_sort_guide(void)             // 自适应动态划分：每个线程每次获取的数组个数逐渐减少
{
#pragma omp parallel for num_threads(THREAD_NUM) schedule(static, 625)
  for (int i = 0; i < ARR_NUM; i++)
    stable_sort(arr[i].begin(), arr[i].end());
}

void init_2(void)
{
  int ratio;
  srand(unsigned(time(nullptr)));
  for (int i = 0; i < ARR_NUM; i++) {
    arr[i].resize(ARR_LEN);
    if (i < seg) ratio = 0;
    else if (i < seg * 2) ratio = 32;
    else if (i < seg * 3) ratio = 64;
    else ratio = 128;
    if ((rand() & 127) < ratio)
      for (int j = 0; j < ARR_LEN; j++)
        arr[i][j] = ARR_LEN - j;
    else
      for (int j = 0; j < ARR_LEN; j++)
        arr[i][j] = j;
  }
}

int main(int argc, char *argv[])
{
  QueryPerformanceFrequency((LARGE_INTEGER *)&freq);

 init_2();
 QueryPerformanceCounter((LARGE_INTEGER *)&head);
 arr_sort_s();
 QueryPerformanceCounter((LARGE_INTEGER *)&tail);
 printf("Sequential: %lfms.\n", (tail - head) * 1000.0 / freq);

 init_2();
 QueryPerformanceCounter((LARGE_INTEGER *)&head);
 arr_sort_static();
 QueryPerformanceCounter((LARGE_INTEGER *)&tail);
 printf("Static: %lfms.\n", (tail - head) * 1000.0 / freq);

 init_2();
 QueryPerformanceCounter((LARGE_INTEGER *)&head);
 arr_sort_dynamic();
 QueryPerformanceCounter((LARGE_INTEGER *)&tail);
 printf("Dynamic: %lfms.\n", (tail - head) * 1000.0 / freq);

  init_2();                                             // 测试自适应动态划分，前面代码测试其他算法
  QueryPerformanceCounter((LARGE_INTEGER *)&head);
  arr_sort_guide();
  QueryPerformanceCounter((LARGE_INTEGER *)&tail);
  printf("Guided: %lfms.\n", (tail - head) * 1000.0 / freq);

  system("PAUSE");
  return 0;
}

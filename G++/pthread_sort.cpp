#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <immintrin.h>
#include <windows.h>
#include <pthread.h>

using namespace std;

typedef struct{
  int  threadId;
} threadParm_t;

const int ARR_NUM = 10000;                  // 待排序数组个数
const int ARR_LEN = 10000;                  // 每个数组长度
const int THREAD_NUM = 4;                   // 线程数
const int seg = ARR_NUM / THREAD_NUM;       // 每个线程负责数组个数

vector<int> arr[ARR_NUM];
pthread_mutex_t  mutex;
long long head, freq;        //timers

void *arr_sort(void *parm)                  // 块划分：每个线程负责连续seg个数组的排序
{
  threadParm_t *p = (threadParm_t *) parm;
  int r = p->threadId;
  long long tail;

  for (int i = r * seg; i < (r + 1) * seg; i++)
    stable_sort(arr[i].begin(), arr[i].end());

  pthread_mutex_lock(&mutex);
  QueryPerformanceCounter((LARGE_INTEGER *)&tail);
  printf("Thread %d: %lfms.\n", r, (tail - head) * 1000.0 / freq);
  pthread_mutex_unlock(&mutex);

  pthread_exit(nullptr);
}

int next_arr = 0;
pthread_mutex_t  mutex_task;
void *arr_sort_fine(void *parm)             // 细粒度动态划分：每个线程每次获取一个数组进行排序
{
  threadParm_t *p = (threadParm_t *) parm;
  int r = p->threadId;
  int task = 0;
  long long tail;

  while (1) {
    pthread_mutex_lock(&mutex_task);
    task = next_arr++;
    pthread_mutex_unlock(&mutex_task);
    if (task >= ARR_NUM) break;
    stable_sort(arr[task].begin(), arr[task].end());
  }
  pthread_mutex_lock(&mutex);
  QueryPerformanceCounter((LARGE_INTEGER *)&tail);
  printf("Thread %d: %lfms.\n", r, (tail - head) * 1000.0 / freq);
  pthread_mutex_unlock(&mutex);

  pthread_exit(nullptr);
}

void *arr_sort_coarse(void *parm)             // 粗粒度动态划分：每个线程每次获取多个数组进行排序
{
  threadParm_t *p = (threadParm_t *) parm;
  int r = p->threadId;
  int task = 0;
  long long tail;

  while (1) {
    pthread_mutex_lock(&mutex_task);
    task = next_arr;
    next_arr += 625;                            // 每次获取625个，可调整
    pthread_mutex_unlock(&mutex_task);
    if (task >= ARR_NUM) break;
    for (int i = task; i < task + 625; i++)
			stable_sort(arr[i].begin(), arr[i].end());
  }
  pthread_mutex_lock(&mutex);
  QueryPerformanceCounter((LARGE_INTEGER *)&tail);
  printf("Thread %d: %lfms.\n", r, (tail - head) * 1000.0 / freq);
  pthread_mutex_unlock(&mutex);

  pthread_exit(nullptr);
}

void init_1(void)                               // 生成均匀初始数据
{
  srand(unsigned(time(nullptr)));
  for (int i = 0; i < ARR_NUM; i++) {
		arr[i].resize(ARR_LEN);
    for (int j = 0; j < ARR_LEN; j++)
      arr[i][j] = rand();
  }
}

void init_2(void)                               // 生成不均匀初始数据
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
  mutex = PTHREAD_MUTEX_INITIALIZER;
  mutex_task = PTHREAD_MUTEX_INITIALIZER;
  pthread_t thread[THREAD_NUM];
  threadParm_t threadParm[THREAD_NUM];

  QueryPerformanceCounter((LARGE_INTEGER *)&head);

  printf("测试粗粒度动态划分\n");                // 测试粗粒度动态划分，可修改（init和pthread_create）来测试块划分和细粒度
  for (int i = 0; i < THREAD_NUM; i++)
  {
    threadParm[i].threadId = i;
    pthread_create(&thread[i], nullptr, arr_sort_coarse, (void *)&threadParm[i]);
  }

  for (int i = 0; i < THREAD_NUM; i++)
  {
    pthread_join(thread[i], nullptr);
  }

  pthread_mutex_destroy(&mutex);

  system("PAUSE");
}

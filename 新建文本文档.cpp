#include "sort.h"
#include <iostream>

int main()
{
  CSoultion soultion;
  vector<int> vec;

  cout << "please input you need sort num: " << endl;
  int i;

  while (1)
  {
    cin >> i;
    if (i == 0)
    {
      break;
    }
    vec.push_back(i);
  }

  cout << "bubble sort begin: " << endl;
  vector<int> vecTemp = vec;
  soultion.BubbleSort(vecTemp);
  auto function = [&]() { for(auto elem : vecTemp){ cout << " " << elem;} };
  function();
  cout << endl;

  cout << "selection sort begin: " << endl;
  vecTemp.clear();
  vecTemp = vec;
  soultion.SelectionSort(vecTemp);
  function();
  cout << endl;

  cout << "quick sort begin: " << endl;
  vecTemp.clear();
  vecTemp = vec;
  soultion.QuickSort(vecTemp, 0, vecTemp.size() - 1);
  function();
  cout << endl;

  cout << "insert sort begin: " << endl;
  vecTemp.clear();
  vecTemp = vec;
  soultion.InsertionSort(vecTemp);
  function();
  cout << endl;

  cout << "shell sort begin: " << endl;
  vecTemp.clear();
  vecTemp = vec;
  soultion.ShellSort(vecTemp);
  function();
  cout << endl;

  cout << "merge sort begin: " << endl;
  vecTemp.clear();
  vecTemp = vec;
  vector<int> vecContain = vec;
  vecContain.clear();
  soultion.MergeSort(vecTemp, vecContain, 0, vecTemp.size() - 1);
  function();
  cout << endl;

  cout << "heap sort begin: " << endl;
  vecTemp.clear();
  vecTemp = vec;
  soultion.HeapSort(vecTemp);
  function();
  cout << endl;

  return 0;
}
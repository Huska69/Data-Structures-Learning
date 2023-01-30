//Please finish the function allocArray
//This function will allocate a 2-D array with size m * n, then point the array using pointer p.
//You will get 100 point if you can allocateconsecutive memory for this 2-D array.

#include <iostream>
#include <cstdlib>
using namespace std;

template <class T> class Memory 
{
public:
  static T **allocArray(int m, int n) 
  {
    T **arr1 = new int*[m];
    T *arr2 = new int[m * n];
    
    for(int i = 0; i < m; i++)
      arr1[i] = arr2 + i * n;
    
    return arr1;
   }
};

int main()
{
  int **array;
  array = Memory<int>::allocArray(5, 10);
  int j, k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      array[j][k] = j * 10 + k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      cout<<array[j][k]<<" ";
}

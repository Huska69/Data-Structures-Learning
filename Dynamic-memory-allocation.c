//Please finish the function allocArray
//This function will allocate a 2-D array with size m * n, then point the array using pointer p.
//You will get 100 point if you can allocateconsecutive memory for this 2-D array.

#include <stdio.h>
#include <stdlib.h>

void allocArray(double ***p, int m, int n)
{
  double **arr1 = (double**)malloc(sizeof(double*) * m);
  double *arr2 = (double*)malloc(sizeof(double) * m * n);
  
  for(int i = 0; i < m; i++)
      arr1[i] = arr2 + i * n;

  *p = arr1;
}

int main()
{
  double **array, *a;
  int j, k;
  allocArray(&array, 5, 10);
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      array[j][k] = j * 10 + k;
  for(j = 0;j < 5;j ++)
  {
    for(k = 0;k < 10;k ++)
      printf("%p ", &(array[j][k]));
    printf("\n");
  }
}

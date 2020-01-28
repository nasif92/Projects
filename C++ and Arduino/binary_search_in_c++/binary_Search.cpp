#include <iostream>

using namespace std;
int
binarySearch (const int value, const int *A, const int N)
{
  // TODO: Implement a binary search that returns
  // the index where all values in A are less than
  // the given value.
  int mid = (N / 2) - 1;
  int right = N;
  int left = 0;
  int index = 0;
  bool found = false;
  if ((value < A[0]) || (value > A[N - 1]))
    {
      index = -1;
    }
  else
    {
      index = -1;
      while ((left != right) && (!found))
{
 if (A[mid] == value)
   {
     index = mid;
     found = true;
   }
 else if (A[mid] > value)
   {
     right = mid;
     mid = (left + right - 1) / 2;
   }
 else if (A[mid] < value)
   {
     left = mid + 1;
     mid = (left + right - 1) / 2;
   }

}
    }
  return index;
}

int
main ()
{
  cout << "Hello World" << endl;
  int arr[] = { 1, 2, 3, 4, 5, 6 };
  int *p = arr;
  int n = binarySearch (4, p, 6);
  cout << n << endl;

  return 0;
}

#include <iostream>

using namespace std;

int binarySearch(const int value, const int *A, const int N){
	// TODO: Implement a binary search that returns
	// the index where all values in A are less than
	// the given value.
  // i is left and j is right
	int left = 0; 
  int right = N - 1; 
  int mid;
  if (value < A[0]){
		return 0;
	}
	else if (value > A[N - 1]){
		return N;
	}
  else{
    while (left <= right){
        mid = (left + right) / 2;
        if (A[mid] < value){
          left = mid + 1;
        }
        else{
          right = mid - 1;
        }
	  }
  }
	
}

int linearSearch(const int value, const int *A, const int N)
{
	// TODO: Implement a sequential search that returns
	// the index where all values in A are less than
	// the given value.
	int i = 0;
	while (*(A + i) < value){
		i += 1;
	}

	return i;
}

int main ()
{
  cout << "Hello World" << endl;
  int A[] = { 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,3,3,3,3,5};
  int B[] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2,3,3,3,3,5};
  int C[30] ;
  int x =0;
  int y = 0;
  int N = 15;
  // linear search here
  for (int i = 0; i < N; i++){
		x = linearSearch(A[i] , B, N);
    C[x + i ] = A[i];
    // cout << "X: " << x << endl;
    y = linearSearch(B[i]+ 1 , A, N);
    // cout << "Y: " << y << endl;

    C[y + i ] = B[i];
	}
  
  // cout << "Time required for linear search: " << duration.count() << endl;
 
  for ( int i = 0; i < 20; i++){
      cout << "Ouput: ";
      cout << C[i] << endl;
    }
     // binary search here
 
  
  for (int i = 0; i < N; i++){
		x = binarySearch(A[i] , B, N);
    C[x + i ] = A[i];
    // cout << "X: " << x << endl;
    y = binarySearch(B[i]+ 1 , A, N);
    // cout << "Y: " << y << endl;

    C[y + i ] = B[i];
	}
  // cout << "Time required for binary search: " << duration.count() << endl;
 
  for ( int i = 0; i < 20; i++){
    cout << "Ouput: ";
    cout << C[i] << endl;
  }
  

  return 0;
}

#include <iostream>

using namespace std;




int main(){

	int A[][3] = {{1,2,3}, {0,0,0}};
	int B[][2] = {{1,0}, {2,0}, {3,0}};
	int C[2][2] = {{0,0} , {0,0}};
	// the first row has the first x in 1st column multiplied by each element of the col of B
	int r1 = 2 , c2 = 2, c1 = 3;
	int x = 0;
	for(int i = 0; i < r1; i++){
		for(int j = 0; j < c2; j++){
			for(int k = 0; k < c1; k++){
            	C[i][j] += A[i][k] * B[k][j];
				
            }
		}
            
	}
        

	for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)
			cout << C[i][j] << endl;
}
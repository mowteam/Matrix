#include "matrix.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

void fillArray(double * arr, int size){
	for(int i = 0; i < size; ++i){
		arr[i] = rand() % 5;
	}
}

//bool testMatrixMult(){
//	srand(time(nullptr));
//	int count = 0;
//	while(true){
//		//determine dimensions
//		int row = rand() % 16;
//		int shared_dim = rand() % 16;
//		int col = rand() % 16;
//
//		//create arrays
//		double * arr1 = new double[row * shared_dim];
//		double * arr2 = new double[shared_dim * col];
//		fillArray(arr1, row * shared_dim);
//		fillArray(arr2, col * shared_dim);
//
//		//create matrices
//		Matrix m1 = Matrix(row, shared_dim, arr1);
//		Matrix m2 = Matrix(shared_dim, col, arr2);
//		Matrix re = m1.inefficientMatrixMult(m2);
//		Matrix re2 = m1 * m2;
//
//		delete[] arr1;
//		delete[] arr2;
//		if(!(re == re2)){
//			cout << m1 << endl;
//			cout << m2 << endl;
//			cout << re << endl;
//			cout << re2 << endl;
//			cout << count << endl;
//			return false;
//		}
//
//		if(count % 1000 == 0){
//			cout << count << endl;
//		}
//		++count;
//
//	}
//}


int main()
{

    return 0;

}






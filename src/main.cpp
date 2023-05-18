#include <iostream>
#include "matrix.h"
#include <stdlib.h>

using namespace std;

void fillArray(double * arr, int size){
	for(int i = 0; i < size; ++i){
		arr[i] = rand();
	}
}


int main() {
	double arr1[10]; fillArray(arr1, 10); // 5 x 2
	double arr2[4]; fillArray(arr2, 4); //2 x 2

	double arr3[10000]; fillArray(arr3, 10000); //100 x 100
	double arr4[4500]; fillArray(arr4, 4500); //100 x 45

	Matrix m1 = Matrix(5, 2, arr1);
	Matrix m2 = Matrix(2, 2, arr2);
    Matrix re = m1.inefficientMatrixMult(m2);

    cout << re << endl;
    // m1.printMatrix();
    // Matrix m2 = Matrix(2, 2);
    // m2.printMatrix();
    // cout << endl;
    // Matrix m3 = m1 + m2;
    // m3.printMatrix();
    return 0;
}






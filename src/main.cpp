#include <iostream>
#include "matrix.h"
#include <stdlib.h>

using namespace std;

void fillArray(double * arr, int size){
	for(int i = 0; i < size; ++i){
		arr[i] = rand() % 5;
	}
}

//bool testMatrixMult(){
////	srand(time(nullptr));
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
//	if(!testMatrixMult()){
//		cout << "ERROR" << endl;
//	}

    string lineBreak = "------------------------------------------";

    //Checking the Print Function and constructor 1
    Matrix m1 = Matrix(2, 3);
    m1.printMatrix();
    cout << endl;
    Matrix m2 = Matrix(2, 2);
    m2.printMatrix();
    cout << endl;
    Matrix m3 = m1 + m2;
    m3.printMatrix();
    cout << lineBreak << endl;

    //Checking the Addition Function and constructor 2
    double arr[4] = {-1, 4, 3, -2};
    Matrix test = Matrix(2, 2, arr);

    test.printMatrix();

    cout << endl;

    double arr2[4] = {2, -1, -4, +4};
    Matrix test2 = Matrix(2, 2, arr2);

    test2.printMatrix();

    cout << endl;

    Matrix test3 = test + test2;

    test3.printMatrix();

    cout << lineBreak << endl;

    return 0;
}






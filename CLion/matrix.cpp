//
// Created by Will Rosenberg on 1/1/23.
//

#include "matrix.h"
#include <iostream>

using namespace std;

Matrix::Matrix(int row1, int col1): row(row1), col(col1), arr(NULL) 
{
    arr = new double[row * col];
    for (int r = 0; r < row; r++) 
    {
        for (int c = 0; c < col; c++) 
        {
            double e;
            cout << "Element (" << r << ", " << c << "): ";
            while(!(cin >> e))
            {
                cout << "Element (" << r << ", " << c << "): ";
            }
            arr[toIndex(r, c)] = e;
        }
    }
}

 int Matrix::toIndex(int r, int c){
    return r * col + c;
 }

void Matrix::printMatrix()
{
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            cout << arr[toIndex(i, j)] << " ";
        }
        cout << endl;
    }
}
void Matrix::scalarMultiply()
{
    return;
}


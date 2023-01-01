//
// Created by Will Rosenberg on 1/1/23.
//

#include "matrix.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Matrix::Matrix(int row1, int col1): row(row1), col(col1), arr(NULL) 
{
    string line;
    stringstream iss;

    arr = new double[row * col];
    for (int r = 0; r < row; r++) 
    {
        for (int c = 0; c < col; c++) 
        {
            double e;
            do{
                iss.clear();
                line = "";
                cout << "Element (" << r << ", " << c << "): ";
                getline(cin, line); 
                iss << line;
            }
            while(!(iss >> e));

            arr[toIndex(r, c)] = e;
        }
    }
}

int Matrix::toIndex(int r, int c) const
{
    return r * col + c;
 }
 
int Matrix::getRow() const
{
    return row;
}

int Matrix::getCol() const
{
    return col;
}

ostream& operator<< (ostream& o, const Matrix& m){
    for(int i = 0; i < m.row; ++i)
    {
        for(int j = 0; j < m.col; ++j)
        {
            o << m.arr[m.toIndex(i, j)] << " ";
        }
        o << endl;
    }

    return o;
}

void Matrix::printMatrix() const
{
    cout << *this;
}

void Matrix::scalarMultiply()
{
    return;
}


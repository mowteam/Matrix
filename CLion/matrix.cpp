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

int Matrix::getSize() const 
{
    return getRow() * getCol();
}
 
int Matrix::getRow() const
{
    return row;
}

int Matrix::getCol() const
{
    return col;
}

double * Matrix::getArr() const
{
    return arr; 
}

Matrix Matrix::add(Matrix &m) const
{
    if ( row == m.getRow() && col == m.getCol() ) 
    {
        Matrix n = m;
        for (int i = 0; i < getSize(); ++i)
        {
            n.getArr()[i] += arr[i];
        }
        return n;
    }
    else
    {
        throw invalid_argument("invalid dimensions for addition operation");
    }
}

Matrix Matrix::operator+(Matrix &m) const 
{
    return add(m);
}

// Matrix Matrix::multiply(Matrix &m) const 
// {
//     if (col == m.getRow()) 
//     {
//         //Make a new matrix with the rows of the first and cols of the second 
//     }
// }

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


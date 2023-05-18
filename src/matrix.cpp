//
// Created by Will Rosenberg on 1/1/23.
//

#include "matrix.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Matrix::Matrix(int row1, int col1): row(row1), col(col1), arr(nullptr)
{
    arr = new double[row * col];
    for (int i = 0; i < row * col; ++i)
    {
		arr[i] = 0;
    }
}

Matrix::Matrix(int row1, int col1, double * inputArr): row(row1), col(col1), arr(nullptr)
{
    arr = new double[row * col];
    for (int i = 0; i < row * col; ++i)
    {
		arr[i] = inputArr[i];
    }
}

Matrix::Matrix(const Matrix & m):row(m.row), col(m.col), arr(nullptr){
    arr = new double[row * col];
    for(int i = 0; i < row * col; ++i){
        arr[i] = m.arr[i];
    }
}

Matrix::Matrix(Matrix && m):row(m.row), col(m.col), arr(m.arr){
    m.arr = nullptr;
    m.row = 0;
    m.col = 0;
}


Matrix & Matrix::operator=(const Matrix & m){
    if(&m != this){
        Matrix temp(m);
        swap(temp.row, row);
        swap(temp.col, col);
        swap(temp.arr, arr);
    }
    return *this; //destructor for temp will clean up resources
}

Matrix & Matrix::operator=(Matrix && m){
    if(&m != this){
        delete [] arr;
        row = m.row;
        col = m.col;
        arr = m.arr;

        m.row = 0;
        m.col = 0;
        m.arr = nullptr;
    }

    return *this;
}

Matrix::~Matrix(){
    delete[] arr;
}



Matrix Matrix::createMatrix(int row, int col){
	Matrix m = Matrix(row, col);
	string line;
	stringstream iss;

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

			m.arr[m.toIndex(r, c)] = e;
		}
	}

	return m;
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

void Matrix::blockMultiply(int row, int col, int block_num){

}


//matrix addition
Matrix Matrix::operator+(Matrix &m) const 
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

//matrix multiplication (cache efficient)
Matrix Matrix::operator*(Matrix &m) const 
{
    if(col != m.getRow()){
        throw invalid_argument("invalid dimensions for multiplication operation");
    }

    //create returned matrix
    int new_row = row;
    int new_col = m.getCol();
    Matrix n = Matrix(new_row, new_col);

    //perform block multiplication
    //iterate blocks within n
    for(int b_row = 0; b_row < new_row / BLOCK_SIZE; ++b_row){
        for(int b_col = 0; b_col < new_col / BLOCK_SIZE; ++b_col){

        	for(int k = 0; k < col / BLOCK_SIZE; ++k){
        		blockMultiply(b_row, b_col, k, n);
        	}

        }
    }

    //account for elements not in a block

    return n;
}

Matrix Matrix::inefficientMatrixMult(Matrix &m) const
{
	if(col != m.getRow()){
		throw invalid_argument("invalid dimensions for multiplication operation");
	}

    //create returned matrix
    int new_row = row;
    int new_col = m.getCol();
    Matrix n = Matrix(new_row, new_col);

    for(int i = 0; i < new_row; ++i){
    	for(int j = 0; j < new_col; ++j){

    		for(int k = 0; k < col; ++k){
    			n.getArr()[toIndex(i, j)] += arr[toIndex(i, k)] * m.getArr()[toIndex(k, j)];
    		}
    	}
    }

    return n;
}

//scalar multiply
Matrix Matrix::operator*(double a) const{
    Matrix n = *this;
    for(int i = 0; i < row * col; ++i){
        n.getArr()[i] *= a;
    }

    return n;
}

//scalar multiply
Matrix operator* (double a, const Matrix& m){
    Matrix n = m;
    for(int i = 0; i < m.getRow() * m.getCol(); ++i){
        n.getArr()[i] *= a;
    }

    return n;
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



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

Matrix::Matrix(const Matrix & m):row(m.row), col(m.col), arr(NULL){
    arr = new double[row * col];
    for(int i = 0; i < row * col; ++i){
        arr[i] = m.arr[i];
    }
}

Matrix::Matrix(Matrix && m):row(m.row), col(m.col), arr(m.arr){
    m.arr = NULL;
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
        m.arr = NULL;
    }

    return *this;
}

Matrix::~Matrix(){
    delete[] arr;
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

//matrix multiplication
Matrix Matrix::operator*(Matrix &m) const 
{
    if(col != m.getRow()){
        throw invalid_argument("invalid dimensions for multiplication operation");
    }

    //create returned matrix
    Matrix n = m;

    //iterate blocks within n
    for(int b_row = 0; b_row < row / BLOCK_SIZE; ++b_row){
        for(int b_col = 0; b_col < col / BLOCK_SIZE; ++b_col){

            //iterate within blocks of n
            for(int r = 0; r < BLOCK_SIZE; ++r){
                for(int c = 0; c < BLOCK_SIZE; ++c){

                    n.getArr()[b_row * BLOCK_SIZE + r][b_col * BLOCK_SIZE + c] = 0;

                    //iterate col to perform dot product
                    for(int k = 0; k < BLOCK_SIZE ++k){
                        n.getArr()[b_row * BLOCK_SIZE + r][b_col * BLOCK_SIZE + c] += arr[b_row * BLOCK_SIZE + r][b_row * BLOCK_SIZE + k] * m.getArr()[b_row * BLOCK_SIZE + k][b_col * BLOCK_SIZE + c];
                    }

                }
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



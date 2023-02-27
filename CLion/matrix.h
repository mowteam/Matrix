//
// Created by Will Rosenberg on 1/1/23.
//

#include <iostream>

BLOCK_SIZE = 8; //size for block matrix operations

class Matrix
{
    friend std::ostream& operator<< (std::ostream& o, const Matrix& m);
    friend Matrix operator* (int a, const Matrix& m);
private:
    int row;
    int col;
    double *arr;

public:
    //constructors
    Matrix(int row, int col);
    Matrix(const Matrix & m); //copy constructor
    Matrix(Matrix && m); //move constructor
    Matrix & operator=(const Matrix & m); //copy assignment operator
    Matrix & operator=(Matrix && m); //move assignment operator
    ~Matrix();

    //helper methods
    int toIndex(int row, int col) const;
    int getSize() const;
    int getRow() const;
    int getCol() const;
    double * getArr() const;

    //matrix operations
    Matrix operator+(Matrix &m) const;
    Matrix operator*(Matrix &m) const; //matrix mult
    Matrix operator*(double a) const;
    //Matrix transpose(Matrix &m) const;
    //double determinant(Matrix &m) const;
    void printMatrix() const;
};

std::ostream& operator<< (std::ostream& o, const Matrix& m);
Matrix operator* (double a, const Matrix& m);

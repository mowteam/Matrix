//
// Created by Will Rosenberg on 1/1/23.
//

#include <iostream>

class Matrix
{
    friend std::ostream& operator<< (std::ostream& o, const Matrix& m);
private:
    int row;
    int col;
    double *arr;
public:
    Matrix(int row, int col);
    Matrix(const Matrix & m); //copy constructor
    Matrix(const Matrix && m); //move constructor
    Matrix & operator=(const Matrix & m); //copy assignment operator
    Matrix & operator=(const Matrix && m); //move assignment operator
    ~Matrix();
    int toIndex(int row, int col) const;
    int getSize() const;
    int getRow() const;
    int getCol() const;
    double * getArr() const;
    Matrix operator+(Matrix &m) const;
    Matrix multiply(Matrix &m) const;
    void printMatrix() const;
    void scalarMultiply();
};

std::ostream& operator<< (std::ostream& o, const Matrix& m);

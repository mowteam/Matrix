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
    int toIndex(int row, int col) const;
    int getRow() const;
    int getCol() const;
    double * getArr() const;
    Matrix add(Matrix m) const;
    void printMatrix() const;
    void scalarMultiply();
};

std::ostream& operator<< (std::ostream& o, const Matrix& m);

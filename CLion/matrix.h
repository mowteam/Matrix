//
// Created by Will Rosenberg on 1/1/23.
//

class Matrix
{
private:
    int row;
    int col;
    double *arr;
public:
    Matrix(int row, int col);
    int toIndex(int row, int col);
    int getRow();
    int getCol();
    void printMatrix();
    void scalarMultiply();
};

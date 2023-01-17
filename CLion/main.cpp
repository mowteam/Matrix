#include <iostream>
#include "matrix.h"

using namespace std;

int main() {
    Matrix m1 = Matrix(2, 2);
    m1.printMatrix();
    Matrix m2 = Matrix(2, 2);
    m2.printMatrix();
    Matrix m3 = m1.add(m2);
    m3.printMatrix();
    return 0;
}




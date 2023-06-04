//
// Created by Will Rosenberg on 1/1/23.
//

#include "matrix.h"
#include "math.h"
#include <iostream>
#include <string>
#include <vector>
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

Matrix::Matrix(const Matrix & m):row(m.row), col(m.col), arr(nullptr)
{
    arr = new double[row * col];
    for(int i = 0; i < row * col; ++i){
        arr[i] = m.arr[i];
    }
}

Matrix::Matrix(Matrix && m):row(m.row), col(m.col), arr(m.arr)
{
    m.arr = nullptr;
    m.row = 0;
    m.col = 0;
}


Matrix & Matrix::operator=(const Matrix & m)
{
    if(&m != this)
    {
        Matrix temp(m);
        swap(temp.row, row);
        swap(temp.col, col);
        swap(temp.arr, arr);
    }
    return *this; //destructor for temp will clean up resources
}

Matrix & Matrix::operator=(Matrix && m)
{
    if(&m != this)
    {
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

Matrix::~Matrix()
{
    delete[] arr;
}



Matrix Matrix::createMatrix(int row, int col)
{
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
    return row * col;
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

int Matrix::gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
        return gcd(b, a % b);
}

int Matrix::lcm(double a, double b)
{
    return (a * b) / gcd(a, b);
}

Matrix Matrix::rrefComplete() //Reduces the matrix to its most simple row equivalent form
{
    Matrix copy = this->rref();

    for (int cols = copy.getCol() - 1; cols > -1; cols--)
    {
        int startingRow = copy.getRow() - (copy.getCol() - cols);
        for (int rows = startingRow - 1; rows > -1; rows--) //Need to fix this, different when starting at the bottom right of a m != n matrix
        {
            int a = copy.arr[copy.toIndex(startingRow, cols)]; //Change this
            int b = copy.arr[copy.toIndex(rows, cols)];
            if ( a < 0 )
            {
                a *= -1;
                for (int i = 0; i < copy.getCol(); ++i)
                {
                    if (copy.arr[copy.toIndex(startingRow, i)] != 0)
                    {
                        copy.arr[copy.toIndex(startingRow, i)] *= -1;
                    }
                }
            }
            if ( b < 0 )
            {
                b *= -1;
                for (int i = 0; i < copy.getCol(); ++i)
                {
                    if (copy.arr[copy.toIndex(rows, i)] != 0)
                    {
                        copy.arr[copy.toIndex(rows, i)] *= -1;
                    }
                }
            }
            double lcm = copy.lcm(a, b);
            double multipleA = lcm / a;
            double multipleB = lcm / b;

            //Multiply each row so the leading elements are the same
            for (int column = 0; column < copy.getCol(); column++)
            {
                copy.arr[copy.toIndex(startingRow, column)] *= multipleA;
                copy.arr[copy.toIndex(rows, column)] *= multipleB;
            }
            //Perform necessary row operations
            copy.rrefHelper(copy, startingRow, rows);

            //Divide each resulting row by their GCD
            int rowGCDA = gcdRowOperation(copy, startingRow);
            int rowGCDB = gcdRowOperation(copy, rows);

            for (int column = 0; column < copy.getCol(); column++)
            {
                copy.arr[copy.toIndex(startingRow, column)] /= rowGCDA;
                copy.arr[copy.toIndex(rows, column)] /= rowGCDB;
            }
        }
    }
    return copy;
}

Matrix Matrix::rref() //Reduces the matrix to an upper triangular row equivalent matrix
{
    Matrix copy = *this;
    for (int cols = 0; cols < copy.getCol(); cols++)
    {
        for (int rows = cols + 1; rows < copy.getRow(); rows++)
        {
            int a = copy.arr[copy.toIndex(cols, cols)]; //Note that the first row always matches the col
            int b = copy.arr[copy.toIndex(rows, cols)];
            if ( a < 0 )
            {
                a *= -1;
                for (int i = 0; i < copy.getCol(); ++i)
                {
                    if (copy.arr[copy.toIndex(cols, i)] != 0)
                    {
                        copy.arr[copy.toIndex(cols, i)] *= -1;
                    }
                }
            }
            if ( b < 0 )
            {
                b *= -1;
                for (int i = 0; i < copy.getCol(); ++i)
                {
                    if (copy.arr[copy.toIndex(rows, i)] != 0)
                    {
                        copy.arr[copy.toIndex(rows, i)] *= -1;
                    }
                }
            }
            double lcm = copy.lcm(a, b);
            double multipleA = lcm / a;
            double multipleB = lcm / b;

            //Multiply each row so the leading elements are the same
            for (int column = 0; column < copy.getCol(); column++)
            {
                copy.arr[copy.toIndex(cols, column)] *= multipleA;
                copy.arr[copy.toIndex(rows, column)] *= multipleB;
            }
            //Perform necessary row operations
            copy.rrefHelper(copy, cols, rows);

            //Divide each resulting row by their GCD
            int rowGCDA = gcdRowOperation(copy, cols);
            int rowGCDB = gcdRowOperation(copy, rows);

            for (int column = 0; column < copy.getCol(); column++)
            {
                copy.arr[copy.toIndex(cols, column)] /= rowGCDA;
                copy.arr[copy.toIndex(rows, column)] /= rowGCDB;
            }
        }
    }
    return copy;
}

void Matrix::rrefHelper(Matrix & A, int row_m, int row_n)
{
    for (int column = 0; column < A.getCol(); column++)
    {
        int difference = A.arr[A.toIndex(row_n, column)] - A.arr[A.toIndex(row_m, column)];
        if (difference == -0)
        {
            difference = 0;
        }
        A.arr[A.toIndex(row_n, column)] = difference;
    }
}

Matrix Matrix::transpose() const
{
	Matrix n = Matrix(col, row); //switch row and col
	for(int i = 0; i < row; ++i)
    {
		for(int j = 0; j < col; ++j)
        {
			n.arr[n.toIndex(j, i)] = arr[toIndex(i, j)];
		}
	}

	return n;
}


int Matrix::gcdRowOperation(const Matrix A, int row)
{
    int result = A.arr[A.toIndex(row, 0)];
    for (int i = 1; i < A.getCol(); ++i)
    {
        result = gcd(abs(A.arr[A.toIndex(row, i)]), result);
    }
    return result;
}

double Matrix::determinant() const
{
    Matrix m = *this;
    if ( m.getRow() != m.getCol() )
    {
        throw exception(invalid_argument("Determinant is undefined."));//Change this to some null value
    }
    else
    {
        return detHelper(m);

    }
}

double Matrix::detHelper(Matrix m) const
{
    double determinant = 0;
    if (m.getRow() == 2)
    {
        return (m.arr[m.toIndex(0,0)] * m.arr[m.toIndex(1,1)] ) - (m.arr[m.toIndex(0,1)] * m.arr[m.toIndex(1,0)]);
    }
    else
    {
        for (int i = 0; i < m.getCol(); ++i)
        {
            double * arr = new double[(m.getRow() - 1) * (m.getCol() - 1)];
            int arrIndex = 0;
            for (int row = 0; row < m.getRow(); row++)
            {
                for (int col = 0; col < m.getCol(); col++)
                {
                    if (row != 0 && col != i) //We are always choosing the first row to iterate across for the determinant
                    {
                        arr[arrIndex] = m.arr[toIndex(row, col)];
                        arrIndex++;
                    }
                }
            }
            Matrix n = Matrix(m.getRow() - 1, m.getCol() - 1, arr);
            delete[] arr;
            determinant += m.arr[i] * pow(-1, i) * n.detHelper(n);
        }
        return determinant;
    }
}
Matrix Matrix::inverse() const
{
    Matrix m = Matrix(this->row, this->col);
    double determinant = this->determinant(); //exception from determinant will be thrown for non-square matrices
    if (determinant == 0)
    {
        cout << "Inverse does not exist." << endl;
        return m;
    }
    else
    {
        //Constructing the adjunct matrix
        for (int i = 0; i < this->getRow(); ++i)
        {
            for (int j = 0; j < this->getCol(); ++j)
            {
                double *arr = new double[(this->getRow() - 1) * (this->getCol() - 1)];
                int arrIndex = 0;
                for (int row = 0; row < this->getRow(); row++) {
                    for (int col = 0; col < this->getCol(); col++) {
                        if (row != i && col != j)
                        {
                            arr[arrIndex] = this->arr[toIndex(row, col)];
                            arrIndex++;
                        }
                    }
                }
                Matrix n = Matrix(this->getRow() - 1, this->getCol() - 1, arr);
                delete[] arr;
                m.arr[toIndex(i, j)] = pow(-1, i + j) * n.determinant();
            }
        }

        m = m.transpose();
        m = m * (1 / determinant);

        //Getting rid of issue with negative zero values
        for (int i = 0; i < m.getSize(); ++i)
        {
            if (m.arr[i] == 0)
            {
                m.arr[i] = 0;
            }
        }
        return m;
    }
}

bool Matrix::operator==(Matrix &m) const
{
	if(row != m.row || col != m.col)
    {
		return false;
	}

	for(int i = 0; i < getSize(); ++i)
    {
		if(arr[i] != m.arr[i])
        {
			return false;
		}
	}
	return true;
}

bool Matrix::operator!=(Matrix &m) const
{
	return !(*this == m);
}


//matrix addition
Matrix Matrix::operator+(Matrix &m) const 
{
    if ( row == m.row && col == m.col)
    {
        Matrix n = m;
        for (int i = 0; i < getSize(); ++i)
        {
            n.arr[i] += arr[i];
        }
        return n;
    }
    else
    {
        throw exception(invalid_argument("Invalid arguments for addition."));
    }
}

//matrix multiplication (cache efficient)
//Matrix Matrix::operator*(Matrix &m) const
//{
//    if(col != m.row){
//        throw invalid_argument("invalid dimensions for multiplication operation");
//    }
//
//    //create returned matrix
//    int new_row = row;
//    int new_col = m.col;
//    Matrix n = Matrix(new_row, new_col); //filled with zeros
//
//    //perform block multiplication
//    //iterate blocks within the new matrix
//    for(int b_row = 0; b_row <= new_row - BLOCK_SIZE; b_row+=BLOCK_SIZE){
//        for(int b_col = 0; b_col <= new_col - BLOCK_SIZE; b_col+=BLOCK_SIZE){
//        	//iterate the row/column of blocks that create the corresponding block in the new matrix
//        	for(int k = 0; k <= col - BLOCK_SIZE; k+=BLOCK_SIZE){
//
//        		//multiply blocks
//				for(int r = 0; r < BLOCK_SIZE; ++r){
//					for(int c = 0; c < BLOCK_SIZE; ++c){
//						for(int kk = 0; kk < BLOCK_SIZE; ++kk){
//							n.arr[n.toIndex(b_row + r, b_col + c)] += arr[toIndex(b_row + r, k + kk)] * m.arr[m.toIndex(k + kk, b_col + c)];
//						}
//					}
//				}
//
//        	}
//
//        }
//    }
//
//    //account for elements not in a block
//    //when rows are not in a block and columns are
//    for(int r = (new_row / BLOCK_SIZE) * BLOCK_SIZE; r < new_row; r++){
//		for(int b_col = 0; b_col <= new_col - BLOCK_SIZE; b_col+=BLOCK_SIZE){
//			//iterate the row/column of blocks that create the corresponding block in the new matrix
//			for(int k = 0; k <= col - BLOCK_SIZE; k+=BLOCK_SIZE){
//
//				//multiply blocks
//				for(int r = 0; r < BLOCK_SIZE; ++r){
//					for(int c = 0; c < BLOCK_SIZE; ++c){
//						for(int kk = 0; kk < BLOCK_SIZE; ++kk){
//							n.arr[n.toIndex(b_row + r, b_col + c)] += arr[toIndex(b_row + r, k + kk)] * m.arr[m.toIndex(k + kk, b_col + c)];
//						}
//					}
//				}
//
//			}
//
//		}
//	}
////    if(b_row + BLOCK_SIZE > new_row || b_col + BLOCK_SIZE > new_col){
////		for(int r = b_row; r < new_row; ++r){
////			for(int c = b_col; c < new_col; ++c){
////				for(int kk = k; kk < col; ++kk){
////					n.arr[n.toIndex(r, c)] += arr[toIndex(r, kk)] * m.arr[m.toIndex(kk, c)];
////				}
////			}
////		}
////	}
//
//    return n;
///}

Matrix Matrix::inefficientMatrixMult(Matrix &m) const
{
	if(col != m.row)
    {
		throw invalid_argument("invalid dimensions for multiplication operation");
	}

    //create returned matrix
    int new_row = row;
    int new_col = m.col;
    Matrix n = Matrix(new_row, new_col);

    for(int i = 0; i < new_row; ++i){
    	for(int j = 0; j < new_col; ++j){

    		for(int k = 0; k < col; ++k){
    			n.arr[n.toIndex(i, j)] += arr[toIndex(i, k)] * m.arr[m.toIndex(k, j)];
    		}
    	}
    }

    return n;
}

//scalar multiply
Matrix Matrix::operator*(double a) const
{
    Matrix n = *this;
    for(int i = 0; i < getSize(); ++i)
    {
        n.arr[i] *= a;
    }

    return n;
}

//scalar multiply
Matrix operator* (double a, const Matrix& m)
{
    Matrix n = m;
    for(int i = 0; i < m.getSize(); ++i)
    {
        n.getArr()[i] *= a;
    }

    return n;
}


ostream& operator<< (ostream& o, const Matrix& m)
{
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



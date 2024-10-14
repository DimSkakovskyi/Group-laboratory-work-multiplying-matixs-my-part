#include <stdexcept>
#include <iostream>

class Complex {
private:
   float real;
   float imag;

public:
    Complex(float real, float imag) : real(real), imag(imag) {}
    Complex() : real(0), imag(0) {}


    Complex operator+(const Complex& other) const {
        return Complex(real + other.getReal(), imag + other.getImag());
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.getReal(), imag - other.getImag());
    }

    Complex operator*(const Complex& other) {
        float r = real * other.getReal() - imag * other.getImag();
        float i = real * other.getImag() + imag * other.getReal();
        return Complex(r, i);
    }

    // Getter for the real part
    double getReal() const {
        return real;
    }

    // Getter for the imaginary part
    double getImag() const{
        return imag;
    }
};


class Matrix {
private:
    Complex** matrix;
    int rows;
    int cols;
public:
    Matrix(int rows, int cols) : rows(rows), cols(cols){
        matrix = new Complex*[rows];
        for(int i = 0; i < cols; i++){
            matrix[i] = new Complex[cols];
        }
    }

    ~Matrix(){
        for (int i = 0; i < rows; ++i) {
            delete matrix[i];  
        }
         delete matrix;
    }

    Complex getElement(int row, int col) const{
        if(row > rows || row < 0 || col > cols || col < 0){
            throw std::invalid_argument("Invalid col or row argument");
        }
        return matrix[row][col];
    }

    void setElement(int row, int col, const Complex& value){
        if(row > rows || row < 0 || col > cols || col < 0){
            throw std::invalid_argument("Invalid col or row argument");
        }
        matrix[row][col] = value;
    }

    void DivideMatrixInFourPart(){
        
    }


    Matrix operator+(Matrix& other) const{
        Matrix sum(rows, cols);

        for(int row = 0; row < rows; row++) {
            for(int col = 0; col < cols; col++){
                sum.setElement(row, col, getElement(row, col) + other.getElement(row, col)); 
            }
        }
        return sum;
    }

    Matrix operator-(Matrix& other) {
        Matrix minus(rows, cols);

        for(int row = 0; row < rows; row++) {
            for(int col = 0; col < cols; col++){
                minus.setElement(row, col, getElement(row, col) - other.getElement(row, col)); 
            }
        }
        return minus;
    }

    Matrix operator*(Matrix& other) {
        Matrix mult = (rows, cols);

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                for (int k = 0; k < 256; k++) {
                    mult.setElement(row, col, mult.getElement(row, col) + (getElement(row, k) * other.getElement(k, col)));
                }
            }
        }

        return mult;
    }


};

Matrix strassen(Matrix A, Matrix B, int N) {

	// Base case
	if (N == 1) {
		return (A*B);
	}

	// Create a new matrix to hold the result
	Matrix C = Matrix(N, N);

	int K = N / 2;

	// New sub-matrices
	Matrix A11 = Matrix(K, K);
	Matrix A12 = Matrix(K, K);
	Matrix A21 = Matrix(K, K);
	Matrix A22 = Matrix(K, K);
	Matrix B11 = Matrix(K, K);
	Matrix B12 = Matrix(K, K);
	Matrix B21 = Matrix(K, K);
	Matrix B22 = Matrix(K, K);


	// Populate the values accordingly
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			A11[i][j] = A[i][j];
			A12[i][j] = A[i][K + j];		
			A21[i][j] = A[K + i][j];
			A22[i][j] = A[K + i][K + j];
			B11[i][j] = B[i][j];
			B12[i][j] = B[i][K + j];		
			B21[i][j] = B[K + i][j];
			B22[i][j] = B[K + i][K + j];
		}
	}

	// M
	Matrix M1 = strassen(A11+A22, B11+B22, K);
    Matrix M2 = strassen(A21+A22, B11, K);
    Matrix M3 = strassen(A11, B12-B22, K);
    Matrix M4 = strassen(A22, B21-B11, K);
    Matrix M5 = strassen(A11+A12, B22, K);
    Matrix M6 = strassen(A21-A11, B11+B12, K);
    Matrix M7 = strassen(A12-A22, B21+B22, K);

	// C_i	
	Matrix C11 = M1 + M4 - M5 + M7;				
	Matrix C12 = M3 + M5;
	Matrix C21 = M2 + M4;
	Matrix C22 = M1 - M2 + M3 + M6;

	// C
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {

			C[i][j] = C11[i][j];

			C[i][j + K] = C12[i][j];

			C[K + i][j] = C21[i][j];

			C[K + i][K + j] = C22[i][j];
		}
	}

	// Return the result
	return C;
}

int main(){
    // const some = new Matrix(4, 4);

    return 0;
}
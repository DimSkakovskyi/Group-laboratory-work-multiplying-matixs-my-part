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

    void print() const {
        if (imag >= 0)
            std::cout << real << " + " << imag << "i";
        else
            std::cout << real << " - " << -imag << "i";
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

    void printMatrix(int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j].print();
            std::cout << "\t";  
        }
        std::cout << std::endl;
    }
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
        Matrix mult = Matrix(rows, cols);

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
	    std::cout<<"Ok";
		return (A*B);
	}
	
	std::cout<<"Ok";

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
	std::cout<<"Ok";


	// Populate the values accordingly
	for (int row = 0; row < K; row++) {
		for (int col = 0; col < K; col++) {
			// A11->matrix[i][j] = A->matrix[i][j];
			// A12->matrix[i][j] = A->matrix[i][K + j];		
			// A21->matrix[i][j] = A->matrix[K + i][j];
			// A22->matrix[i][j] = A->matrix[K + i][K + j];
			// B11->matrix[i][j] = B->matrix[i][j];
			// B12->matrix[i][j] = B->matrix[i][K + j];		
			// B21->matrix[i][j] = B->matrix[K + i][j];
			// B22->matrix[i][j] = B->matrix[K + i][K + j];

            
            A11.setElement(row, col, A.getElement(row, col));
            A12.setElement(row, col, A.getElement(row, K + col));
            A21.setElement(row, col, A.getElement(K + row, col));
            A22.setElement(row, col, A.getElement(K + row, K + col));
            B11.setElement(row, col, B.getElement(row, col));
            B12.setElement(row, col, B.getElement(row, K + col));
            B21.setElement(row, col, B.getElement(K + row, col));
            B22.setElement(row, col, B.getElement(K + row, K + col));
		}
	}
	
	std::cout<<"Ok";

	// M
	Matrix M1 = strassen(A11+A22, B11+B22, K);
    Matrix M2 = strassen(A21+A22, B11, K);
    Matrix M3 = strassen(A11, B12-B22, K);
    Matrix M4 = strassen(A22, B21-B11, K);
    Matrix M5 = strassen(A11+A12, B22, K);
    Matrix M6 = strassen(A21-A11, B11+B12, K);
    Matrix M7 = strassen(A12-A22, B21+B22, K);
    
    std::cout<<"Ok";

	// C_i	
	Matrix C11 = M1 + M4 - M5 + M7;				
	Matrix C12 = M3 + M5;
	Matrix C21 = M2 + M4;
	Matrix C22 = M1 - M2 + M3 + M6;
	
	std::cout<<"Ok";

	// C
	for (int row = 0; row < K; row++) {
		for (int col = 0; col < K; col++) {

			// C[i][j] = C11[i][j];

			// C[i][j + K] = C12[i][j];

			// C[K + i][j] = C21[i][j];

			// C[K + i][K + j] = C22[i][j];

            C.setElement(row, col, C11.getElement(row, col));
            C.setElement(row, col + K, C12.getElement(row, col));
            C.setElement(K + row, col, C21.getElement(row, col));
            C.setElement(K + row, K + col, C22.getElement(row, col));
		}
	}
	
	std::cout<<"Ok";

	// Return the result
	return C;
}

int main(){
    // const some = new Matrix(4, 4);
    int N = 4; // size of the matrix
    Matrix matrixA(N, N);
    Matrix matrixB(N, N);

    // Fill matrixA with complex numbers
    matrixA.setElement(0, 0, Complex(1, 1));
    matrixA.setElement(0, 1, Complex(2, 2));
    matrixA.setElement(0, 2, Complex(3, 3));
    matrixA.setElement(0, 3, Complex(4, 4));

    matrixA.setElement(1, 0, Complex(5, 5));
    matrixA.setElement(1, 1, Complex(6, 6));
    matrixA.setElement(1, 2, Complex(7, 7));
    matrixA.setElement(1, 3, Complex(8, 8));

    matrixA.setElement(2, 0, Complex(9, 9));
    matrixA.setElement(2, 1, Complex(10, 10));
    matrixA.setElement(2, 2, Complex(11, 11));
    matrixA.setElement(2, 3, Complex(12, 12));

    matrixA.setElement(3, 0, Complex(13, 13));
    matrixA.setElement(3, 1, Complex(14, 14));
    matrixA.setElement(3, 2, Complex(15, 15));
    matrixA.setElement(3, 3, Complex(16, 16));

    // Fill matrixB with complex numbers
    matrixB.setElement(0, 0, Complex(16, 16));
    matrixB.setElement(0, 1, Complex(15, 15));
    matrixB.setElement(0, 2, Complex(14, 14));
    matrixB.setElement(0, 3, Complex(13, 13));

    matrixB.setElement(1, 0, Complex(12, 12));
    matrixB.setElement(1, 1, Complex(11, 11));
    matrixB.setElement(1, 2, Complex(10, 10));
    matrixB.setElement(1, 3, Complex(9, 9));

    matrixB.setElement(2, 0, Complex(8, 8));
    matrixB.setElement(2, 1, Complex(7, 7));
    matrixB.setElement(2, 2, Complex(6, 6));
    matrixB.setElement(2, 3, Complex(5, 5));

    matrixB.setElement(3, 0, Complex(4, 4));
    matrixB.setElement(3, 1, Complex(3, 3));
    matrixB.setElement(3, 2, Complex(2, 2));
    matrixB.setElement(3, 3, Complex(1, 1));

    matrixA.printMatrix(N);
    matrixB.printMatrix(N);

    Matrix C = strassen(matrixA, matrixB, N);
    C.printMatrix(N);

    return 0;
}
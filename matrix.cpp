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
        // TODO: implement right destructor
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
        // Check id other matrix have same size
    
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

    // matrix operator*(matrix& other) {
    //     matrix* mult = new matrix;

    //     for (int i = 0; i < 256; i++) {
    //     for (int j = 0; j < 256; j++) {
    //         for (int k = 0; k < 256; ++k) {
    //             *mult->array[i][j] = *mult->array[i][j] + (*array[i][k] * *other.array[k][j]);
    //         }
    //     }
    //     }

    //     return *mult;
    // }


};

int main(){
    // const some = new Matrix(4, 4);

    return 0;
}
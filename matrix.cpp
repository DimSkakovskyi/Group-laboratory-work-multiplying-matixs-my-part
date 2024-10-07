class Complex {
private:
   float real;
   float imag;

public:
    Complex operator+(Complex& other) {
        Complex* sum = new Complex;
        sum->real = real + other.real;
        sum->imag = imag + other.imag;
        return *sum;
    }

    Complex operator-(Complex& other) {
        Complex* sub = new Complex;
        sub->real = real + other.real;
        sub->imag = imag + other.imag;
        return *sub;
    }

    Complex operator*(Complex& other) {
        Complex* mult = new Complex;
        mult->real = real * other.real - imag * other.imag;
        mult->imag = real * other.imag + imag * other.real;
        return *mult;
    }

    // Getter for the real part
    double getReal() {
        return real;
    }

    // Getter for the imaginary part
    double getImag() {
        return imag;
    }
};

class matrix {
private:
    Complex* array[256][256];

public:
    matrix operator+(matrix& other) {
        matrix* sum = new matrix;
        for(int i = 0; i < 256; i++) {
            for(int j = 0; j < 256; j++){
                *sum->array[i][j] = *array[i][j] + *other.array[i][j];
            }
        }

        return *sum;
    }

    matrix operator-(matrix& other) {
        matrix* minus = new matrix;
        for(int i = 0; i < 256; i++) {
            for(int j = 0; j < 256; j++){
                *minus->array[i][j] = *array[i][j] - *other.array[i][j];
            }
        }

        return *minus;
    }

    matrix operator*(matrix& other) {
        matrix* mult = new matrix;

        for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int k = 0; k < 256; ++k) {
                *mult->array[i][j] = *mult->array[i][j] + (*array[i][k] * *other.array[k][j]);
            }
        }
        }

        return *mult;
    }


};
class complexNum {
private:
   float real
   float imag;

public:
    Complex operator+(Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(Complex& other) {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(Complex& other) {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }

    // Getter for the real part
    double getReal() {
        return real;
    }

    // Getter for the imaginary part
    double getImag() {
        return imag;
    }

    void display() {
        if (imag < 0)
            cout << real << " - " << -imag << "i" << endl;
        else
            cout << real << " + " << imag << "i" << endl;
    }
};

class matrix {
private:
    
};
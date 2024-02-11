#include <iostream>


class Complex{
public:
    double real;
    double img;

    Complex(double real, double img){
        this->real = real;
        this->img = img;
    }

    Complex operator + (Complex a) const{
        return {this->real + a.real, this->img + a.img};
    }

    Complex operator - (Complex a) const{
        return {this->real - a.real, this->img - a.img};
    }

    Complex operator * (Complex a) const{
        return {this->real * a.real - this->img * a.img, this->real * a.img + this->img * a.real};
    }

    Complex operator / (Complex a) const{
        return {(this->real * a.real + this->img * a.img) / (a.real * a.real + a.img * a.img),
                (a.real * this->img - this->real * a.img) / (a.real * a.real + a.img * a.img)};
    }

    void print() const{
        printf("%lf", this->real);
        if (this->img < 0) printf(" - %lfi", -this->img);
        else printf(" + %lfi", this->img);
    }
};


int main(){
    Complex a = Complex(4, 8);
    Complex b = Complex(7, -6);
    Complex d = Complex(2, 2);
    Complex c = a + b * d;

    c.print();
    return 0;
}

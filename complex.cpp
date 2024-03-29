#include <iostream>


class Complex{
public:
    double real;
    double img;

    Complex(double real = 0, double img = 0){
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

    Complex sopr() {
        return {this->real, -this->img};
    }

    Complex operator / (double d) const{
        return {this->real / d, this->img / d};
    }

    Complex operator / (Complex a) const{
        double d = a.real * a.real + a.img * a.img;
        return {(*this * a.sopr()) / d};
    }

    void print() const{
        printf("%lf", this->real);
        if (this->img < 0) printf(" - %lfi\n", -this->img);
        else printf(" + %lfi\n", this->img);
    }
};


int main(){
    using namespace std;

    printf("input complex number a: \n     real part: ");
    double real; cin >> real;
    printf("    imagine part: ");
    double img; cin >> img;

    Complex a = Complex(real, img);

    printf("\ninput complex number b: \n     real part: ");
    cin >> real;
    printf("    imagine part: ");
    cin >> img;

    Complex b = Complex(real, img);

    Complex c = a + b;

    cout << "\n'+': ";
    c.print();

    c = a - b;
    cout << "\n'-': ";
    c.print();

    c = a * b;
    cout << "\n'*': ";
    c.print();

    c = a / b;
    cout << "\n'/': ";
    c.print();

    return 0;
}

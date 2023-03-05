# Operator Overloading
Refer this: https://www.geeksforgeeks.org/overloading-stream-insertion-operators-c/
```cpp
#include <iostream>

class Complex{
private:
    int real, imaginary;
public:
    Complex(int real, int imaginary){
        this->real = real;
        this->imaginary = imaginary;
    }

    // we have to make this friend because we have to define this function globally. 
    // why globally? Because when std::cout << c is executed, the linker will look for a method in ostream class for the overloaded operator. Since we cannot 
    // define this function in the ostream class, we have to make this function as global.
    friend std::ostream& operator << (std::ostream& out, Complex c);
    friend Complex operator+ (int r, Complex c);
};

std::ostream& operator << (std::ostream &out, Complex c){
    out << "Real: " << c.real;
    out << ", Imaginary: " << c.imaginary << std::endl;
    return out;
}

Complex operator+(int r, Complex c){
    Complex c2 = c;
    c2.real += r;
    return c2;
}


int main(){

    Complex c(1, 2);
    operator << (std::cout, c);

    std::cout << 3 + c << std::endl;

    return 0;
}
```

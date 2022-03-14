#include <iostream>
#include <cmath>
#include <iomanip>

double calculate_pi(int termCount){
    double sum = 0.0;

    for(int i = 0; i < termCount; i++){

        int sign = std::pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }
    return sum * 4;
}

int main(){
    std::cout << std::setprecision(15) << calculate_pi(1E6) << std::endl;
    return 0;
}
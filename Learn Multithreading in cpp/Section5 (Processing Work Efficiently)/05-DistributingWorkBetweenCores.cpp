#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <thread>
#include <future>

//CALCULATING PI ON DIFFERENT THREADS
double calculate_pi(int termCount, int start, int skip){
    double sum = 0.0;

    for(int i = start; i < termCount; i += skip){

        int sign = std::pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }
    return sum * 4;
}

int main(){
    std::vector<std::shared_future<double>> futures;
    
    int CONCURRENCY = std::thread::hardware_concurrency();
    int terms = 1E7;

    for(int i = 0; i < CONCURRENCY; i++){
        std::shared_future<double> f = std::async(std::launch::async, calculate_pi, terms, i, CONCURRENCY);
        futures.push_back(f);
    }

    double sum = 0;
    for(auto f: futures){
        sum += f.get();
    }

    std::cout << std::setprecision(15) << "Value Of pi: " << sum << std::endl;
}
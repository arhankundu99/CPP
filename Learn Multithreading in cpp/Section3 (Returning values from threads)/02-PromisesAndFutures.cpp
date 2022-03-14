#include <iostream>

#include <thread>

#include <cmath>
#include <iomanip>

#include <future>

void calculate_pi(int termCount, std::promise <double>& promise){
    double sum = 0.0;

    for(int i = 0; i < termCount; i++){

        int sign = std::pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }

    promise.set_value(sum * 4);
    
}

int main(){

    //promise is an object which is used by the asynchronous producer code to store the result.
    std::promise <double> promise;
    
    //future is an object which is used by the asynchronous consumer code to get the stored result from a promise.
    std::future <double> future = promise.get_future();
    
    //why are we separating promise and future?
    //The reason it is separated into these two separate "interfaces" is to hide the "write/set" functionality from the "consumer/reader".
    
    std::thread t(calculate_pi, 1E6, std::ref(promise));
    
    //future.get() is a blocking code, that means until the thread t is done calculating, the code after wont get executed
    //So no need for t.join() here
    double pi = future.get();

    std::cout << std::setprecision(15) << pi << std::endl;

    t.join();

    return 0;
}
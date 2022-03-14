#include <iostream>

#include <thread>

#include <cmath>
#include <iomanip>

#include <future>

#include <exception>

double calculate_pi(int termCount){
    if(termCount < 1)throw std::runtime_error("Terms cannot be less than one.");
    double sum = 0.0;

    for(int i = 0; i < termCount; i++){

        int sign = std::pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }

    return 4 * sum;
    
}

int main(){

    int number_of_terms = 0;
    //promise is an object which is used by the asynchronous producer code to store the result.
    std::promise <double> promise;
    
    //future is an object which is used by the asynchronous consumer code to get the stored result from a promise.
    std::future <double> future = promise.get_future();

    std::thread t([&](){

        try{
            double pi = calculate_pi(number_of_terms);
            promise.set_value(pi);
        }

        catch(std::exception& e){
            //get the exception message
            //std::cout << e.what() << std::endl;

            //the exeception which is being passed in set_exception method will be thrown by future.get() method.
            //we are not passing the exception e because set_exception method expects a different type of exception which
            //is provided by current_exception() method.
            promise.set_exception(std::current_exception()); 
        }
    });

    try{
        double pi = future.get();
        std::cout << std::setprecision(15) << pi << std::endl;
    }
    catch(const std::exception& e){

        //get the exception message
        std::cout << e.what() << std::endl;
    }

    t.join();

    return 0;
}
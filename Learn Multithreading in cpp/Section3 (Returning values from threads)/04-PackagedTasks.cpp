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
//what is std::move???
//Packaged task is syntactic sugar for the code written with promises, the code becomes cleaner when packaged tasks are used instead of promises 

int main(){

    int number_of_terms = 1E6;

    //in packedTask, we pass the function signature (in this case the signature for calculate_pi) and then we pass in the function.
    //we do not pass the function arguments here.
    std::packaged_task <double(int)> packagedTask(calculate_pi);
    
    //future is an object which is used by the asynchronous consumer code to get the stored result from promise or packagedtask.
    std::future <double> future = packagedTask.get_future();

    //pass the packaged task to thread
    //note that we cant pass the packagedTask by value, so we pass reference
    std::thread t(std::ref(packagedTask), number_of_terms);

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
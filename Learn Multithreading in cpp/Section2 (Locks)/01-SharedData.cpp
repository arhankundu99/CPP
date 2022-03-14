#include <iostream>
#include <thread>

/*
lambda expressions
src: https://www.geeksforgeeks.org/lambda-expression-in-c/

lambda expressions are used to create anonymous functions that are not going to be reused and are not worth naming

syntax: [](){}

[] contains the variables from the outer scope that we want to attach to the anonymous function
() contains the function arguments
{} contains the code that should get executed
*/

int main(){

    int count = 0;
    const int ITERATIONS = 1E6;

    //note that we are passing the reference of the count variable. so any changes made by the thread t1 to count will be reflected to the count variable in main thread
    std::thread t1([&count](){
        for(int i = 0; i < ITERATIONS; i++)
            count++;
    });

    std::thread t2([&count](){
        for(int i = 0; i < ITERATIONS; i++)
            count++;
    });

    t1.join(); //The calling thread (In this case main thread) will wait until t1 is done executing.
    t2.join(); //The calling thread (In this case main thread) will wait until t2 is done executing.

    std::cout << count << std::endl; /*usually a number < 2E6 because same data is shared between two threads. As these threads are executing
    simultaneously and not sequencially, we get this random result. The changes made by t1 to count may not be seen by t2 and viceversa. And 
    so we must be very careful while sharing data between two threads */
    return 0;
}
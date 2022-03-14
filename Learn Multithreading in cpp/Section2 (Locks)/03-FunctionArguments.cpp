#include <iostream>
#include <thread>

#include <mutex>

//refer this: https://stackoverflow.com/questions/11833070/when-is-the-use-of-stdref-necessary

//PLEASE NOTE THAT ITS NOT COMMON TO USE MUTEXES BECAUSE WHAT IF THE CODE BETWEEN LOCK AND UNLOCK throws an error?
//then the mutex will never get unlocked.
//So for that reason it is more common to use UNIQUE LOCK and LOCK GUARDS

void func(int& count, const int& ITERATIONS, std::mutex& mtx){
    for(int i = 0; i < ITERATIONS; i++){
        mtx.lock(); 
        count++;
        mtx.unlock();
    }
}

int main(){

    int count = 0;
    const int ITERATIONS = 1E6;

    //initialize a mutex object
    std::mutex mtx;

    /*Way to pass arguments to a function called by a thread

    std::thread t1(func, count, ITERATIONS, mtx);
    std::thread t2(func, count, ITERATIONS, mtx);

    But this is not the correct way if we want to pass references. 
    To pass references, we have to use std::ref
    But why?

    In this case, t1 will call the func with the arguments count, ITERATIONS and mtx -> func(count, ITERATIONS, mtx)
    And we are passing these arguments BY VALUE, that means before executing func(count, ITERATIONS, mtx):
    count, ITERATIONS and mtx are getting copied into new variables and those new variables are being passed to func function

    So any changes made by the func function will not be reflected to the original count because we did not pass the reference of count
    */

    std::thread t1(func, std::ref(count), std::ref(ITERATIONS), std::ref(mtx));
    std::thread t2(func, std::ref(count), std::ref(ITERATIONS), std::ref(mtx));


    t1.join(); //The calling thread (In this case main thread) will wait until t1 is done executing.
    t2.join(); //The calling thread (In this case main thread) will wait until t2 is done executing.

    std::cout << count << std::endl;

}
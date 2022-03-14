#include <iostream>
#include <thread>

#include <mutex>

//Mutex is a lock that is used to lock the critical section of the code, so that only one thread at a time can access the critical section
//and other threads have to wait until the thread unlocks the mutex. Mutex is used to share data between threads in a secure way

//PLEASE NOTE THAT ITS NOT COMMON TO USE MUTEXES BECAUSE WHAT IF THE CODE BETWEEN LOCK AND UNLOCK throws an error?
//then the mutex will never get unlocked.
//So for that reason it is more common to use UNIQUE LOCK and LOCK GUARDS
int main(){

    int count = 0;
    const int ITERATIONS = 1E6;

    //initialize a mutex
    std::mutex mtx;

    //assigning function to a variable
    //note that in lamda expression, if we write [&], this means to capture all the local variables
    //this means in this case, in this anonymous function [&](){in this code, we can access both count and iteration}

    auto func = [&](){
        for(int i = 0; i < ITERATIONS; i++){
            mtx.lock(); 
            //what this does is, if a thread is already executing the section of code between mutex lock and mutex unlock, other threads have to
            //WAIT for the mutex to unlock, so that they can access the code
            count++;

            mtx.unlock();
            //count is incremented by a thread and now other threads can access the code

            //THE CODE BETWEEN mtx.lock() and mtx.unlock() is known as CRITICAL SECTION
            //ONLY ONE THREAD CAN ACCESS THE CRITICAL SECTION AT A TIME

            //REMEMBER TO UNLOCK THE MUTEX, otherwise other threads cannot access the critical section.

            //REMEMBER TO PLACE THE LOCK AND UNLOCK to the code which you want to share between multiple threads
        }
    };

    std::thread t1(func);
    std::thread t2(func);

    t1.join(); //The calling thread (In this case main thread) will wait until t1 is done executing.
    t2.join(); //The calling thread (In this case main thread) will wait until t2 is done executing.

    std::cout << count << std::endl;
}
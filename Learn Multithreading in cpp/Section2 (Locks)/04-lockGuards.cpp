#include <iostream>
#include <thread>

#include <mutex>
#include <chrono>

// https://www.modernescpp.com/index.php/prefer-locks-to-mutexes

//refer this: https://stackoverflow.com/questions/11833070/when-is-the-use-of-stdref-necessary

//PLEASE NOTE THAT ITS NOT COMMON TO USE MUTEXES BECAUSE WHAT IF THE CODE BETWEEN LOCK AND UNLOCK throws an error?
//then the mutex will never get unlocked.
//So for that reason it is more common to use UNIQUE LOCK and LOCK GUARDS

//unique_lock is built on lock_guards with some more properties like where to lock or unlock, try_lock() etc

void func(float dividend, float divisor, std::mutex& mtx){
    std::lock_guard<std::mutex> guard(mtx);
    //mtx.lock();

    std::cout << divisor << std::endl;
    return; //here, if we have used mutexes, mtx would never be unlocked causing other threads to wait indefinitely
    //Instead of mutexes, if we use lock_guards, when lock guard goes out of scope, in the destructor of lock_guard, mtx.unlock() is called


    //mtx.unlock();
}

int main(){

    float dividend = 10, divisor1 = 0, divisor2 = 5;

    //initialize a mutex object
    std::mutex mtx;

    std::thread t1(func, dividend, divisor1, std::ref(mtx));
    std::thread t2(func, dividend, divisor2, std::ref(mtx));


    t1.join();
    t2.join();

}


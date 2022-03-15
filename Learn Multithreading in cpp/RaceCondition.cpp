// src: https://www.avanderlee.com/swift/race-condition-vs-data-race/

#include <iostream>
#include <thread>
#include <mutex>

//A race condition occurs when the timing or order of events affects the correctness of a piece of code.

void raceConditionF1(int& num, std::mutex& mtx){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mtx.lock();
    num *= 2;
    mtx.unlock();
}

void raceConditionF2(int& num, std::mutex& mtx){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mtx.lock();
    num -= 2;
    mtx.unlock();
}


int main(){

    
    std::mutex mtx;

    for(int i = 0; i < 10; i++){
    
        int num = 10;
        std::thread t1(raceConditionF1, std::ref(num), std::ref(mtx)); 
        std::thread t2(raceConditionF2, std::ref(num), std::ref(mtx));

        t1.join();
        t2.join();

        //here if t1 executes first, then we get result as 18, else if t2 runs first then we get result as 16
        std::cout << "The value of num in " << i << " iteration: " << num << std::endl;
    }

    return 0;
}
// src: https://www.avanderlee.com/swift/race-condition-vs-data-race/

#include <iostream>
#include <thread>

//data race occurs when one or more threads are writing to a shared resource (Or one thread is writing and one thread is reading) without using a lock

const int ITERATIONS = 1E5;
void dataRace(int& count){
    for(int i = 0; i < ITERATIONS; i++)count++;
}
int main(){

    int count = 0;
    std::thread t1(dataRace, std::ref(count));
    std::thread t2(dataRace, std::ref(count));

    t1.join();
    t2.join();

    std::cout << count << std::endl; //This does not give the correct result because here two threads are writing to count at the same time without a lock which results in a data race
    return 0;
}
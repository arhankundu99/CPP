#include <iostream>

#include <thread>
#include <mutex>

#include <condition_variable>

#include <chrono>

std::condition_variable cond;
bool notified = false;
int iterations = 3;

void producer(std::mutex& mtx, int& count){
    
    for(int i = 1; i <= iterations; i++){
        //std::cout << "Producer trying to acquire lock in " << i << "th iteration" << std::endl;
        std::unique_lock<std::mutex> lock(mtx);

        cond.wait(lock, [](){return !notified;});

        std::cout << "Producer acquired lock in " << i << " iteration" << std::endl;

        count++;

        std::cout << "Producer unlocked the lock in " << i << " iteration" << std::endl;
        lock.unlock();

        std::cout << "Producer notifying the consumer in " << i << " iteration" << std::endl;

        notified = true;
        cond.notify_one();

    }
}

void consumer(std::mutex& mtx, int& count){

    
    while(count != iterations){
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "Consumer acquired lock and waiting for notification from producer" << std::endl;

        cond.wait(lock, [](){return notified;});
        std::cout << "Consumer gets notification from producer" << std::endl;

        std::cout << "t2 recieves this value of count of t1: " << count << std::endl;

        notified = false;

        lock.unlock();
        cond.notify_one();

    }
}

int main(){

    std::mutex mtx;
    int count = 0;

    std::thread t1(producer, std::ref(mtx), std::ref(count));
    std::thread t2(consumer, std::ref(mtx), std::ref(count));

    t1.join();
    t2.join();

    return 0;

}
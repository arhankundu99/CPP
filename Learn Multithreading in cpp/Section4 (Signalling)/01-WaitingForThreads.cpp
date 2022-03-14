//src: https://www.youtube.com/watch?v=13dFggo4t_I
#include <iostream>

#include <thread>
#include <mutex>

#include <chrono>

#include <deque>

std::deque<int> q;
std::mutex mtx;

void function1(){
    int count = 10;
    while(count > 0){
        std::unique_lock<std::mutex> lock(mtx);
        q.push_front(count);
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        count--;
    }
}

//here function2 is always checking whether the deque is empty or not, let's say the function1 takes a while to lock the mutex and deque is empty
//so in function2, the while loop will run again and again. How do we optimize this?
void function2(){
    int data = 0;
    while(data != 1){
        std::unique_lock<std::mutex> lock(mtx);
        if(!q.empty()){
            data = q.back();
            q.pop_back();
            lock.unlock();
            std::cout << "t2 got a value from t1: " << data << std::endl;
        }
        else{
            lock.unlock();

            //To solve this, we can use condition_variable
            
            //std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

int main(){

    std::thread t1(function1);
    std::thread t2(function2);

    t1.join();
    t2.join();
}
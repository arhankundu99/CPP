#include<iostream>
#include<thread>

//templates are used to write generic functions or generic classes that can be used for all datatypes

//read more: https://www.geeksforgeeks.org/templates-cpp/

template<typename T>
class blockingQueue{
public:
    void push(T E){
        std::cout << "push" << std::endl;
    }

    void pop(){
        std::cout << "pop" << std::endl;
    }
};

int main(){
    blockingQueue<int> bQueue;

    std::thread t1(blockingQueue<int>::push, &bQueue, 5);
    std::thread t2(blockingQueue<int>::pop, &bQueue);
    
    t1.join();
    t2.join();
}

#include <iostream>
#include <thread>
#include <chrono>

//chrono library deals with time and date

void work(){
    for(int i = 0; i < 10; i++){
        //this_thread is a namespace defined in thread header file
        //which groups a set of functions that access the current thread like get_id, sleep_for, sleep_until, yeild etc.
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::cout << "Loop " << i << std::endl;
    }
}

int main(){
    std::cout << "Hello Multithreading!" << std::endl;

    //create 2 thread objects using thread class defined in thread header and pass in a function pointer. 
    //in this case, the work function would execute in a different thread
    std::thread t1(work);
    std::thread t2(work);

    t1.join();
    t2.join();

    return 0;
}
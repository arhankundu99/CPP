#include <iostream>
#include <thread>

//Refer this link: https://docs.microsoft.com/en-us/dotnet/api/system.threading.thread.join
void work(){
    for(int i = 0; i < 10; i++){
        std::cout << "Loop " << i << std::endl;
    }
}

int main(){
    std::cout << "Hello Multithreading!" << std::endl;

    //create thread object using thread class defined in thread header and pass in a function pointer. 
    //in this case, the work function would execute in a different thread
    std::thread t1(work);

    //now there are 2 threads: Main thread and t1

    /*
    Join is a synchronization method that blocks the calling thread (that is, the thread that calls the method) 
    until the thread whose Join method is called has completed. 
    Use this method to ensure that a thread has been terminated. 
    The caller will block indefinitely if the thread does not terminate.
    */

    // So here if we want the main thread to wait until t1 thread executes, then we would have to use t1.join() method
    t1.join();

    return 0;
}
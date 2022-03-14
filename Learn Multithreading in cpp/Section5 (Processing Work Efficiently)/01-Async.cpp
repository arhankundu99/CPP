#include <iostream>

#include <future>
#include <thread>

int work(int id){
    for(int i = 0; i < 3; i++){
        std::cout << "Current thread id: " << id << std::endl;
    }
    return id;
}

int main(){

    auto future1 = std::async(std::launch::async, work, 0); //this will launch the function work in a seperate thread

    auto future2 = std::async(std::launch::deferred, work, 1); //this will not launch the function in a separate thread until future2.get() is invoked

    /*NOTE:
        The below code will run SYNCHRONOUSLY
        If the std::future obtained from std::async is not moved from or bound to a reference, 
        the destructor of the std::future will block at the end of the full expression until the asynchronous operation completes, 
        essentially making code such as the following synchronous:
        
        std::async(std::launch::async, work, 0);
        std::async(std::launch::async, work, 1);

        Difference between std::async and std::packaged_task

        Using packaged_task, we can run the packaged_task in a specific thread

        Using async with launch::async, will run the function in different thread without any invocation

        we can say that async is a higher level implementatation of packaged_task 
        and packaged_task is a higher level implementation of promise.
    */

    std::cout << future1.get() << std::endl;
    std::cout << future2.get() << std::endl;

    return 0;
}
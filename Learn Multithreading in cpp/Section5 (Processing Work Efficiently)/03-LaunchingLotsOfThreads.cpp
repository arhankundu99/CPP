#include <iostream>

#include <thread>
#include <mutex>
#include <future>

#include <vector>

std::mutex mtx;
int work(int id){
    std::unique_lock <std::mutex> lock(mtx);
    std::cout << "Running " << id << std::endl;
    mtx.unlock();
    return id;
}

int main(){

    // std::vector <std::future<int>> futures; //for method1 and method2
    std::vector <std::shared_future<int>> futures; //for method3
    for(int i = 0; i < std::thread::hardware_concurrency(); i++){
        /*
        //method1
        std::future<int> f = std::async(std::launch::async, work, i); 
        //this works synchrounously because f goes out of scope when the loop restarts

        //Remember that with async, if future gets out of scope then the function runs synchronously
        //So we can try to store the futures in a vector
        */

       /*
       //method2
       std::future<int> f = std::async(std::launch::async, work, i);

       futures.push_back(f);

        //this will not work as futures are not copyable
        //so we need to shared_future
       */

       //method3
       std::shared_future<int> f = std::async(std::launch::async, work, i);
       futures.push_back(f);
    }

    for(int i = 0; i < futures.size(); i++)std::cout << "Returned: " << futures[i].get() << std::endl;

    return 0;
}
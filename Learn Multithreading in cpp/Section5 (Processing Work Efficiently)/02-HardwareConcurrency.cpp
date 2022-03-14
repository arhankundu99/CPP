#include <iostream>
#include <thread>

int main(){

    std::cout << "Number of threads that my pc can run at the same time: " << std::thread::hardware_concurrency() << std::endl;
}
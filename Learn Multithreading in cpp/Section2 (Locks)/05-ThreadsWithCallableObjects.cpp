#include <iostream>

#include <thread>
#include <mutex>

class App{
private:
    int count;
    std::mutex mtx;

public:
    //operator overloading for ()
    void operator()(const int ITERATIONS){
        for(int i = 0; i < ITERATIONS; i++){
            std::lock_guard <std::mutex> guard(mtx);
            count++;
        }
    }

    int getCount(){
        return count;
    }
};
int main(){

    int ITERATIONS = 1E6;

    App app;

    /*
        std::thread t1(app, ITERATIONS);
        std::thread t2(app, ITERATIONS);

        If we dont use std::ref, we would get an error because, app object is passed by value and the copy constructor is called for
        shallow copy and mutex does not allow copy constructor.
    */
    std::thread t1(std::ref(app), ITERATIONS);
    std::thread t2(std::ref(app), ITERATIONS);

    t1.join();
    t2.join();

    std::cout << app.getCount() << std::endl;
}
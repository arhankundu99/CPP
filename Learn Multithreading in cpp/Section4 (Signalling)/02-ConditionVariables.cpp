//src: https://www.youtube.com/watch?v=13dFggo4t_I

//condition_variables are used to block one or many threads, 
//until another thread modifies the shared resource and notifies the dependent threads

//condition_variables are used to block one or many threads, until a certain condition is met
//Best practice is to write the predicate function so that the thread does not wake up for wrong conditions

//Thread waking up even if the condition is not met is known as spurious wakeup, that is why it is best to write predicate functions

//Where to use condition_variables? One way to identify is that if producer code and consumer code is running in different threads

//std::condition_variable works only with std::unique_lock<std::mutex>
#include <iostream>

#include <thread>
#include <mutex>

#include <chrono>

#include <deque>

#include <condition_variable>

std::deque<int> q;
std::mutex mtx;
std::condition_variable cond;

//producer code
void function1(){
    int count = 10;
    while(count > 0){
        std::unique_lock<std::mutex> lock(mtx);
        q.push_front(count);
        lock.unlock();
        cond.notify_one(); //here we are notifying only one thread that is t2, if there were multiple threads, use cond.notify_all();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        count--;

        //why cond.notify_one() is written after lock.unlock()?
        /*That's a minor and usually irrelevant optimization. 
        The concern arises because each thread that wakes up after a call to notify or notify_all has to lock the mutex before it is allowed to proceed. 
        If the call to unlock occurs after the call to notify_one (or to notify), 
        the thread(s) that wake up will have to wait until after the calling thread unlocks it. 
        If the call to unlock is made before the notify call then one awakened thread can get the mutex immediately.*/
    }
}

//consumer code
void function2(){
    int data = 0;
    while(data != 1){
        std::unique_lock<std::mutex> lock(mtx);
        cond.wait(lock, [](){
            return !q.empty();
        }); 
        //here the thread is blocked until the notification comes from the other thread. But why are we passing the lock? Because
        //cond.wait() method unlocks the mutex, so that the other thread can access the shared resource. And once the other thread notifies this
        //thread that the shared resource has been modified, cond.wait() method unlocks the mutex and executes its code

        //And that is why unique_lock is used instead of lock_guards because we have to manually unlock and lock. 

        //lets say that the other thread modified a shared resource and the thread2 was not expecting this value of the shared resource to proceed
        //in this case, we can pass a function pointer to cond.wait() method to unlock the unique_lock when shared resource value is equal to the 
        //expected value

        data = q.back();
        q.pop_back();
        lock.unlock();
        std::cout << "t2 got a value from t1: " << data << std::endl;
    }
}

int main(){

    std::thread t1(function1);
    std::thread t2(function2);

    t1.join();
    t2.join();

    return 0;
}
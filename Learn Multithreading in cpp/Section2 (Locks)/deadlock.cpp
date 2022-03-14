#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

/*
What is deadlock?
Suppose there are two threads, one holding mutex1 and the other holding mutex2 
(in which case at least the latter must be running something different from your pseudocode). 
Now suppose that each thread attempts to acquire the other mutex without releasing the one it already holds. 
The first thread must acquire mutex2 to proceed, and cannot do so until the other releases it. 
The second thread must acquire mutex1 to proceed, and cannot do so until the other releases it. 
Ergo, neither thread can ever proceed -- this is a deadlock.

*/

//link: https://stackoverflow.com/questions/42720131/multiple-locks-with-mutex-and-the-possibility-of-a-deadlock
//link: https://www.modernescpp.com/index.php/the-risk-of-mutexes

void deadLock(std::mutex& m1, std::mutex& m2){

  m1.lock();
  std::cout << "get the first mutex" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  m2.lock();
  std::cout << "get the second mutex" << std::endl;

  m1.unlock();
  m2.unlock();
  
}

int main(){

  std::mutex m1;
  std::mutex m2;

  std::thread t1(deadLock, std::ref(m1), std::ref(m2));
  std::thread t2(deadLock, std::ref(m2), std::ref(m1));

  t1.join();
  t2.join();

}
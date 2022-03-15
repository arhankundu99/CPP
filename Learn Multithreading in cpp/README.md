When is multithreading useful?

Multithreading gives us asynchronous execution. This is where functions are not synchronized with each other. They can run at the same time.

**a) When we are waiting for something external and we want to execute some code in the mean time**

Example: pinging remote servers to get data collectively instead of getting data from pinging the servers one by one
        (assuming the data from the servers are independent from each other) or drawing graphics while taking user input

**b) Distributing processing across multiple cores**

Let's say a CPU has 8 cores, So we can distribute the work in 8 cores which runs at the same time so that processing can be faster

Example: calculating pi to lots of digits

**c) What is time-slicing?**

Time-slice multithreading is the convectional multithreading where CPU creates an illusion of executing more than once program at a time 
but the CPU can execute only one of these programs at a time. 
The OS maintains the illusion of concurrency by rapidly switching between running programs at a fixed interval, called a time slice.

1. Running a function from a different thread

   Syntax: ```std::thread t1(function);```

2. **join**: The join method of std::thread is used to block the calling thread until the thread finishes execution. Otherwise if the calling thread terminates before the execution of the thread completes, then the thread will stop prematurely.
  
   Syntax: ```t1.join();```

3. **std::this_thread::sleep_for**: ```std::this_thread::sleep_for``` is a function which is defined in ```std::this_thread``` namespace. Use ```std::chrono``` for specifying the duration.

4. **Locks**: Locks are used to make our code thread-safe. If two or more threads are writing to the same variable at the same time (or one thread is writing and the other thread is reading), then the changes made by thread1 may not be visible to the thread2 and this may lead to data corruption.
                       
5. **std::mutex**: mutex is an object which is used to lock the critical section of the code (The code which may contain manipulation of shared resource) so that only one thread can access the critical section of the code and if other threads want to get access, they would have to wait for the thread to unlock the mutex.
   
   Syntax: 
   
   ```
   std::mutex mtx;
   mtx.lock(); //lock the mutex
   /*
   	critical section
   */
   mtx.unlock();
   ```

6. **Problem with std::mutex**: The drawback with std::mutex is that if the critical section throws an error or if the programmer forgets to unlock the mutex, the mutex is never unlocked and other threads will wait indefinitely. To avoid this problem, we use ```std::lock_guards```.

7. **std::lock_guards**: The advantage with lock_guards is that whenever lock_guard goes out of scope, the mutex is unlocked, So we dont have to worry about critical sections throwing errors or programmers forgetting to unlock the mutex

   Syntax:
   
   ```
   std::mutex mtx;
   std::lock_guard <std::mutex> lock(mtx); //pass the mtx in the constructor of lock_guard
   /*
   	critical section
   */

   // No need to unlock the lock, lock will get unlocked whenever it goes out of scope.
   ```
8. **std::unique_lock**: ```std::unique_lock``` provides some more features in addition to ```std::lock_guards``` like we can manually unlock the mutex even if the unique_lock does not go out of scope.

9. **deadlock**: deadlock occurs when two or more threads wants each others' mutexes before unlocking their own mutex. As a result neither of the threads proceed.

10. **Returning values from threads**: 
   a) **promise**: ```std::promise``` is an object which is used to store the result from an asynchronous producer code which can retrieved by a ```std::future``` object in the consumer code.
    
   b) **packaged_task**: ```std::packaged_task``` is an object which has the same functionality as a ```std::promise``` object but we can write   cleaner code with package_task.
    
   c) **async**: ```std::async``` with ```std::launch::async``` runs the passed function in a different thread. The difference between async and packaged_task is that we dont get to run the function in a specified thread with async.
   NOTE: Remember to store the future from the async function otherwise the function defined in ```std::async``` will run synchronously.
  
       ```
       // These functions will run synchronously 
       std::async(std::launch::async, work, 0);
       std::async(std::launch::async, work, 1);
     
       ```

       Solution:
       ```
       //These functions will run asynchronously
       auto future1 = std::async(std::launch::async, work, 0);
       auto future2 = std::async(std::launch::async, work, 1);
       ```
   d) **future**: ```std::future``` is an object which is used to get results from asynchronous producer code.
   NOTE that ```future.get()``` is a blocking code, meaning until the producer code gives the result, the calling thread will wait. 

11. **std::condition_variables**: ```std::condition_variables``` are used to block threads until a certain condition is met.
   NOTE: It is generally a good practice to define the predicate_function as it makes the code cleaner
    
   Spurious wakeup: A spurious wakeup happens when a thread wakes up from waiting on a condition variable that's been signaled, only to discover that the condition it was waiting for isn't satisfied. It's called spurious because the thread has seemingly been awakened for no reason. But spurious wakeups don't happen for no reason: they usually happen because, in between the time when the condition variable was signaled and when the waiting thread finally ran, another thread ran and changed the condition. There was a race condition between the threads, with the typical result that sometimes, the thread waking up on the condition variable runs first, winning the race, and sometimes it runs second, losing the race

12. **Data Race**: Data Race occurs when two or more threads are writing to the same shared resource (or one thread is writing and one thread is reading simultaneously) without using locks that leads to data corruption.

13. **Race Condition**: Race condition occurs when the order of events affects the correctness of a piece of code.
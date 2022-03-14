//refer thread safety docx

#include <iostream>
#include <thread>
#include <queue>

#include <mutex>
#include <condition_variable>

//templates are used to write generic functions or generic classes that can be used for all datatypes

//read more: https://www.geeksforgeeks.org/templates-cpp/

template<typename T>
class blockingQueue{
private:
    std::mutex mtx;
    std::condition_variable cond;
    int maxElements;
    std::queue<T> q;
public:
    blockingQueue(int maxElements): maxElements(maxElements){

    }
    void push(T E){
        std::unique_lock<std::mutex> lock(mtx);
        cond.wait(lock, [this](){
            return q.size() < maxElements;
        });
        q.push(E);
        
        lock.unlock();
        cond.notify_one();
    }
    T front(){
        std::unique_lock<std::mutex> lock(mtx);

        cond.wait(lock, [this](){
            return !q.empty();
        });

        return q.front();
    }
    T pop(){
        
        std::unique_lock<std::mutex> lock(mtx);

        cond.wait(lock, [this](){
            return !q.empty();
        });

        q.pop();
        
        lock.unlock();
        cond.notify_one();

        return item;
    }

    int size(){
        std::unique_lock<std::mutex> lock(mtx);
        return q.size();
    }
};

int main(){
    blockingQueue<int> bQueue(5);

    std::thread t1([&](){
        for(int i = 0; i < 10; i++){
            bQueue.push(i);
        }
    });
    std::thread t2([&](){
        for(int i = 0; i < 10; i++){
            auto item = bQueue.front();
            bQueue.pop();
            std::cout << "consumed " << item << std::endl;
        }
    });
    
    t1.join();
    t2.join();
}

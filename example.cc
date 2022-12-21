#include <iostream>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <mutex>
/*
    Rough Idea:
        - A single class that spawns two threads in its constructors
            - The threads themselves are while loops doing CPU intensive work
        - we call join on its dtor
        - A condition variable that will determine who will get the current priority to run
*/

class TestingClass {
    
    public:
    TestingClass() {
        T1 = std::thread(&TestingClass::thread_func,this);
        T2 = std::thread(&TestingClass::thread_func_b, this);
    }

    ~TestingClass() {
        T1.join();
        T2.join();
    }

    // ThreadA
    static void thread_func(TestingClass * cls) {

       while(1) {   
            std::unique_lock<std::mutex> lk(cls->mu);
            cls->threadARunningCv.wait(lk, [cls] { return cls->threadARunning; });

            std::cout<<"Thread A is Running " << std::endl;
            std::this_thread::sleep_for(std::chrono::microseconds(25)); // Simulating task
            std::cout<<"Thread A is complete" << std::endl;

            cls->threadARunning = false;
            cls->threadARunningCv.notify_one();
       }
    }

    // ThreadB
    static void thread_func_b(TestingClass * cls) {
        while(1) {
            std::unique_lock<std::mutex> lk (cls->mu);
            cls->threadARunningCv.wait(lk, [cls] { return !cls->threadARunning; }); // Wait untill threadA stops running

            std::cout<<"Thread B is running "<< std::endl;
            std::this_thread::sleep_for(std::chrono::microseconds(25)); // Simulate working on tasks
            std::cout<<"Thread B is complete "<<std::endl;

            cls->threadARunning = true;
            cls->threadARunningCv.notify_one();
        }
        
    }

    std::thread T1;
    std::thread T2;
  
    bool threadARunning = false;
    std::mutex mu;
    std::condition_variable threadARunningCv;

};

int main() {
    TestingClass * cls  = new TestingClass();
    delete cls;
}

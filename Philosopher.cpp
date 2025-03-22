#include <Philosopher.hpp>

void Philosopher::eat(){
    // bool finishedEating = true;
    while(!shouldClose){
        std::unique_lock<std::mutex> lock(*philosopherMutex);
        condition->wait(lock,  [&]() { return !isEating || shouldClose; }); 

        if(shouldClose)
            break;

        isEating = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        (*food)--;
    
        isEating = false;
        // finishedEating = true;
        
        // lock.unlock();
        condition->notify_all();
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Philosopher::close(){
    std::cout << name << " is leaving" << std::endl;
    shouldClose = true;
    condition->notify_all();
    if(philosopherThread.joinable())
        philosopherThread.join();
    std::cout << name << " left" << std::endl;
}
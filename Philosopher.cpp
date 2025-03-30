#include "Philosopher.hpp"

void Philosopher::eat(const std::vector<std::shared_ptr<Philosopher>>& philosophers){
    while(!shouldClose){
        std::unique_lock<std::mutex> lock(*philosopherMutex);
        condition->wait(lock, [&]() { return canEat(philosophers) || shouldClose; }); 

        if(shouldClose)
            break;

        if (!canEat(philosophers))
            continue;

        isEating = true;
        (*food)--;

        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        lock.lock();
        isEating = false;
        lock.unlock();

        condition->notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Philosopher::close(){
    std::cout << "Philosopher " << name << " is leaving" << std::endl;
    shouldClose = true;
    condition->notify_all();
    if(philosopherThread.joinable())
        philosopherThread.join();
    std::cout << "Philosopher " << name << " left" << std::endl;
}

bool Philosopher::canEat(const std::vector<std::shared_ptr<Philosopher>>& philosophers){
    if (id == 0)
        return !philosophers[id + 1]->isEating && !philosophers[philosophers.size() - 1]->isEating;
    else if(id == philosophers.size() - 1)
        return !philosophers[id - 1]->isEating && !philosophers[0]->isEating;
    else{
        return !philosophers[id - 1]->isEating && !philosophers[id + 1]->isEating;
    }
}
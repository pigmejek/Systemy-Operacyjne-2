#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <mutex>
#include <memory>
#include <thread>
#include <condition_variable>
#include <string>
#include <iostream>

class Philosopher{
public:
    Philosopher(std::string name, std::shared_ptr<std::mutex> mutex, 
                std::shared_ptr<int> food, std::shared_ptr<std::condition_variable> condition, bool isEating = false)
                 : name{name}
                 , philosopherMutex{mutex}
                 , food{food}
                 , condition{condition}
                 , isEating{isEating}
    {
        philosopherThread = std::thread(&Philosopher::eat, this);
    };
    
    std::string name;
    bool isEating;

    std::thread philosopherThread;
    std::shared_ptr<std::mutex> philosopherMutex;
    std::shared_ptr<int> food;
    std::shared_ptr<std::condition_variable> condition;
    
    volatile bool shouldClose = false;

    void eat();

    void close();
};

#endif // PHILOSOPHER_H
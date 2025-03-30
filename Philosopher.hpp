#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <mutex>
#include <memory>
#include <thread>
#include <condition_variable>
#include <string>
#include <iostream>
#include <vector>

class Philosopher{
public:
    Philosopher(std::string name, int id, std::shared_ptr<std::mutex> mutex, 
                std::shared_ptr<int> food, std::shared_ptr<std::condition_variable> condition,
                bool isEating = false)
                 : name{name}
                 , id{id}
                 , philosopherMutex{mutex}
                 , food{food}
                 , condition{condition}
                 , isEating{isEating}
    {
    };

    void startThread(std::vector<std::shared_ptr<Philosopher>>& philosophers) { 
        philosopherThread = std::thread(&Philosopher::eat, this, ref(philosophers));
    }

    ~Philosopher() = default;
    
    std::string name;
    int id;
    bool isEating;

    std::thread philosopherThread;
    std::shared_ptr<std::mutex> philosopherMutex;
    std::shared_ptr<int> food;
    std::shared_ptr<std::condition_variable> condition;
    
    volatile bool shouldClose = false;

    void eat(const std::vector<std::shared_ptr<Philosopher>>& philosophers);

    void close();

private:
    bool canEat(const std::vector<std::shared_ptr<Philosopher>>& philosophers);
};

#endif // PHILOSOPHER_H
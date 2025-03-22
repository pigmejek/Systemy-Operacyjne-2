#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <Philosopher.hpp>
#include <ncurses.h>

void printStates();

void close();

std::vector<std::unique_ptr<Philosopher>> philosophers;

std::shared_ptr<int> FOOD = std::make_shared<int>(INT32_MAX);
std::shared_ptr<std::condition_variable> condition = std::make_shared<std::condition_variable>();
std::shared_ptr<std::mutex> philosopherMutex = std::make_shared<std::mutex>();

int main(){
    initscr();
    cbreak();
    noecho();   
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    resize_term(100, 100);

    philosophers.push_back(std::make_unique<Philosopher>("Platon", philosopherMutex, FOOD, condition));
    philosophers.push_back(std::make_unique<Philosopher>("Sokrates", philosopherMutex, FOOD, condition));
    philosophers.push_back(std::make_unique<Philosopher>("Heraklit", philosopherMutex, FOOD, condition));
    philosophers.push_back(std::make_unique<Philosopher>("Arystoteles", philosopherMutex, FOOD, condition));
    
    volatile bool shouldClose = false;
    while (!shouldClose){
        printStates();
        int ch = getch();
        if (ch == ' ') {
            endwin();
            (*condition).notify_all();
            close();
            shouldClose = true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}

void printStates(){
    erase();
    mvprintw(0, 0, "Currently there is %d food", *FOOD);
    int i = 1;
    for(auto const& p : philosophers){
        if(p->isEating)
            mvprintw(i++, 0, "Philosopher %s is eating", p->name.c_str());
        else
            mvprintw(i++, 0, "Philosopher %s is waiting for food", p->name.c_str());
    
    }
}

void close(){
    for(auto const& p : philosophers)
        p->close();
}
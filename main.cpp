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

std::vector<std::shared_ptr<Philosopher>> philosophers;

std::shared_ptr<int> FOOD = std::make_shared<int>(INT32_MAX);
std::shared_ptr<std::condition_variable> condition = std::make_shared<std::condition_variable>();
std::shared_ptr<std::mutex> philosopherMutex = std::make_shared<std::mutex>();

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_philosophers>" << std::endl;
        return 1;
    }

    int numPhilosophers = std::stoi(argv[1]);
    if (numPhilosophers < 2) {
        std::cerr << "Error: The number of philosophers must be at least 2." << std::endl;
        return 1;
    }

    initscr();
    cbreak();
    noecho();   
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    resize_term(100, 100);

    for (int i = 0; i < numPhilosophers; i++) {
        std::string name = "Philosopher " + std::to_string(i);
        philosophers.push_back(std::make_shared<Philosopher>(name, i, philosopherMutex, FOOD, condition));
    }

    for (const auto p : philosophers)
        p->startThread(philosophers);

    volatile bool shouldClose = false;
    while (!shouldClose) {
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

void printStates() {
    erase();
    mvprintw(0, 0, "Currently there is %d food", *FOOD);
    int i = 1;
    for (auto const& p : philosophers) {
        if (p->isEating)
            mvprintw(i++, 0, "%s is eating", p->name.c_str());
        else
            mvprintw(i++, 0, "%s is waiting for food", p->name.c_str());
    }
}

void close() {
    for (auto const& p : philosophers)
        p->close();
}
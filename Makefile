# Makefile

main:
	g++ -std=c++17 -o program main.cpp Philosopher.cpp -I. -Iphilosopher -pthread -lncurses

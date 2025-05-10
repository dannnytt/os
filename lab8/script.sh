#!/bin/bash

g++ -o bin/lab8_sequential lab8_sequential.cpp
gcc -o bin/lab8_pthreads lab8_parallel.c
g++ -o bin/lab8_cpp-thread lab8_parallel.cpp

echo "Результат последовательного вычисления:"
./bin/lab8_sequential

echo -e "\nРезультат последовательного вычисления (pthreads):"
./bin/lab8_pthreads

echo -e "\nРезультат параллельного вычисления (c++ threads):"
./bin/lab8_cpp-thread
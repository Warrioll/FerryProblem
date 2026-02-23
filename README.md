# Ferry problem
This repository contains a simple console application that demonstrates the Ferry problem described below, using threads in C++.

>The river ferry allows 5 cars on board, or if there are too few cars, it waits for some time. Then it sails to the other shore, releases the cars, and returns empty. Cars board the ferry one after another in sequential order.

The ferry is represented as the main thread, and each car is represented as a separate thread. The application uses mechanisms such as semaphore and mutexe to manage access to shared data.

Users can decide how many cars can wait in the queue, the time interval at which cars spawn, and how long the ferry waits for cars to board before it departs.

## How to run and compile
 To start application, run `x64/Debug/SystemyOperacyjne-KN-MN.exe` program.

The project was compiled with Visual Studio 2022 and Microsoft (R) C/C++ Optimizing Compiler Version 19.33.31630 for x86, but since the application uses only standard libraries, it should be compilable with any compiler that supports C++20.

## Disclaimer

This application was created for learning purposes as a student project.

#pragma once
#include <iostream>
#include <thread>
#include <mutex>
		 
#include <semaphore>
#include <chrono>
#include <queue>
#include <random>
#include <Windows.h>
#include "Car.h"

class Ferry
{
	static int minSec;
	static int maxSec;
	static int maxSize;

	int k;
	static int carsWaiting;
	static std::vector<Car> list;
	static std::counting_semaphore<5> sem;	

	static std::mutex mtx;
	static bool ferryReturned;				//odpowiada za to czy prom powróci³		
	static bool drawing;
	static int boarded;
	static std::condition_variable cv;

	static bool ferryLeft;

	static std::chrono::high_resolution_clock::time_point boardStart;
	int waitTime = 0;
	int waitingTime;
	static int toRelease;
	static int id;

	

	using high_resolution_clock = std::chrono::high_resolution_clock;
	using time_point = std::chrono::high_resolution_clock::time_point;

	time_point start, end;

	static int newTime;

	static void boardCar(int carId);
	int randomNumber(int a, int b);
	
	void generateCar(int& id);

public:
	Ferry(int queueMaxSize, int minSec, int maxSec, int waitingTime);
	~Ferry();

	void tryBoardCar(Car* car);

	void ferryWork();

	void render(int cars, int offset);
};


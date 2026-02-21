#include "Ferry.h"

bool Ferry::ferryReturned = true;
bool Ferry::ferryLeft = false;
std::counting_semaphore<5> Ferry::sem(5);
std::mutex Ferry::mtx;
int Ferry::boarded = 0;
std::chrono::high_resolution_clock::time_point Ferry::boardStart;
int Ferry::toRelease = 0;

int Ferry::maxSize = 0;
int Ferry::minSec = 0;
int Ferry::maxSec = 0;
int Ferry::id = 0;

int Ferry::newTime;

std::vector <Car> Ferry::list;

int Ferry::carsWaiting = 0;

Ferry::Ferry(int maxSize, int minSec, int maxSec, int waitingTime) {
	

	srand(static_cast<unsigned>(time(nullptr)));

	this->id = 0;
	this->k = 0;
	this->maxSize = maxSize;
	this->minSec = minSec;
	this->maxSec = maxSec;
	this->toRelease = 0;
	this->newTime = randomNumber(minSec, maxSec);
	this->carsWaiting = 0;
	this->waitingTime = waitingTime;
	start = high_resolution_clock::now();
}

Ferry::~Ferry() {

	for (int i = 0; i < list.size(); i++) {
		if (list[i].t.joinable()) {
			list[i].t.join();
		}
	}
}

void Ferry::tryBoardCar(Car* car)
{
	car->t = std::thread(boardCar, car->id);

}

void Ferry::boardCar(int carId)
{
	while (!ferryReturned) {		
	}

	sem.acquire();		
	
	while (!ferryReturned) {		
	}

	mtx.lock();
	
	boarded++;
	
	carsWaiting--;
	mtx.unlock();

	
	
	while (!ferryLeft) {
	}

	mtx.lock();
	boarded--;
	toRelease++;
	if (boarded == 0) {

		sem.release(toRelease);
		toRelease = 0;
		
	}
	mtx.unlock();
	
}

int Ferry::randomNumber(int a, int b) {

	return rand() % (b - a + 1) + a;
}

void Ferry::generateCar(int& id) {
	++id;
	list.push_back(Car(id));
}

void Ferry::ferryWork() {
	
	render(0, 0);
	boardStart = std::chrono::high_resolution_clock::now();
	while (true) {
		
		waitTime = 0;
		if (boarded > 0) {

			mtx.lock();
			auto boardStop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::seconds>(boardStop - boardStart);
			waitTime = static_cast<int>(duration.count());
			mtx.unlock();
		}
		else
			waitTime = 0;

		if ((boarded == 5 || waitTime >= waitingTime) && !ferryLeft) {
			mtx.lock();
			ferryReturned = false;
			for (int i = 0; i < 50; i++) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				this->end = high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
				if (duration.count() > newTime && carsWaiting < maxSize) {
					newTime = randomNumber(minSec, maxSec);
					this->start = high_resolution_clock::now();
					generateCar(id);
					carsWaiting++;
					tryBoardCar(&list[k]);
					k++;
				}

				system("cls");
				render(boarded, i);
			}
			ferryLeft = true;
			mtx.unlock();
			
		}

		

		if (boarded == 0 && !ferryReturned) {							
			mtx.lock();
			ferryLeft = false;
			for (int i = 0; i < 50; i++) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				this->end = high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
				if (duration.count() > newTime && carsWaiting < maxSize) {
					newTime = randomNumber(minSec, maxSec);
					this->start = high_resolution_clock::now();
					generateCar(id);
					carsWaiting++;
					tryBoardCar(&list[k]);
					k++;
				}

				system("cls");
				render(boarded, 50-i);
				
			}


			
			boardStart = std::chrono::high_resolution_clock::now();
			ferryReturned = true;
			mtx.unlock();
			system("cls");
			render(boarded, 0);

		}

		
		this->end = high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
		if (duration.count() > newTime && carsWaiting < maxSize) {
			newTime = randomNumber(minSec, maxSec);
			this->start = high_resolution_clock::now();
			generateCar(id);
			mtx.lock();
			carsWaiting++;
			mtx.unlock();
			tryBoardCar(&list[k]);
			system("cls");
			render(boarded, 0);
			k++;
		}

		

	}
}

void Ferry::render(int cars, int offset) {
	
	std::cout << "Max length of cars queue: " << this->maxSize << std::endl;
	std::cout << "Cars generating range (seconds): [" << this->minSec << ", " << this->maxSec << "] " << std::endl;
	std::cout << "Waiting time for cars: " << this->waitingTime << std::endl;

	std::cout << std::endl;

	std::string spaces;

	for (int i = 0; i < offset; i++) {
		spaces += " ";
	}

	std::cout << "Amount of waiting cars: " << carsWaiting << std::endl;
	std::cout << "Amount of boarded cars: " << cars << std::endl;
	std::cout << "State: ";
	if (spaces.length() == 0) {
		std::cout << "Boarding" << std::endl;
	}
	else {
		std::cout << "Underway" << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "VISUALIZATION: " << std::endl;
	std::cout << std::endl;
	std::cout << "Ferry: " << std::endl;


	switch (cars) {
	case 0:
		std::cout << spaces << "-------" << std::endl;
		std::cout << spaces << "|     |" << std::endl;
		std::cout << spaces << "-------" << std::endl;
		break;
	case 1:
		std::cout << spaces << "-------" << std::endl;
		std::cout << spaces << "|#    |" << std::endl;
		std::cout << spaces << "-------" << std::endl;
		break;
	case 2:
		std::cout << spaces << "-------" << std::endl;
		std::cout << spaces << "|##   |" << std::endl;
		std::cout << spaces << "-------" << std::endl;
		break;
	case 3:
		std::cout << spaces << "-------" << std::endl;
		std::cout << spaces << "|###  |" << std::endl;
		std::cout << spaces << "-------" << std::endl;
		break;
	case 4:
		std::cout << spaces << "-------" << std::endl;
		std::cout << spaces << "|#### |" << std::endl;
		std::cout << spaces << "-------" << std::endl;
		break;
	case 5:
		std::cout << spaces << "-------" << std::endl;
		std::cout << spaces << "|#####|" << std::endl;
		std::cout << spaces << "-------" << std::endl;
		break;
	}

	std::cout << std::endl;
	std::cout << "Queue: " << std::endl;
	for (int i = 0; i < carsWaiting;i++) {
		std::cout << " #";
	}


	std::cout << std::endl;

}
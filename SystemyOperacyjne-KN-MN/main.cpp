#include"Ferry.h"
#include <queue>
#include <random>
#include <thread>

void getVariableValues(int& queueMaxSize, int& minSeconds, int& maxSeconds, int& timeToWait) {
	std::cout << "Max amount of cars waiting for ferry in queue: ";	std::cin >> queueMaxSize;
	std::cout << std::endl;
	std::cout << "Cars should be generated in range (seconds): " << std::endl; 
	std::cout << "from: "; std::cin >> minSeconds;
	std::cout << "to: "; std::cin >> maxSeconds;
	std::cout << std::endl;
	std::cout << "How long should ferry wait for cars to join (seconds)? "; std::cin >>timeToWait;
	
	system("cls");
}

int main() {
	
	int queueMaxSize;
	int minSeconds;
	int maxSeconds;
	int timeToWait;
	
	getVariableValues(queueMaxSize, minSeconds, maxSeconds, timeToWait);
	Ferry ferry(queueMaxSize,minSeconds,maxSeconds,timeToWait);
	

	ferry.ferryWork();

	return 0;
}

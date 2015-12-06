/*
 * Simulator.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#include "Simulator.h"
#include "Ram.h"
#include "Task.h"

Simulator::Simulator(std::vector<Task> tasks, int ramSize, int loadTime) :
	tasks(tasks),
	ram(Ram(ramSize)),
	loadTime(loadTime),
	swapMem(SwapMem()),
	simEnd(computeIntervalEnd())
{}

int Simulator::gcd(int a, int b) {
    while (true) {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

int Simulator::lcm(int a, int b) {
    int temp = gcd(a, b);
    return temp ? (a / temp * b) : 0;
}

int Simulator::computeIntervalEnd() {
	int max=tasks.begin()->getOffset();
	int lcm = tasks.begin()->getPeriod();
	for (std::vector<Task>::iterator it = ++tasks.begin(); it != tasks.end(); ++it) {
		if (max<it->getOffset()) {
			max = it->getOffset();
		}
		lcm = this->lcm(lcm,it->getPeriod());
	}
	return simEnd = max + (2*lcm);
}

void Simulator::run() {
}

bool Simulator::audsley(std::vector<Task> tasks) {
	if (tasks.size()==0) {
		return true;
	} else {
		Task* aTask = lowestPriorityViable(tasks);
		if (aTask==NULL) {
			return false;
		} else {
			//tasks.erase(*aTask);
			//audsley()
			//aTask->setPriority(--priority);
		}
	}
}

Task* Simulator::lowestPriorityViable(std::vector<Task> tasks) {
	/*int tot = 0;
	for (std::vector<Task>::iterator it = tasks.begin(); it != tasks.end(); ++it) {
		tot += (*it).;
	}*/
	return NULL;
}

Simulator::~Simulator() {
	// TODO Auto-generated destructor stub
}


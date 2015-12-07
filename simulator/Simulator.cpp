/*
 * Simulator.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#include "Simulator.h"
#include "Ram.h"
#include "Task.h"

#include <cmath>

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

int Simulator::computeStudyIntervalEnd(std::vector<Task*>*tasks,std::vector<Task*>::iterator last) {
	Task* aTask = *tasks->begin();
	int res = aTask->getOffset();
	int lcm = aTask->getPeriod();
	for (std::vector<Task*>::iterator it = ++tasks->begin(); it != tasks->end(); ++it) {
		aTask = *it;
		lcm = this->lcm(lcm,aTask->getPeriod());
		if (it != last) {
			res = aTask->getOffset() + std::ceil(float( res-aTask->getOffset()>0 ? res-aTask->getOffset() : 0)/aTask->getPeriod()) * aTask->getPeriod();
		}
	}
	aTask = *last;
	res = aTask->getOffset() + std::ceil(float(res-aTask->getOffset()>0 ? res-aTask->getOffset() : 0)/aTask->getPeriod()) * aTask->getPeriod();
	return res+lcm;
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
	std::vector<Task*> tasksRef;
	for (std::vector<Task>::iterator it = tasks.begin(); it != tasks.end(); ++it) {
		tasksRef.push_back(&(*it));
	}
	if (audsley(tasksRef)) {
		for (std::vector<Task>::iterator it = tasks.begin(); it != tasks.end(); ++it) {
			std::cout << it->getPriority() << std::endl;
		}
	} else {
		std::cout << "Impossible" << std::endl;
	}

}

bool Simulator::audsley(std::vector<Task*> tasksRef) {
	if (tasksRef.size()==0) {
		return true;
	} else {
		int pos = lowestPriorityViable(tasksRef);
		if (pos<0) {
			return false;
		} else {
			Task* lowestPriorityViableTask = *(tasksRef.begin()+pos);
			lowestPriorityViableTask->setPriority(tasksRef.size()-1);
			tasksRef.erase(tasksRef.begin()+pos);
			return audsley(tasksRef);
		}
	}
}

bool Simulator::eventOccures(int t, int o,int p) {
	return (t-o>=0) && ((t-o)%p==0);
}

int Simulator::lowestPriorityViable(std::vector<Task*> tasksRef) {
	for (int i=0; i<tasksRef.size(); ++i) {
		int cpt = 0, lowest = 0;
		std::vector<Task*>::iterator it = tasksRef.begin()+i;
		bool usable = true;
		int studyIntervalEnd = computeStudyIntervalEnd(&tasksRef,it);
		for (int t=0; t<studyIntervalEnd; ++t) {
			if (cpt>0) --cpt;
			else if (lowest>0) --lowest;

			for (std::vector<Task*>::iterator it2 = tasksRef.begin(); it2 != tasksRef.end(); ++it2) {
				Task* aTask = *it2;
				if ((it==it2) && eventOccures(t,aTask->getOffset()+aTask->getDeadline(),aTask->getPeriod())) {
					if (lowest>0) {
						usable = false;
						break;
					}
				}

				if (eventOccures(t,aTask->getOffset(),aTask->getPeriod())) {
					if (it!=it2) {
						cpt+=aTask->getWCET();
					} else {
						lowest+=aTask->getWCET();
					}
				}
			}

			if (!usable) {
				break;
			}
		}

		if (usable) {
			return i;
		}
	}
	return -1;
}

Simulator::~Simulator() {
	// TODO Auto-generated destructor stub
}


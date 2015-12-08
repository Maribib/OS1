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
	simEnd(computeIntervalEnd()),
	preemptionCpt(0),
	idleTime(0),
	swapTime(0)
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

bool Simulator::setPriorities() {
	std::vector<Task*> tasksRef;
	for (std::vector<Task>::iterator it = tasks.begin(); it != tasks.end(); ++it) {
		tasksRef.push_back(&(*it));
	}
	if (audsley(tasksRef)) {
		std::cout << "Priorities set." << std::endl;
		return true;
	} else {
		std::cout << "Impossible." << std::endl;
		return false;
	}
}

Task* Simulator::getHighestPriorityTask() {
	Task* highestPriorityTask = NULL;
	for (std::vector<Task>::iterator it = tasks.begin(); it!=tasks.end(); ++it ) {
		if ((!it->execFinished()) && ((highestPriorityTask==NULL) || (highestPriorityTask->getPriority()>it->getPriority()))) {
			highestPriorityTask = &(*it);
		}
	}
	return highestPriorityTask;
}

void Simulator::loadPages() {
	for (std::vector<Task>::iterator it = tasks.begin(); it!=tasks.end(); ++it ) {
		for (int p=0; p<it->getMemory(); ++p) {
			swapMem.push_back(Page(it->getPriority()));
		}
	}
}

bool Simulator::allPagesInRam(int id) {
	for (std::vector<Page>::iterator it = swapMem.begin(); it!=swapMem.end(); ++it) {
		if (it->getId()==id) {
			return false;
		}
	}
	return true;
}

void Simulator::loadAPage(int id) {
	std::vector<Page>::iterator toDel;
	for (std::vector<Page>::iterator it = swapMem.begin(); it!=swapMem.end(); ++it) {
		if (it->getId()==id) {
			toDel = it;
		}
	}
	swapMem.erase(toDel);
	ram.push_back(Page(id));
}


int Simulator::findVictim(int id) {
	int res = -1;
	for (std::vector<Page>::iterator it = ram.begin(); it!=ram.end(); ++it ) {
		if (it->getId()!=id) {
			for (std::vector<Task>::iterator it2 = tasks.begin(); it2!=tasks.end(); ++it2 ) {
				if (it2->getPriority()==it->getId()){
					if (res<it2->getLastUse()) {
						res = it2->getPriority();
					}
					break;
				}
			}
		}
	}
	return res;
}

void Simulator::swapPage(int victim, int id) {
	Page* p = NULL;
	for (std::vector<Page>::iterator it = swapMem.begin(); it!=swapMem.end(); ++it ) {
		if (it->getId()==id) {
			p = &(*it);
			break;
		}
	}
	for (std::vector<Page>::iterator it = ram.begin(); it!=ram.end(); ++it ) {
		if (it->getId()==victim) {
			it->swap(p);
			break;
		}
	}
}

void Simulator::increaseAllTaskLastUse() {
	for (std::vector<Task>::iterator it = tasks.begin(); it!=tasks.end(); ++it ) {
		it->increaseLastUse();
	}
}

Task* Simulator::taskReleased(int t,Task* highestPriorityTask) {
	for (std::vector<Task>::iterator it = tasks.begin(); it!=tasks.end(); ++it ) {
		if (eventOccures(t,it->getOffset(),it->getPeriod())) { // new task released
			it->resetExecTimeCpt();
		}
		if (!it->execFinished()) {
			if ((highestPriorityTask==NULL) || (highestPriorityTask->getPriority()>it->getPriority())) {
				highestPriorityTask = &(*it);
			}
		}
	}
	return highestPriorityTask;
}

bool Simulator::isPreemption(Task* aTask, Task* anotherTask) {
	return (aTask!=NULL) && (anotherTask!=NULL) && (aTask!=anotherTask);
}

Task* Simulator::executeProgram(Task* highestPriorityTask) {
	highestPriorityTask->decreaseExecTimeCpt(); // by the highest priority task
	increaseAllTaskLastUse();
	highestPriorityTask->resetLastUse();
	if (highestPriorityTask->execFinished()) { // task end CPU usage
		highestPriorityTask = NULL;
	}
	return highestPriorityTask;
}

void Simulator::handleLoadOrSwap(Task* highestPriorityTask) {
	if (!highestPriorityTask->swapFinished()) {
		highestPriorityTask->decreaseSwapTimeCpt();
		++swapTime;
		if (highestPriorityTask->swapFinished()) {
			if (ram.freePlaceLeft()) {
				loadAPage(highestPriorityTask->getPriority());
			} else {
				int victim = findVictim(highestPriorityTask->getPriority());
				swapPage(victim,highestPriorityTask->getPriority());
			}
		}
	}
}

void Simulator::display(int t, Task* highestPriorityTask) {
	if (highestPriorityTask==NULL) {
		std::cout << t << "\t" << "IDLE" << std::endl;
	} else {
		std::cout << t << "\t" << *highestPriorityTask << "\t" << std::endl;
	}
}

void Simulator::run() {
	bool status = this->setPriorities();
	if (status) {
		preemptionCpt = 0, swapTime = 0, idleTime = 0;
		loadPages();

		Task* highestPriorityTask = NULL;
		for (int t=0; t<simEnd; ++t) {
			if (highestPriorityTask!=NULL) { // CPU used
				if (allPagesInRam(highestPriorityTask->getPriority())) {
					highestPriorityTask = executeProgram(highestPriorityTask);
				} else {
					handleLoadOrSwap(highestPriorityTask);
				}
			}

			// Task release
			Task* newHighestPriorityTask = taskReleased(t,highestPriorityTask);
			if (isPreemption(newHighestPriorityTask,highestPriorityTask)) ++preemptionCpt;
			highestPriorityTask = newHighestPriorityTask;

			// Apply swap in/out delay
			if (highestPriorityTask!=NULL) {
				if (!allPagesInRam(highestPriorityTask->getPriority())) {
					if (highestPriorityTask->swapFinished()) {
						highestPriorityTask->setSwapTimeCpt(loadTime);
					}
				}
			}

			if (highestPriorityTask==NULL) ++idleTime;
			display(t,highestPriorityTask);
		}
		std::cout << "Preemptions : " << preemptionCpt << std::endl;
		std::cout << "Idle time : " << idleTime << std::endl;
		std::cout << "Swap time : " << swapTime << std::endl;
		std::cout << "System usage : " << float(simEnd-idleTime)*100/simEnd << "%" << std::endl;
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


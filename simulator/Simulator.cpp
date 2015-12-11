/*
 * Simulator.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#include "Simulator.h"
#include "Ram.h"
#include <cmath>
#include "../datastructure/Task.h"
#include "../pattern/Observable.h"

Simulator::Simulator(std::vector<Task> tasks, int ramSize, int loadTime) :
	Observable(),
	tasks(tasks),
	ram(Ram(ramSize)),
	loadTime(loadTime),
	swapMem(SwapMem()),
	simEnd(computeIntervalEnd()),
	utilization(computeUtilisation()),
	preemptionCpt(0),
	idleTime(0),
	swapTime(0),
	swapCpt(0),
	highestPriorityTask(NULL)
{}

float Simulator::computeUtilisation() {
	float utilization = 0;
	for (std::vector<Task>::iterator it= tasks.begin(); it!=tasks.end(); ++it) {
		utilization += float(it->getWCET())/it->getPeriod();
	}
	return utilization;
}

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

int Simulator::computeStudyIntervalEnd(std::vector<Task*>*tasks) {
	Task* aTask;
	for (std::vector<Task*>::iterator it = tasks->begin(); it != tasks->end(); ++it) {
		aTask = *it;
		if (aTask->getPeriod()==0) break;
	}
	int res = aTask->getOffset();
	int lcm = aTask->getPeriod();
	for (int i=0; i<tasks->size();++i ) {
		for (std::vector<Task*>::iterator it = tasks->begin(); it != tasks->end(); ++it) {
			aTask = *it;
			if (i==aTask->getPriority()) {
				lcm = this->lcm(lcm,aTask->getPeriod());
				res = aTask->getOffset() + std::ceil(float( res-aTask->getOffset()>0 ? res-aTask->getOffset() : 0)/aTask->getPeriod()) * aTask->getPeriod();
			}
		}
	}
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
	if (audsley(&tasksRef)) {
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

void Simulator::loadPages(std::vector<Task*>* tasksRef) {
	for (std::vector<Task*>::iterator it = tasksRef->begin(); it!=tasksRef->end(); ++it ) {
		Task* aTask = *it;
		for (int p=0; p<aTask->getMemory(); ++p) {
			swapMem.push_back(Page(aTask->getPriority()));
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


int Simulator::findVictim(std::vector<Task*>* tasksRef, int id) {
	int res = -1;
	for (std::vector<Page>::iterator it = ram.begin(); it!=ram.end(); ++it ) {
		if (it->getId()!=id) { // the victim cannot belong to the task to load
			for (std::vector<Task*>::iterator it2 = tasksRef->begin(); it2!=tasksRef->end(); ++it2 ) {
				Task* aTask = *it2;
				if (aTask->getPriority()==it->getId()){
					if (res<aTask->getLastUse()) {
						res = aTask->getPriority();
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

void Simulator::increaseAllTaskLastUse(std::vector<Task*>* tasksRef) {
	for (std::vector<Task*>::iterator it = tasksRef->begin(); it!=tasksRef->end(); ++it ) {
		(*it)->increaseLastUse();
	}
}

Task* Simulator::taskReleased(std::vector<Task*>* tasksRef,int t,Task* highestPriorityTask) {
	for (std::vector<Task*>::iterator it = tasksRef->begin(); it!=tasksRef->end(); ++it ) {
		Task* aTask = *it;
		if (eventOccures(t,aTask->getOffset(),aTask->getPeriod())) { // new task released
			aTask->resetExecTimeCpt();
		}
		if (!aTask->execFinished()) {
			if ((highestPriorityTask==NULL) || (highestPriorityTask->getPriority()>aTask->getPriority())) {
				highestPriorityTask = aTask;
			}
		}
	}
	return highestPriorityTask;
}

bool Simulator::isPreemption(Task* aTask, Task* anotherTask) {
	return (aTask!=NULL) && (anotherTask!=NULL) && (aTask!=anotherTask);
}

void Simulator::executeProgram(std::vector<Task*>* tasksRef, Task* highestPriorityTask) {
	highestPriorityTask->decreaseExecTimeCpt(); // by the highest priority task
	increaseAllTaskLastUse(tasksRef);
	highestPriorityTask->resetLastUse();
}

void Simulator::handleLoadOrSwap(std::vector<Task*>* tasksRef,Task* highestPriorityTask) {
	if (!highestPriorityTask->swapFinished()) {
		highestPriorityTask->decreaseSwapTimeCpt();
		++swapTime;
		if (highestPriorityTask->swapFinished()) {
			++swapCpt;
			if (ram.freePlaceLeft()) {
				loadAPage(highestPriorityTask->getPriority());
			} else {
				int victim = findVictim(tasksRef, highestPriorityTask->getPriority());
				swapPage(victim,highestPriorityTask->getPriority());
			}
		}
	}
}

void Simulator::display(int t, Task* highestPriorityTask) {
	if (highestPriorityTask==NULL) {
		std::cout << t << "\t" << "IDLE\t" ;
	} else {
		std::cout << t << "\t" << *highestPriorityTask << " ";
	}
	std::cout << swapMem << " " << ram << std::endl;
}

void Simulator::simulate() {
	bool status = this->setPriorities();
	if (status) {
		std::vector<Task*> tasksRef;
		for (std::vector<Task>::iterator it = tasks.begin(); it != tasks.end(); ++it) {
			tasksRef.push_back(&(*it));
		}
		run(&tasksRef, simEnd, 1);
	}
}

bool Simulator::meetDeadline(int t, Task* aTask) {
	if (eventOccures(t,aTask->getOffset()+aTask->getDeadline(),aTask->getPeriod()))
		return aTask->execFinished();
	else return true;
}

bool Simulator::meetAllDeadline(std::vector<Task*>* tasksRef,int t) {
	for (std::vector<Task*>::iterator it = tasksRef->begin(); it!=tasksRef->end(); ++it ) {
		if (!meetDeadline(t,*it)) {
			return false;
		}
	}
	return true;
}

void Simulator::swapInOutDelay() {
	if (highestPriorityTask!=NULL) {
		if (!allPagesInRam(highestPriorityTask->getPriority())) {
			if (highestPriorityTask->swapFinished()) {
				if (ram.freePlaceLeft()) highestPriorityTask->setSwapTimeCpt(loadTime);
				else highestPriorityTask->setSwapTimeCpt(loadTime*2);
			}
		}
	}
}

bool Simulator::run(std::vector<Task*>* tasksRef, int length, int verbose, Task* flaggedTask) {
	// Reset all datastructures and variables
	clean(tasksRef);
	preemptionCpt = 0, swapTime = 0, idleTime = 0, swapCpt = 0;

	loadPages(tasksRef);
	std::cout << length << " " << tasksRef->size() << std::endl;

	highestPriorityTask = NULL;
	for (int t=0; t<length; ++t) {

		if (highestPriorityTask!=NULL) { // CPU used
			if (allPagesInRam(highestPriorityTask->getPriority())) {
				executeProgram(tasksRef,highestPriorityTask);
				if (highestPriorityTask->execFinished()) { // task end CPU usage
					highestPriorityTask = NULL;
				}
			} else {
				handleLoadOrSwap(tasksRef,highestPriorityTask);
			}
		}

		if (flaggedTask==NULL) {
			if (!meetAllDeadline(tasksRef, t)) return false;
		} else {
			if (!meetDeadline(t,flaggedTask)) return false;
		}

		// Task release
		Task* newHighestPriorityTask = taskReleased(tasksRef,t,highestPriorityTask);
		if (isPreemption(newHighestPriorityTask,highestPriorityTask)) ++preemptionCpt;
		highestPriorityTask = newHighestPriorityTask;

		// Apply swap in/out delay
		swapInOutDelay();

		if (verbose>0) this->notifyAll();
		if (highestPriorityTask==NULL) ++idleTime;
		if (verbose>1) display(t,highestPriorityTask);
	}
	if (verbose>0) {
		std::cout << "Preemptions : " << preemptionCpt << std::endl;
		std::cout << "Idle time : " << idleTime << std::endl;
		std::cout << "Swap time : " << swapTime << std::endl;
		std::cout << "System utilization : " << utilization*100 << "%" << std::endl;
		std::cout << "Nb Swap : " << swapCpt << std::endl;
		std::cout << "System Load : " << float(simEnd-idleTime)*100/simEnd << "%" << std::endl;
	}
	return true;
}

bool Simulator::audsley(std::vector<Task*>* tasksRef) {
	if (tasksRef->size()==0) {
		return true;
	} else {
		int pos = lowestPriorityViable(tasksRef);
		if (pos<0) {
			return false;
		} else {
			Task* lowestPriorityViableTask = *(tasksRef->begin()+pos);
			lowestPriorityViableTask->setPriority(tasksRef->size()-1);
			tasksRef->erase(tasksRef->begin()+pos);
			return audsley(tasksRef);
		}
	}
}

bool Simulator::eventOccures(int t, int o,int p) {
	return (t-o>=0) && ((t-o)%p==0);
}

void Simulator::clean(std::vector<Task*>* tasksRef) {
	ram.clear();
	swapMem.clear();
	for (std::vector<Task*>::iterator it = tasksRef->begin(); it!=tasksRef->end(); ++it ) {
		(*it)->setExecTimeCpt(0);
		(*it)->setLastUse(-1);
		(*it)->setSwapTimeCpt(0);
	}
}

int Simulator::lowestPriorityViable(std::vector<Task*>* tasksRef) {
	for (int i = 0; i<tasksRef->size(); ++i) {
		tasksRef->at(i)->setPriority(tasksRef->size()-1);
		int p = 0;
		for (int j = 0; j<tasksRef->size(); ++j) {
			if (i!=j) tasksRef->at(j)->setPriority(p++);
		}
		bool status = run(tasksRef, computeStudyIntervalEnd(tasksRef),0,tasksRef->at(i));
		for (int j = 0; j<tasksRef->size(); ++j) tasksRef->at(j)->setPriority(-1);
		if (status) return i;
	}
	return -1;
}

Simulator::~Simulator() {
	// TODO Auto-generated destructor stub
}


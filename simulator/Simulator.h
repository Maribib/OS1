/*
 * Simulator.h
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#ifndef SIMULATOR_SIMULATOR_H_
#define SIMULATOR_SIMULATOR_H_

#include <vector>
#include <string>

#include "Ram.h"
#include "Task.h"
#include "SwapMem.h"

class Simulator {
public:
	Simulator(std::vector<Task>, int, int);
	void run();
	virtual ~Simulator();
private:
	int gcd(int, int);
	int lcm(int, int);
	bool setPriorities();
	void swapPage(int victim, int id);
	void loadPages();
	void increaseAllTaskLastUse();
	Task* taskReleased(int,Task*);
	bool allPagesInRam(int);
	void loadAPage(int);
	int findVictim(int);
	Task* getHighestPriorityTask();
	int computeIntervalEnd();
	Task* executeProgram(Task*);
	void handleLoadOrSwap(Task*);
	void display(int,Task*);
	bool isPreemption(Task*, Task*);
	bool eventOccures(int,int,int);
	int computeStudyIntervalEnd(std::vector<Task*>*,std::vector<Task*>::iterator);
	bool audsley(std::vector<Task*>);
	int lowestPriorityViable(std::vector<Task*>);

	std::vector<Task> tasks;
	int loadTime;
	Ram ram;
	SwapMem swapMem;
	int simEnd;
	int preemptionCpt;
	int idleTime;
	int swapTime;
};

#endif /* SIMULATOR_SIMULATOR_H_ */

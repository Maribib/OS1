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

#include "../datastructure/Task.h"
#include "Ram.h"
#include "SwapMem.h"

class Simulator {
public:
	Simulator(std::vector<Task>, int, int);
	void simulate();
	virtual ~Simulator();
private:
	bool meetDeadline(int,Task*);
	bool meetAllDeadline(std::vector<Task*>*,int);
	bool run(std::vector<Task*>*,int,bool,Task* = NULL);
	void clean(std::vector<Task*>*);
	int gcd(int, int);
	int lcm(int, int);
	bool setPriorities();
	void swapPage(int victim, int id);
	void loadPages(std::vector<Task*>*);
	void increaseAllTaskLastUse(std::vector<Task*>*);
	Task* taskReleased(std::vector<Task*>*,int,Task*);
	bool allPagesInRam(int);
	void loadAPage(int);
	int findVictim(std::vector<Task*>*,int);
	Task* getHighestPriorityTask();
	int computeIntervalEnd();
	void executeProgram(std::vector<Task*>*,Task*);
	void handleLoadOrSwap(std::vector<Task*>*,Task*);
	void display(int,Task*);
	bool isPreemption(Task*, Task*);
	bool eventOccures(int,int,int);
	int computeStudyIntervalEnd(std::vector<Task*>*);
	bool audsley(std::vector<Task*>*);
	int lowestPriorityViable(std::vector<Task*>*);

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

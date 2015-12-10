/*
 * Task.h
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 *
 */

#ifndef DATASTRUCTURE_TASK_H_
#define DATASTRUCTURE_TASK_H_

#include <string>
#include <vector>
#include <iostream>

#include "../datastructure/Page.h"

class Task {
public:
	Task(int, int, int, int, int);
	Task(std::vector<std::string>);
	virtual ~Task();

	int getOffset() { return this->offset; };
	int getPeriod() { return this->period; };
	void setDeadline(int deadline) { this->deadline = deadline; }
	int getDeadline() { return this->deadline; };
	int getWCET() { return this->WCET; };
	void setWCET(int WCET) { this->WCET = WCET; }
	int getMemory() { return this->memory; };

	int getPriority() { return this->priority; };
	void setPriority(int priority) { this->priority=priority; };

	void setLastUse(int lastUse) { this->lastUse=lastUse; }
	int getLastUse() { return this->lastUse; };
	void increaseLastUse() { ++this->lastUse; };
	void resetLastUse() { this->lastUse=0; };

	void setExecTimeCpt(int execTimeCpt) { this->execTimeCpt=execTimeCpt; }
	int getExecTimeCpt() { return this->execTimeCpt; }
	void resetExecTimeCpt() { this->execTimeCpt = this->WCET; };
	void decreaseExecTimeCpt() { --this->execTimeCpt; };
	bool execFinished() { return this->execTimeCpt==0; }

	int getSwapTimeCpt() { return this->swapTimeCpt; }
	void setSwapTimeCpt(int load) { this->swapTimeCpt = load; };
	void decreaseSwapTimeCpt() { --this->swapTimeCpt; };
	bool swapFinished() { return this->swapTimeCpt==0; }

	friend std::ostream& operator<< (std::ostream &out, Task &aTask);

private:
	int offset;
	int period;
	int deadline;
	int WCET;
	int memory;

	int execTimeCpt;
	int priority;
	int lastUse;
	int swapTimeCpt;

	std::vector<Page> pages;
};

#endif /* DATASTRUCTURE_TASK_H_ */

/*
 * Task.h
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 *
 */

#ifndef SIMULATOR_TASK_H_
#define SIMULATOR_TASK_H_

#include <string>
#include <vector>
#include <iostream>

#include "Page.h"

class Task {
public:
	Task(int, int, int, int, int);
	Task(std::vector<std::string>);
	virtual ~Task();

	int getOffset() { return this->offset; };
	int getPeriod() { return this->period; };
	int getDeadline() { return this->deadline; }
	int getWCET() { return this->WCET; }
	int getMemory() { return this->memory; }

	int getPriority() { return this->priority; }

	void setPriority(int priority) { this->priority=priority; }

	friend std::ostream& operator<< (std::ostream &out, Task &aTask);

private:
	int offset;
	int period;
	int deadline;
	int WCET;
	int memory;

	int timeLeft;
	int priority;

	std::vector<Page> pages;
};

#endif /* SIMULATOR_TASK_H_ */

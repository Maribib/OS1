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
	int computeIntervalEnd();
	bool audsley(std::vector<Task>);
	Task* lowestPriorityViable(std::vector<Task>);

	std::vector<Task> tasks;
	int loadTime;
	Ram ram;
	SwapMem swapMem;
	int simEnd;
};

#endif /* SIMULATOR_SIMULATOR_H_ */

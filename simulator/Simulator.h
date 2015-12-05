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

class Simulator {
public:
	Simulator(std::vector<Task>, int, int);
	void run();
	virtual ~Simulator();
private:
	std::vector<Task> tasks;
	int loadTime;
	Ram ram;
};

#endif /* SIMULATOR_SIMULATOR_H_ */

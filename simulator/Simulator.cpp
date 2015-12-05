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
	loadTime(loadTime)
{}

void Simulator::run() {

}

Simulator::~Simulator() {
	// TODO Auto-generated destructor stub
}


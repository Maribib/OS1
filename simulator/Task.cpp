/*
 * Task.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#include "Task.h"

Task::Task(int offset, int period, int deadline, int WCET, int memory) :
	offset(offset),
	period(period),
	deadline(deadline),
	WCET(WCET),
	memory(memory),
	execTimeCpt(0),
	lastUse(-1),
	swapTimeCpt(0)
{}

Task::Task(std::vector<std::string> infos) :
	offset(std::stoi(infos.at(0))),
	period(std::stoi(infos.at(1))),
	deadline(std::stoi(infos.at(2))),
	WCET(std::stoi(infos.at(3))),
	memory(std::stoi(infos.at(4))),
	execTimeCpt(0),
	lastUse(-1),
	swapTimeCpt(0)
{}

Task::~Task() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator<< (std::ostream &out, Task &aTask) {
	out << "Task [O:" << aTask.offset
			<< ", T:" << aTask.period
			<< ", D:" << aTask.deadline
			<< ", W:" << aTask.WCET
			<< ", M:" << aTask.memory
			<< ", C:" << aTask.execTimeCpt
			<< ", P:" << aTask.priority
			<< ", S:"  << aTask.swapTimeCpt
			<< ", U:"  << aTask.lastUse
			<< "]";
	return out;
}

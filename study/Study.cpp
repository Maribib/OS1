/*
 * Study.cpp
 *
 *  Created on: 10 déc. 2015
 *      Author: julianschembri
 */

#include <string>

#include "Study.h"
#include "../generator/Generator.h"
#include "../simulator/TaskFileParser.h"
#include "../simulator/Simulator.h"

#define H_UTILIZATION 80
#define L_UTILIZATION 40
#define H_MEMORY 6
#define L_MEMORY 3
#define H_NBTASKS 6
#define L_NBTASKS 3
#define RAM_SIZE 9
#define LOAD_TIME 2

Study::Study() {}

void Study::run(int utilization, int memory, int nbTasks, std::string fileName) {
	Generator g1(utilization,memory,nbTasks,fileName);
	g1.generate(); g1.toFile();
	TaskFileParser parser(fileName);
	std::vector<Task> tasks = parser.parse();
	Simulator s(tasks, RAM_SIZE, LOAD_TIME);
	s.simulate();
	std::cout << std::endl;
}

void Study::run(){
	run(H_UTILIZATION,H_MEMORY,H_NBTASKS,"test/1-HHH.tsk");
	run(H_UTILIZATION,H_MEMORY,L_NBTASKS,"test/2-HHL.tsk");
	run(H_UTILIZATION,L_MEMORY,H_NBTASKS,"test/3-HLH.tsk");
	run(H_UTILIZATION,L_MEMORY,L_NBTASKS,"test/4-HLL.tsk");
	run(L_UTILIZATION,H_MEMORY,H_NBTASKS,"test/5-LHH.tsk");
	run(L_UTILIZATION,H_MEMORY,L_NBTASKS,"test/6-LHL.tsk");
	run(L_UTILIZATION,L_MEMORY,H_NBTASKS,"test/7-LLH.tsk");
	run(L_UTILIZATION,L_MEMORY,L_NBTASKS,"test/8-LLL.tsk");
}


Study::~Study() {
	// TODO Auto-generated destructor stub
}


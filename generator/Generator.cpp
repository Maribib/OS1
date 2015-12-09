/*
 * Generator.cpp
 *
 *  Created on: 8 déc. 2015
 *      Author: julianschembri
 */

#include "Generator.h"
#include "../datastructure/Task.h"

#include <string>
#include <random>
#include <time.h>

Generator::Generator(int usage, int memory, int nbTasks, std::string fileName) {
	std::vector<Task> tasks;
	srand(time(NULL));
	float contribution = float(usage)/(100*nbTasks);
	for (int i=0; i<nbTasks; ++i) {
		int offset = rand() % 150;
		int WCET = 3+ (rand() % 40);
		int period=  WCET/contribution;
		int deadline=0;
		tasks.push_back(Task(offset, period, deadline, WCET, memory));
	}

	for (int i=0; i<10; ++i) {
		float pct = float((1+rand()%30))/100;

		int ind1 = rand()%nbTasks;
		int ind2 = rand()%nbTasks;
		while (ind2==ind1) ind2 = rand()%nbTasks;

		float realVal = float(tasks[ind1].getWCET())*pct/tasks[ind1].getPeriod();

		tasks[ind1].setWCET(int(float(tasks[ind1].getWCET())*(pct+1)));

		float realVal2 = float(tasks[ind2].getWCET())/tasks[ind2].getPeriod();
		float pct2 = (realVal2-realVal)/realVal2;

		tasks[ind2].setWCET(ceil(float(tasks[ind2].getWCET())*(pct2)));
	}

	float utilization = 0;
	for (std::vector<Task>::iterator it= tasks.begin(); it!=tasks.end(); ++it) {
		utilization += float(it->getWCET())/it->getPeriod();
		std::cout << it->getWCET() << " " << it->getPeriod() << " "<< float(it->getWCET())/it->getPeriod() << std::endl;
	}
	std::cout << utilization << std::endl;
}

Generator::~Generator() {
	// TODO Auto-generated destructor stub
}


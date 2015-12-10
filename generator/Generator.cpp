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
#include <vector>
#include <fstream>

Generator::Generator(int utilization, int memory, int nbTasks, std::string fileName) :
	utilization(utilization),
	memory(memory),
	nbTasks(nbTasks),
	fileName(fileName)
{}

void Generator::generate(){
	srand(time(NULL));
	float contribution = float(utilization)/(100*nbTasks);
	for (int i=0; i<nbTasks; ++i) {
		int offset = rand() % 150;

		int period= ((1+rand()%12)*20);
		// c = W / P
		int WCET;
		if (i%2==0) WCET = ceil(period*contribution);
		else WCET = period*contribution;

		int mem = 1+ (rand()%memory);
		int deadline=0;
		tasks.push_back(Task(offset, period, deadline, WCET, mem));
	}

	/*for (int i=0; i<10; ++i) {
		float pct = float((1+rand()%30))/100;

		int ind1 = rand()%nbTasks;
		int ind2 = rand()%nbTasks;
		while (ind2==ind1) ind2 = rand()%nbTasks;

		float realVal = float(tasks[ind1].getWCET())*pct/tasks[ind1].getPeriod();

		tasks[ind1].setWCET(int(float(tasks[ind1].getWCET())*(pct+1)));

		float realVal2 = float(tasks[ind2].getWCET())/tasks[ind2].getPeriod();
		float pct2 = (realVal2-realVal)/realVal2;

		tasks[ind2].setWCET(ceil(float(tasks[ind2].getWCET())*(pct2)));
	}*/

	float utilization = 0;
	for (std::vector<Task>::iterator it= tasks.begin(); it!=tasks.end(); ++it) {
		it->setDeadline(it->getPeriod()*(1-(float(rand()%20)/100)));
		utilization += float(it->getWCET())/it->getPeriod();
		//std::cout << it->getWCET() << " " << it->getPeriod() << " " << float(it->getWCET())/it->getPeriod() << std::endl;
	}
	std::cout << " ut : "<< utilization << std::endl;
}

void Generator::toFile() {
	std::cout << "Start writing in the file '" << fileName << "'...";
	std::ofstream file;
	file.open(fileName);
	if (file.is_open()) {
		for (std::vector<Task>::iterator it = tasks.begin(); it!=tasks.end(); ++it ) {
			file 	<< it->getOffset() << " "
					<< it->getPeriod() << " "
					<< it->getDeadline() << " "
					<< it->getWCET() << " "
					<< it->getMemory();
			if (it != --tasks.end()) {
				file << "\n";
			}
		}
		file.close();
		std::cout << "Succeed !" << std::endl;
	} else std::cout << "Failed !" << std::endl;
}

Generator::~Generator() {
	// TODO Auto-generated destructor stub
}


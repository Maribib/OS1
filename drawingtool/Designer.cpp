/*
 * Designer.cpp
 *
 *  Created on: 10 déc. 2015
 *      Author: julianschembri
 */

#include "../drawingtool/Designer.h"
#include "../pattern/Observer.h"
#include "../datastructure/Task.h"
#include "../simulator/Simulator.h"

#include <string>
#include <vector>

Designer::Designer(std::string fileName) :
	Observer(),
	render(10000, 300, 1.0, (fileName+".png").c_str()),
	tasks(NULL),
	t(0)
{}

void Designer::update(Observable* ob) {

	if (tasks==NULL) tasks=((Simulator*) ob)->getTasks();

	if (t%10==0) {
		render.line(5+t,0,5+t,600,0,0,0);
	}
	Task* currentTask = ((Simulator*) ob)->getCurrentTask();
	if (currentTask!=NULL) {
		if (!currentTask->swapFinished())
			render.filledsquare(5+t,10+currentTask->getPriority()*50,5+t,40+currentTask->getPriority()*50,65535,30000,30000);
		else
			render.filledsquare(5+t,10+currentTask->getPriority()*50,5+t,40+currentTask->getPriority()*50,30000,30000,30000);
	}



	t+=1;
}

Designer::~Designer() {
	for (int i=0; i<t; ++i) {
		for (std::vector<Task>::iterator it = tasks->begin(); it!=tasks->end(); ++it) {
			if (eventOccures(i,it->getOffset(),it->getPeriod())) {
				render.filledarrow(5+i,50+it->getPriority()*50,5+i,40+it->getPriority()*50,3,0.4236,65535,0,0);
			}
			if (eventOccures(i,it->getOffset()+it->getDeadline(),it->getPeriod())) {
				render.circle(5+i,10+it->getPriority()*50,3,65535,0,0);
			}
		}
	}


	render.close();
}


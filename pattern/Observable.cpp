/*
 * Observable.cpp
 *
 *  Created on: 10 déc. 2015
 *      Author: julianschembri
 */

#include "Observable.h"

#include <vector>

Observable::Observable() {
	// TODO Auto-generated constructor stub

}

void Observable::addObserver(Observer* ob) {
	obs.push_back(ob);
}

void Observable::notifyAll() {
	for (std::vector<Observer*>::iterator it = obs.begin(); it!=obs.end(); ++it) {
		(*it)->update(this);
	}
}

Observable::~Observable() {
	// TODO Auto-generated destructor stub
}


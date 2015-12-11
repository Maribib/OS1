/*
 * Observable.h
 *
 *  Created on: 10 déc. 2015
 *      Author: julianschembri
 */

#ifndef PATTERN_OBSERVABLE_H_
#define PATTERN_OBSERVABLE_H_

#include "Observer.h"

#include <vector>

class Observable {
public:
	Observable();
	void addObserver(Observer*);
	void notifyAll();
	virtual ~Observable();

private:
	std::vector<Observer*> obs;

};

#endif /* PATTERN_OBSERVABLE_H_ */

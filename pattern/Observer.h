/*
 * Observer.h
 *
 *  Created on: 10 déc. 2015
 *      Author: julianschembri
 */

#ifndef PATTERN_OBSERVER_H_
#define PATTERN_OBSERVER_H_

class Observable;

class Observer {
public:
	Observer();
	virtual void update(Observable*)=0;
	virtual ~Observer();
};

#endif /* PATTERN_OBSERVER_H_ */

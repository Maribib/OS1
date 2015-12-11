/*
 * Ram.h
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#ifndef SIMULATOR_RAM_H_
#define SIMULATOR_RAM_H_

#include <vector>

#include "../datastructure/Page.h"

class Ram : public std::vector<Page> {
public:
	Ram(int);
	bool freePlaceLeft();
	int getS(){return s;}
	friend std::ostream& operator<< (std::ostream &out, Ram &aRam);
	virtual ~Ram();
private:
	int s;
};

#endif /* SIMULATOR_RAM_H_ */

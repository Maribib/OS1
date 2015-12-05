/*
 * Ram.h
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#ifndef SIMULATOR_RAM_H_
#define SIMULATOR_RAM_H_

#include <vector>

#include "Page.h"

class Ram : public std::vector<Page> {
public:
	Ram(int);

	virtual ~Ram();
private:
	int size;
};

#endif /* SIMULATOR_RAM_H_ */

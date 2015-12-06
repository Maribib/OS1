/*
 * Ram.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#include "Ram.h"
#include "Page.h"

#include <vector>

Ram::Ram(int size) :
	std::vector<Page>(size)
{}



Ram::~Ram() {
	// TODO Auto-generated destructor stub
}


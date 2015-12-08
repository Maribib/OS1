/*
 * Ram.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#include "Ram.h"
#include <vector>
#include "../datastructure/Page.h"

Ram::Ram(int size) :
	std::vector<Page>(),
	s(size)
{}

bool Ram::freePlaceLeft() {
	return this->s>=this->size();
}

Ram::~Ram() {
	// TODO Auto-generated destructor stub
}


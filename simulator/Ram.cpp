/*
 * Ram.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#include "Ram.h"

#include <vector>
#include <iostream>

#include "../datastructure/Page.h"

Ram::Ram(int size) :
	std::vector<Page>(),
	s(size)
{}

bool Ram::freePlaceLeft() {
	return this->s>=this->size();
}

std::ostream& operator<< (std::ostream &out, Ram &aRam) {
	out << "Ram [" ;
	for (std::vector<Page>::iterator it = aRam.begin(); it!=aRam.end(); ++it) {
		out << it->getId() << ", ";
	}
	out << "]" ;
	return out;
}


Ram::~Ram() {
	// TODO Auto-generated destructor stub
}


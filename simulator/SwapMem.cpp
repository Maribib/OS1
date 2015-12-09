/*
 * SwapMem.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#include "SwapMem.h"

#include <iostream>

SwapMem::SwapMem() :
	std::vector<Page>()
{}

SwapMem::~SwapMem() {
	// TODO Auto-generated destructor stub
}


std::ostream& operator<< (std::ostream &out, SwapMem &aSwapMem) {
	out << "SwapMem [" ;
	for (std::vector<Page>::iterator it = aSwapMem.begin(); it!=aSwapMem.end(); ++it) {
		out << it->getId() << ", ";
	}
	out << "]" ;
	return out;
}


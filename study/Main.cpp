/*
 * Main.cpp
 *
 *  Created on: 10 déc. 2015
 *      Author: julianschembri
*/

#include <stdio.h>
#include <iostream>
#include <string>

#include "Study.h"

int main( int argc, const char* argv[] ) {
	if (1<argc) {
		std::cout << "Usage is : ./studyAudsley" << std::endl;
	} else {
		Study s;
		s.run();
	}
	return 0;
}

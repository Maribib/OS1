/*
 * Main.cpp
 *
 *  Created on: 8 déc. 2015
 *      Author: julianschembri
 */

#include <iostream>
#include <string>
#include <stdio.h>

#include "Generator.h"

#define D_USAGE 70
#define D_MEMORY 3
#define D_TASKS 8
#define D_FILENAME "tasks.txt"

int main( int argc, const char* argv[] ) {
	if (9<argc) {
		std::cout << "Usage is : ./taskGenerator -u 70 -m 3 -n 8 -o tasks.txt" << std::endl;
	} else {
		int usage = D_USAGE;
		int memory = D_MEMORY;
		int tasks = D_TASKS;
		std::string fileName = D_FILENAME;

		for (int i=0;i<argc;++i) {
			if (std::string(argv[i])=="-u") usage = std::stoi(argv[i+1]);
			if (std::string(argv[i])=="-m") memory = std::stoi(argv[i+1]);
			if (std::string(argv[i])=="-n") tasks = std::stoi(argv[i+1]);
			if (std::string(argv[i])=="-o") fileName = argv[i+1];
		}

		Generator t(usage, memory, tasks, fileName);
		t.generate();
		t.toFile();
	}
	return 0;
}


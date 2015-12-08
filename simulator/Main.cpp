#include <stdio.h>
#include <iostream>
#include <string>

#include "TaskFileParser.h"
#include "Task.h"
#include "Simulator.h"

int main( int argc, const char* argv[] ) {
	if ((argc<3) || (4<argc)) {
		std::cout << "Usage is : ./simAudsley <tasksFile> <ram> <load>=1" << std::endl;
	} else {
		std::string taskFileName = std::string(argv[1]);
		int ramSize = int(std::stoi(argv[2]));
		int loadTime = argc==4 ? int(std::stoi(argv[3])) : 1;

		TaskFileParser parser(taskFileName);
		std::vector<Task> tasks = parser.parse();

		Simulator s(tasks, ramSize, loadTime);
		s.run();
	}
	return 0;
}


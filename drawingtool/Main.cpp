/*
 * Main.cpp
 *
 *  Created on: 9 déc. 2015
 *      Author: julianschembri
 */

#include "../simulator/TaskFileParser.h"
#include "../simulator/Simulator.h"
#include "Designer.h"

int main(int argc, char** argv) {
	TaskFileParser t("test/task.txt");
	Simulator s(t.parse(),10,2);

	Designer d("test");
	s.addObserver(&d);
	s.simulate();
	return 0;
}

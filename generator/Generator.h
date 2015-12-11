/*
 * Generator.h
 *
 *  Created on: 8 déc. 2015
 *      Author: julianschembri
 */

#ifndef GENERATOR_GENERATOR_H_
#define GENERATOR_GENERATOR_H_

#include <string>
#include <vector>

#include "../datastructure/Task.h"

class Generator {
public:
	Generator(int,int,int,std::string);
	void generate();
	void toFile(bool = false);
	virtual ~Generator();
	static void init();
private:
	int utilization;
	int memory;
	int nbTasks;
	std::string fileName;
	std::vector<Task> tasks;

};

#endif /* GENERATOR_GENERATOR_H_ */

/*
 * TaskFileParser.h
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#ifndef SIMULATOR_TASKFILEPARSER_H_
#define SIMULATOR_TASKFILEPARSER_H_

#include <string>
#include <vector>

#include "Task.h"

class TaskFileParser {
public:
	TaskFileParser(std::string);
	std::vector<Task> parse();
	virtual ~TaskFileParser();
private:
	std::string fileName;
	std::vector<std::string> split(std::string, char);
};

#endif /* SIMULATOR_TASKFILEPARSER_H_ */

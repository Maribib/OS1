/*
 * TaskFileParser.cpp
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 *
 * Row Format : Offset Period Deadline WCET Memory
 */

#include "TaskFileParser.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "../datastructure/Task.h"

TaskFileParser::TaskFileParser(std::string aTaskFileName) :
	fileName(aTaskFileName)
{}

std::vector<Task> TaskFileParser::parse() {
	std::vector<Task> res;
	std::ifstream file(this->fileName);
	if (file.is_open()) {
		std::string line;
		while(getline(file,line)) {
			std::vector<std::string> inlineTask = this->split(line,' ');
			res.push_back(Task(inlineTask));
		}
		file.close();
	} else std::cout << "Unable to open file." << std::endl;
	return res;
}

std::vector<std::string> TaskFileParser::split(std::string str, char delimiter) {
	std::vector<std::string> res;
	std::stringstream ss(str);
	std::string tok;

	while(getline(ss, tok, delimiter)) {
		res.push_back(tok);
	}

	return res;
}

TaskFileParser::~TaskFileParser() {
	// TODO Auto-generated destructor stub
}


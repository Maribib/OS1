/*
 * Study.h
 *
 *  Created on: 10 déc. 2015
 *      Author: julianschembri
 */

#ifndef STUDY_STUDY_H_
#define STUDY_STUDY_H_

class Study {
public:
	Study();
	void run();
	void run(int,int,int,std::string,std::string);
	virtual ~Study();
	static void init();
};

#endif /* STUDY_STUDY_H_ */

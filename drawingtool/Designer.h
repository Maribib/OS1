/*
 * Designer.h
 *
 *  Created on: 10 déc. 2015
 *      Author: julianschembri
 */

#ifndef DRAWINGTOOL_DESIGNER_H_
#define DRAWINGTOOL_DESIGNER_H_

#include "../pattern/Observer.h"
#include "../datastructure/Task.h"

#include <pngwriter.h>
#include <string>
#include <vector>

class Designer : public Observer {
public:
	Designer(std::string);
	bool eventOccures(int t, int o,int p) { return (t-o>=0) && ((t-o)%p==0); }
	void update(Observable*);
	virtual ~Designer();
private:
	pngwriter render;
	std::vector<Task>* tasks;
	int t;
};

#endif /* DRAWINGTOOL_DESIGNER_H_ */

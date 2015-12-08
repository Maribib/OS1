/*
 * Page.h
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#ifndef SIMULATOR_PAGE_H_
#define SIMULATOR_PAGE_H_

class Page {
public:
	Page(int);

	int getId() { return this->id; };
	void swap(Page* p) {
		int tmp = this->id;
		this->id = p->id;
		p->id = tmp;
	}

	virtual ~Page();
private:
	int id;
};

#endif /* SIMULATOR_PAGE_H_ */

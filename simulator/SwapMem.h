/*
 * SwapMem.h
 *
 *  Created on: 5 déc. 2015
 *      Author: julianschembri
 */

#ifndef SIMULATOR_SWAPMEM_H_
#define SIMULATOR_SWAPMEM_H_

#include <vector>

#include "Page.h"

class SwapMem : public std::vector<Page>{
public:
	SwapMem();
	virtual ~SwapMem();
};

#endif /* SIMULATOR_SWAPMEM_H_ */

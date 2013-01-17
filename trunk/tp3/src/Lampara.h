/*
 * Lampara.h
 *
 *  Created on: Jan 16, 2013
 *      Author: damian
 */

#ifndef LAMPARA_H_
#define LAMPARA_H_

#include <vector>
#include "Curves/Coordinate.h"
#include "Generic.h"

class Lampara {
public:
	Lampara();
	void print();
	virtual ~Lampara();

private:
	Generic* generic;
};

#endif /* LAMPARA_H_ */

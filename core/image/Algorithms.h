/*
 * Algorithms.h
 *
 *  Created on: Oct 5, 2010
 *      Author: brueckner
 */

#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

namespace NICE {

//! converts a gray value \in [0.0,1.0] to a pseudo color red,green,blue \in [0.0,1.0]
void grayToPseudoColor(double gray, double & red, double & green, double & blue);

//! converts a gray value \in [0,255] to a pseudo color red,green,blue \in [0,255]
void grayToPseudoColor(int gray, int & red, int & green, int & blue);

}

#endif /* ALGORITHMS_H_ */

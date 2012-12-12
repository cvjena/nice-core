/*
 * Algorithms.cpp
 *
 *  Created on: Oct 5, 2010
 *      Author: brueckner
 */

#include "Algorithms.h"

namespace NICE {

void grayToPseudoColor(double gray, double & red, double & green, double & blue) {
	int sector = static_cast<int> (gray * 4.0);
	gray = 4.0 * gray - sector;

	switch (sector) {
	case 0:
		red = 1.0;
		green = gray;
		blue = 0.0;
		break;
	case 1:
		red = 1.0 - (gray);
		green = 1.0;
		blue = 0.0;
		break;
	case 2:
		red = 0.0;
		green = 1.0;
		blue = gray;
		break;
	case 3:
		red = 0.0;
		green = 1.0 - (gray);
		blue = 1.0;
		break;
	default:
		red = 0.0;
		green = 0.0;
		blue = 1.0;
		break;
	}
}

void grayToPseudoColor(int gray, int & red, int & green, int & blue) {
	double grayD = (double)gray/255.0;
	double redD,blueD,greenD;
	grayToPseudoColor(grayD, redD, greenD, blueD);
	red = (int)(redD*255.0);
	green = (int)(greenD*255.0);
	blue = (int)(blueD*255.0);
}

}



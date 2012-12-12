//
// C++ Interface: EpipolarGeometryVisualizer
//
// Description: 
//
//
// Author: Marcel Brueckner <brueckner [at] informatik [dot] uni-jena [dot] de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef _IMAGEDISPLAY_EPIPOLARGEOMETRYVISUALIZER_H
#define _IMAGEDISPLAY_EPIPOLARGEOMETRYVISUALIZER_H

#include <core/imagedisplay/ImageDisplay.h>
#include <core/vector/MatrixT.h>
#include <core/image/CoordT.h>
#include <vector>

namespace NICE {
	
class EpipolarGeometryDisplay : public ImageDisplay {
	Q_OBJECT;
public:
	EpipolarGeometryDisplay (std::vector< CoordT<double> >* points,
									 std::vector< std::pair<CoordT<double>, CoordT<double> > >* epipolarLines,
			QWidget* parent = NULL, const char* name = NULL,
               Qt::WFlags flags = 0);
	
	inline void addPoint (const Vector& point) {
		double x = point[0]/point[2];
		double y = point[1]/point[2];
		if (x > 0.0 && y > 0.0 && x < imageWidth() && y < imageHeight()) {
			m_points->push_back(CoordT<double>(x/imageWidth(), 1.0f - y/imageHeight()));
		}
	}
	
	void addEpipolarLine (const Vector& epipolarLine);
	
	inline void clearPoints(void) {
		m_points->clear();
	}
	
	inline void clearEpipolarLines(void) {
		m_epipolarLines->clear();
	}
	
protected:
	//! receive mouse events
	virtual void mousePressEvent(QMouseEvent* event);

	virtual void setGLProjection(void);
	
	virtual void paintGLObjects(void);	

private:
	virtual void contextMenuEvent(QContextMenuEvent* event);
	
	std::vector< CoordT<double> >* m_points;
	std::vector< std::pair<CoordT<double>, CoordT<double> > >* m_epipolarLines;
};

}

#endif


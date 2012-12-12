//
// C++ Interface: PolygonDrawer
//
// Description: 
//
//
// Author: Marcel Brueckner <brueckner [at] informatik [dot] uni-jena [dot] de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef IMAGEDISPLAY_POLYGONDRAWER_H
#define IMAGEDISPLAY_POLYGONDRAWER_H

#include <core/imagedisplay/ImageDisplay.h>
#include <core/image/CoordT.h>
#include <fstream>

namespace NICE {

class PolygonDrawer : public ImageDisplay {
	Q_OBJECT;
public:
	PolygonDrawer ( QWidget* parent = NULL, const char* name = NULL,
	                Qt::WFlags flags = 0 );
	
	virtual ~PolygonDrawer(void);
	
	inline const std::vector < CoordT<double> >& getPolygon (void) const {
		return m_points;
	}
	
	inline void clearPolygon (void) {
		m_points.clear();
		updateGL();
	}
	
protected:
	virtual void paintGLObjects(void);
	
	virtual void mousePressEvent(QMouseEvent* event);

private:
	virtual void contextMenuEvent(QContextMenuEvent* event);
	
	//! points of the polygon
	std::vector < CoordT<double> > m_points;	
};

}

#endif


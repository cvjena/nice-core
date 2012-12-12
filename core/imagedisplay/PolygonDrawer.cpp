//
// C++ Implementation: PolygonDrawer
//
// Description: 
//
//
// Author: Marcel Brueckner <brueckner [at] informatik [dot] uni-jena [dot] de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "PolygonDrawer.h"

namespace NICE {
	
	
PolygonDrawer::PolygonDrawer ( QWidget* parent,
                               const char* name ,
                               Qt::WFlags flags )
		: ImageDisplay ( parent, name, flags )
{
};

PolygonDrawer::~PolygonDrawer() {
}

void PolygonDrawer::paintGLObjects(void) {
	if (m_points.size() > 0) {
		glPointSize(5);
		glBegin(GL_POINTS);
		for (unsigned int i = 0; i < m_points.size(); ++i) {
			float xPos = m_points[i].x*width();
			float yPos = m_points[i].y*height();
			glVertex2f(xPos, yPos);
		}
		glEnd();	

		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glLineWidth(3);
		glColor4f(1, 1, 1, 1);
		glBegin(GL_LINE_LOOP);
		for (unsigned int i = 0; i < m_points.size(); ++i) {
			float xPos = m_points[i].x*width();
			float yPos = m_points[i].y*height();
			glVertex2f(xPos, yPos);
		}
		glEnd();
		glFlush();
	}
};

void PolygonDrawer::mousePressEvent(QMouseEvent* event) {
  QGLWidget::mousePressEvent(event);
  
  switch (event->button()) {
		case Qt::LeftButton: {
			m_points.push_back(CoordT<double>(static_cast<float>(event->x())/width(), 1.0f - static_cast<float>(event->y())/height()));
			updateGL();
		} break;
		
	  case Qt::RightButton:
			m_points.clear();
			updateGL();
			break;
		
		default:
			break;
	}
}

void PolygonDrawer::contextMenuEvent(QContextMenuEvent* event) {
}

}//namespace NICE


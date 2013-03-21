//
// C++ Implementation: EpipolarGeometryVisualizer
//
// Description:
//
//
// Author: Marcel Brueckner <brueckner [at] informatik [dot] uni-jena [dot] de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "EpipolarGeometryDisplay.h"
#include <QGridLayout>

#ifdef NICE_USELIB_GLUT
#include <GL/glut.h>
#endif

namespace NICE {

EpipolarGeometryDisplay::EpipolarGeometryDisplay ( std::vector< CoordT<double> >* points,
    std::vector< std::pair<CoordT<double>, CoordT<double> > >* epipolarLines,
    QWidget* parent, const char* name,
    Qt::WFlags flags )
    : ImageDisplay ( parent, name, flags ), m_points ( points ), m_epipolarLines ( epipolarLines )

{
}

void EpipolarGeometryDisplay::addEpipolarLine ( const Vector& epipolarLine ) {
  CoordT<double> start;
  CoordT<double> end;

  bool startOK = false;
  bool endOK = false;

  if ( isZero ( epipolarLine[1], 1e-20 ) ) {
    double x = -epipolarLine[2] / epipolarLine[0];

    if ( x >= 0.0 && x <= imageWidth() - 1.0 ) {
      start.x = ( x / imageWidth() );
      start.y = ( 1.0 );
      startOK = true;

      end.x = ( x / imageWidth() );
      end.y = ( 0.0 );
      endOK = true;
    }
  } else {
    double x1 = - epipolarLine[2] / epipolarLine[0];
    double x2 = - epipolarLine[1] / epipolarLine[0] * imageHeight() + x1;

    double y1 = - epipolarLine[2] / epipolarLine[1];
    double y2 = - epipolarLine[0] / epipolarLine[1] * imageWidth() + y1;

    if ( x1 >= 0.0 && x1 <= imageWidth() ) {
      if ( !startOK ) {
        start.x = ( x1 / imageWidth() );
        start.y = ( 1.0 );
        startOK = true;
      } else if ( !endOK ) {
        end.x = ( x1 / imageWidth() );
        end.y = ( 1.0 );
        endOK = true;
      }
    }

    if ( x2 >= 0.0 && x2 <= imageWidth() ) {
      if ( !startOK ) {
        start.x = ( x2 / imageWidth() );
        start.y = ( 0.0 );
        startOK = true;
      } else if ( !endOK ) {
        end.x = ( x2 / imageWidth() );
        end.y = ( 0.0 );
        endOK = true;
      }
    }

    if ( y1 >= 0.0 && y1 <= imageHeight() ) {
      if ( !startOK ) {
        start.x = ( 0.0 );
        start.y = ( 1.0f - y1 / imageHeight() );
        startOK = true;
      } else if ( !endOK ) {
        end.x = ( 0.0 );
        end.y = ( 1.0f - y1 / imageHeight() );
        endOK = true;
      }
    }

    if ( y2 >= 0.0 && y2 <= imageHeight() ) {
      if ( !startOK ) {
        start.x = ( 1.0 );
        start.y = ( 1.0f - y2 / imageHeight() );
        startOK = true;
      } else if ( !endOK ) {
        end.x = ( 1.0 );
        end.y = ( 1.0f - y2 / imageHeight() );
        endOK = true;
      }
    }
  }

  if ( startOK && endOK )
    m_epipolarLines->push_back ( std::pair<CoordT<double> , CoordT<double> > ( start, end ) );
}

void EpipolarGeometryDisplay::mousePressEvent ( QMouseEvent* event )
{
  QGLWidget::mousePressEvent ( event );

  switch ( event->button() )
  {
    case Qt::LeftButton:
    {
      m_points->push_back ( CoordT<double> ( static_cast<float> ( event->x() ) / width(),
                                             1.0f - static_cast<float> ( event->y() ) / height() ) );
      updateGL();
    }
    break;

    default:
      break;
  }
}

void EpipolarGeometryDisplay::setGLProjection ( void ) {
  glViewport ( 0, 0, width(), height() );
  glMatrixMode ( GL_PROJECTION );
  glLoadIdentity();
#ifdef NICE_USELIB_GLUT
  gluOrtho2D ( 0.0, ( GLdouble ) width(), 0.0, ( GLdouble ) height() );
#endif
}

void EpipolarGeometryDisplay::paintGLObjects ( void ) {

  if ( m_points->size() > 0 ) {
    glPointSize ( 3 );
    glBegin ( GL_POINTS );
    for ( unsigned int i = 0; i < m_points->size(); ++i ) {
      float xPos = m_points->operator[] ( i ).x*width();
      float yPos = m_points->operator[] ( i ).y*height();
      glVertex2f ( xPos, yPos );
    }
    glEnd();
    glFlush();
  }

  if ( m_epipolarLines->size() > 0 ) {
    glEnable ( GL_LINE_SMOOTH );
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glHint ( GL_LINE_SMOOTH_HINT, GL_DONT_CARE );
    glLineWidth ( 2 );
    glColor4f ( 1, 1, 1, 1 );
    for ( unsigned int i = 0; i < m_epipolarLines->size(); ++i ) {
      glBegin ( GL_LINE_LOOP );
      float xPos = m_epipolarLines->operator[] ( i ).first.x*width();
      float yPos = m_epipolarLines->operator[] ( i ).first.y*height();
      glVertex2f ( xPos, yPos );
      xPos = m_epipolarLines->operator[] ( i ).second.x*width();
      yPos = m_epipolarLines->operator[] ( i ).second.y*height();
      glVertex2f ( xPos, yPos );
      glEnd();
    }
    glFlush();
  }
}

void EpipolarGeometryDisplay::contextMenuEvent ( QContextMenuEvent* event ) {
}



}


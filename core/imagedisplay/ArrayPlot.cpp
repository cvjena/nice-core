//
// C++ Implementation: ArrayPlot
//
// Description:
//
//
// Author: Marcel Brueckner <brueckner [at] informatik [dot] uni-jena [dot] de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "core/basics/Exception.h"
#include "ArrayPlot.h"
#include <iostream>
#include <core/basics/numerictools.h>

#ifdef NICE_USELIB_GLUT
#include <GL/glut.h>
#endif

namespace NICE {

ArrayPlot::ArrayPlot ( std::vector<double> probs,
                       unsigned int width,
                       unsigned int height,
                       bool invertColors,
                       QWidget* parent,
                       const char* name ,
                       Qt::WFlags flags )
    : QGLWidget ( parent, name, NULL, flags ),
    m_width ( width ),
    m_height ( height ),
    m_maxProb ( -std::numeric_limits<double>::infinity() ),
    m_minProb ( std::numeric_limits<double>::infinity() ),
    m_probs ( probs ),
    m_xPos ( 0 ),
    m_yPos ( 0 ),
    m_invertColors ( invertColors )
{
  if ( ( m_width * m_height ) != m_probs.size() )
    std::cerr << "MProbDisplay: INCONSISTENT SIZES!" << std::endl;

  for ( unsigned int i = 0 ; i < m_probs.size(); ++i ) {
    if ( m_probs[i] > m_maxProb )
      m_maxProb = m_probs[i];

    if ( m_probs[i] < m_minProb )
      m_minProb = m_probs[i];
  }
};

ArrayPlot::~ArrayPlot() {
}

void ArrayPlot::paintGL ( void ) {
#ifdef NICE_USELIB_OPENGL
  glViewport ( 0, 0, width(), height() );
  glMatrixMode ( GL_PROJECTION );
  glLoadIdentity();
#   ifdef NICE_USELIB_GLUT
  gluOrtho2D ( 0.0, ( GLdouble ) width(), 0.0, ( GLdouble ) height() );
#   endif

  double quadWidth = width() / ( double ) ( m_width );
  double quadHeight = height() / ( double ) ( m_height );
  double difference = m_maxProb - m_minProb;
  glEnable ( GL_BLEND );
  glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  if ( isZero ( difference, 1e-20 ) )
    difference = 1.0;
  for ( unsigned int i = 0; i < m_width; ++i ) {
    for ( unsigned int j = 0; j < m_height; ++j ) {
      float value = ( m_probs[i * m_height + j] - m_minProb ) / ( m_maxProb - m_minProb );
      double r, g, b;
      toColor ( value, r, g, b );
      glColor4f ( r, g, b, 1 );
      glBegin ( GL_QUADS );
      glVertex2f ( quadWidth*i, ( j + 1 ) *quadHeight );
      glVertex2f ( quadWidth*i,     j*quadHeight );
      glVertex2f ( quadWidth* ( i + 1 ), j*quadHeight );
      glVertex2f ( quadWidth* ( i + 1 ), ( j + 1 ) *quadHeight );
      glEnd();
    }
  }

  glEnable ( GL_LINE_SMOOTH );
  glHint ( GL_LINE_SMOOTH_HINT, GL_DONT_CARE );
  glLineWidth ( 3 );
  glColor4f ( 1, 1, 1, 1 );
  glBegin ( GL_LINE_LOOP );
  glVertex2f ( quadWidth*m_xPos, ( m_yPos + 1 ) *quadHeight );
  glVertex2f ( quadWidth*m_xPos,     m_yPos*quadHeight );
  glVertex2f ( quadWidth* ( m_xPos + 1 ), m_yPos*quadHeight );
  glVertex2f ( quadWidth* ( m_xPos + 1 ), ( m_yPos + 1 ) *quadHeight );
  glEnd();

  glFlush();

#else
  fthrow(Exception,"OpenGL lib not availabe, recompile using OpenGL!");
#endif
};

void ArrayPlot::mousePressEvent ( QMouseEvent* event )
{
  QGLWidget::mousePressEvent ( event );

  switch ( event->button() )
  {
    case Qt::LeftButton:
    {
      m_xPos = static_cast<int> ( double ( event->x() * m_width ) / width() );
      m_yPos = static_cast<int> ( double ( ( height() - event->y() ) * m_height ) / height() );
      updateGL();
    }
    break;

    default:
      break;
  }
}

void ArrayPlot::repaint() {
  updateGL();
}

void ArrayPlot::toColor ( double x, double & r, double & g, double & b )
{
  if ( m_invertColors )
    x = 1.0 - x;

  int sector = static_cast<int> ( x * 4.0 );
  x = 4.0 * x - sector;

  switch ( sector ) {
    case 0:
      r = 1.0;
      g = x;
      b = 0.0;
      break;
    case 1:
      r = 1.0 - ( x );
      g = 1.0;
      b = 0.0;
      break;
    case 2:
      r = 0.0;
      g = 1.0;
      b = x;
      break;
    case 3:
      r = 0.0;
      g = 1.0 - ( x );
      b = 1.0;
      break;
    default:
      r = 0.0;
      g = 0.0;
      b = 1.0;
      break;
  }

}

}

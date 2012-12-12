/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimagedisplay - A library for image and video display
 * See file License for license information.
 */

#include <core/image/RectangleT.h>
#include <core/image/CrossT.h>
#include <core/imagedisplay/OverlayColors.h>
#include <core/basics/stringutils.h>

#include "SimpleSelector.h"

using namespace std;

namespace NICE {

SimpleSelector::SimpleSelector ( bool drawRectangle,
    bool drawCross, int maxColors,
    QWidget *parent, const char *name, Qt::WFlags flags)
    : ImageDisplay ( parent, name, flags ),
      m_markColor (1),
      m_maxColors(maxColors),
      m_drawRectangle(drawRectangle), m_drawCross(drawCross)
{
    connect(this, SIGNAL(rectSelect(float,float,float,float)),
              this, SLOT(rectSelect(float,float,float,float)));

    setDrawSelectionRect ( m_drawRectangle );

    m_crossSize = 10;
}
  
void SimpleSelector::rectSelect(float left, float top, float right, float bottom)
{
    RectT<double> r ( CoordT<float>(left, top), CoordT<float>( right, bottom) );
    m_rectangles.push_back ( r );
    m_rectanglesColor.push_back ( m_markColor );
    updateGL();
}
  
void SimpleSelector::addExtraMenuItems ( Q3PopupMenu *popupMenu )
{
    colorMenuMap.clear();
    for ( int color = 1 ; color <= m_maxColors ; color++ )
    {
		string caption = "Color/Class " + itostr(color);
		int id = popupMenu->insertItem ( QString(caption.c_str()), this, SLOT(dummy()) );
		colorMenuMap.insert ( pair<int, int> ( id, color ) );
    }

    connect (popupMenu, SIGNAL(activated(int)), this, SLOT(menuActivated(int)));
    popupMenu->insertSeparator();
}
  
void SimpleSelector::dummy(void)
{
}

void SimpleSelector::menuActivated ( int id ) 
{
    map<int, int>::const_iterator i = colorMenuMap.find(id);
    if ( i != colorMenuMap.end()  ) 
		setCurrentColor(i->second);
}

void SimpleSelector::setCurrentColor ( int color )
{
    m_markColor = color;
}

void SimpleSelector::paintGLObjects(void)
{
    int index = 0;
    for ( vector<RectT<double> >::const_iterator i = m_rectangles.begin();
	    i != m_rectangles.end(); i++,index++ )
    {
		int rColor = m_rectanglesColor[index];
		int mark_r = overlayColorTable[ rColor % overlayColorTableNumEntries ][0];
		int mark_g = overlayColorTable[ rColor % overlayColorTableNumEntries ][1];
		int mark_b = overlayColorTable[ rColor % overlayColorTableNumEntries ][2];

		const RectT<double> & r = *i;
		double left = r.left * width() / image->width();
		double right = r.right() * width() / image->width();
		double top = r.top * height() / image->height();
		double bottom = r.bottom() * height() / image->height();
		if ( m_drawRectangle )
		{
			glLineWidth(1);
			glColor4f(mark_r, mark_g, mark_b, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2f(left, height() - top);
			glVertex2f(left, height() - bottom);
			glVertex2f(right, height() - bottom);
			glVertex2f(right, height() - top);
			glEnd();
			glFlush();
		}

		if ( m_drawCross ) 
		{
			glLineWidth(1);
			glColor4f(mark_r, mark_g, mark_b, 1);
			glBegin(GL_LINES);
			glVertex2f(left, height() - top - m_crossSize );
			glVertex2f(left, height() - top + m_crossSize );
			glVertex2f(left - m_crossSize, height() - top );
			glVertex2f(left + m_crossSize, height() - top );
			glEnd();
			glFlush();
		}
    }

}

SimpleSelector::~SimpleSelector ()
{
}

void SimpleSelector::addRectangle ( const NICE::RectT<double> & rectangle, int color )
{
	m_rectangles.push_back ( rectangle );
	m_rectanglesColor.push_back ( color );
}


};

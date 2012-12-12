/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
/*
 *  $Author: bajramov $
 *  $Date: 2009/05/28 11:36:30 $
 *  $Revision: 1.2 $
 */
/*****************************************************************************/

#include "core/image/PointT.h"

namespace NICE {

// Constructors:
// -------------
template<class P>
PointT<P>::PointT(const PointT<P>& ex) : Drawable<P>(ex)
{
  *this=ex;
}

// Operators:
// ----------
template<class P>
PointT<P>& PointT<P>::operator=(const PointT<P>& ex)
{
  coord=ex.coord;
  this->defaultColor=ex.defaultColor;
  return *this;
}

template<class P>
bool PointT<P>::operator==(const PointT<P>& ex) const
{
  if(coord==ex.coord && this->defaultColor==ex.defaultColor)
      return true;
  return false;
}

template<class P>
bool PointT<P>::operator!=(const PointT<P>& ex) const {
    return !(this->operator==(ex));
}

// Methods:
// --------
template<class P>
void PointT<P>::doDraw(ColorImageT<P> &image, const ColorT<P>& color) const
{
    if(coord.x>=0 && coord.y>=0  &&
       coord.x<image.width() && coord.y<image.height())
        image.setPixelQuick(coord,color);
}
template<class P>
void PointT<P>::doDraw(ImageT<P> &image, const P& gray) const
{
    if(coord.x>=0 && coord.y>=0  &&
       coord.x<image.width() && coord.y<image.height())
        image.setPixelQuick(coord,gray);
}

// Destructor:
// -----------
template<class P>
PointT<P>::~PointT()
{
}


}; // namespace NICE

/*****************************************************************************/
/*
 *  $Log: PointT.tcc,v $
 *  Revision 1.2  2009/05/28 11:36:30  bajramov
 *  renamed a few things for consistency
 *
 *  Revision 1.2  2008/05/26 18:26:51  bajramov
 *  warnings
 *
 *  Revision 1.1.1.1  2007/05/22 19:26:35  bajramov
 *  limun2
 *
 *  Revision 1.6  2007/05/03 12:07:28  bajramov
 *  docu
 *
 *  Revision 1.5  2007/02/04 15:32:50  zimmermann
 *  * added operator !=
 *  * bugfix operator == : circle, color
 *  * bugfix operator =  : point, circle
 *  * expended gray() in ColorT for size()==3
 *  * expended draw for ColorImage, to draw gray Drawables
 *  * added new constructor PointT(Coord)
 *
 *  Revision 1.4  2006/11/02 13:36:16  zimmermann
 *  * insert some 'this->'
 *
 *  Revision 1.3  2006/11/01 16:05:24  bajramov
 *  Further changes to Drawable and subclasses.
 *  Methods draw() of ImageT/ColorImageT with iterator parameter renamed to drawIter().
 *  New Drawable CrossT.
 *
 *  Revision 1.2  2006/11/01 15:18:14  bajramov
 *  added drawing methods with color/gray value parameter
 *
 *  Revision 1.1  2006/06/29 10:16:03  bajramov
 *  classes and functions for drawing points, lines, ellipses, ...
 *
 *  Revision 1.2  2006/02/09 09:39:14  mattern
 *  * template update
 *
 *  Revision 1.3  2006/02/02 10:50:12  mattern
 *  * Template changed
 *
 *  Revision 1.2  2005/07/28 09:56:34  bajramov
 *  License
 *
 *  Revision 1.1.1.1  2005/07/22 13:53:17  mattern
 *  Librarys for IMage UNderstanding
 *
 */

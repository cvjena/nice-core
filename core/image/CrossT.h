/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _CROSS_IMAGE_H
#define _CROSS_IMAGE_H

#include <iostream>

#include <core/image/Drawable.h>
#include <core/image/CoordT.h>
#include <core/image/ColorT.h>

namespace NICE {

/**
 * A Drawabele cross with lines parallel to coordinate axes / image borders
 * or 45° diagonal.
 */
template<class P>
class CrossT  : public Drawable<P>
{
private:
  Coord center;
  unsigned int halfWidth;
  bool diagonal;
protected:
  void doDraw(ColorImageT<P> &image, const ColorT<P>& color) const;
  void doDraw(ImageT<P> &image, const P& gray) const;
public:
  //! Default constructor
  inline CrossT() {}

  CrossT(const Coord &_center, const unsigned int _halfWidth,
         bool _diagonal = false);
  CrossT(const Coord &_center, const unsigned int _halfWidth,
         bool _diagonal, const ColorT<P>& _defaultColor);

  //! Copy-Constructor
  /*! \param arg class to copy
  */
  CrossT(const CrossT<P>& arg);

  //! Destructor of CrossT
  virtual ~CrossT();

  //! Assignment operator
  /*! \param ex class to copy
   *  \return a reference to this class
   */
  CrossT<P>& operator=(const CrossT<P>& ex);

  //! Compare operator
  /*! \param ex class to compare
   *  \return true if class content is equal
   */
  bool operator==(const CrossT<P>& ex) const;

  //! Compare operator
  /*! \param ex class to compare
   *  \return true if class content is not equal
   */
  bool operator!=(const CrossT<P>& ex) const;

};

typedef CrossT<Ipp8u> Cross;

} // namespace NICE

#ifdef __GNUC__
#include "core/image/CrossT.tcc"
#endif

#endif /* _CROSS_IMAGE_H */

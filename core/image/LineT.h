/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
#ifndef _LINE_IMAGE_H
#define _LINE_IMAGE_H

#include <iostream>

#include <core/image/Drawable.h>
#include <core/image/CoordT.h>
#include <core/image/ColorT.h>

namespace NICE {

/**
 * A Drawable line.
 */
template<class P>
class LineT  : public Drawable<P>
{
private:
    bool steep;
    Coord begin;
    Coord end;
protected:
  void doDraw(ColorImageT<P> &image, const ColorT<P>& color) const;
  void doDraw(ImageT<P> &image, const P& gray) const;
public:
  //! Default constructor
  inline LineT() {}

  //! Constructor
  /** \param begin begin of the line
   *  \param end   end of the line
   */
  LineT(const Coord &begin, const Coord &end);

  //! Constructor
  /** \param begin          begin of the line
   *  \param end            end of the line
   *  \param _defaultColor  color of the line
   */
  LineT(const Coord &begin, const Coord &end, const ColorT<P>& _defaultColor);

  //! Copy-Constructor
  /*! \param arg class to copy
  */
  LineT(const LineT<P>& arg);

  //! Destructor of LineT
  virtual ~LineT();

  //! Assignment operator
  /*! \param ex class to copy
   *  \return a reference to this class
   */
  LineT<P>& operator=(const LineT<P>& ex);

  //! Compare operator
  /*! \param ex class to compare
   *  \return true if class content is equal
   */
  bool operator==(const LineT<P>& ex) const;

  //! Compare operator
  /*! \param ex class to compare
   *  \return true if class content is not equal
   */
  bool operator!=(const LineT<P>& ex) const;

};

typedef LineT<Ipp8u> Line;

} // namespace NICE

//#ifdef __GNUC__
#include "core/image/LineT.tcc"
//#endif

#endif /* _LINE_IMAGE_H */

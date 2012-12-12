/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
/*! \file GHough.h
    \brief GHough class declaration
 */
/*****************************************************************************/
/*
 *  $Author: bajramov $
 *  $Date: 2009/05/28 11:36:30 $
 *  $Revision: 1.2 $
*/
/*****************************************************************************/

#ifndef _GHOUGH_IMAGE_H
#define _GHOUGH_IMAGE_H

#include <iostream>

#include <core/image/ImageT.h>

namespace NICE {

/**
 * Hough transformation.
 */
class GHough
{
public:
    //! pixel neighbors enumeration
    typedef enum {SINGLE_BIN, FOUR_NEIGHBORS, EIGHT_NEIGHBORS, HALF_OVERLAP} NeighborType;
private:
    //! the Hough Transform space
    FloatImage houghmap;
    //! Size of the image space
    IppiSize imageSize;
    //! Size of the transform space
    IppiSize transformSize;
    //! indicates if the transform space has been allocated
    bool isInitialized;
    //! Which bins to increment during add operation
    NeighborType addMode;

    //! Checks if a point is within zero and the specified bounds
    inline bool boundsOkay(const Coord &pt, const IppiSize &bounds) const;

public:

  //! Default constructor
  GHough();

  //! Constructor of optional argument with default-value
  /** @param imageSize     size of the image
   *  @param transformSize size of transformation area
   *  @param addMode        neighbor type
   */
  GHough(IppiSize imageSize, IppiSize transformSize, NeighborType addMode);

  //! Copy-Constructor
  /*! \param arg class to copy
	*/
  GHough(const GHough& arg);

  //! Destructor of GHough
  virtual ~GHough(){}

  //! Cast operator to char*
  //operator char*();

  //! Assignment operator
  /*! \param ex class to copy
   *  \return a reference to this class
   */
  GHough& operator=(const GHough& ex);

  //! Adds activation to a set/one Hough Transform bins
  /*!
    * \param pt location in the image space of the pixel point
	* \param activation value to add to the bin(s)
   **/
  void addPoint(const Coord &pt, float activation = 1.0);

  //! Adds activation to a set/one Hough Transform bins
  /*!
    * \param x x-coordinate in the image space of the pixel point
    * \param y y-coordinate in the image space of the pixel point
	* \param activation value to add to the bin(s)
   **/
  void addPoint(float x, float y, float activation = 1.0);

  //! Transforms a point from the image spage to the Hough Space giving top-left bin if overlap
  Coord transformPoint(const Coord &pt) const;

  //! Transforms a point from the image spage to the Hough Space giving best bin if overlap
  Coord nearestTransformPoint(const Coord &pt) const;

  //! Transforms a point from the Hough Space to the Image Space
  Coord invTransformPoint(const Coord &pt) const;

  //! allocates memory for the transform space
  /**
   * \param	imageSize  Size of the Image
   * \param	transformSize  Size of the Hough Transform space
   * \param	addMode  which bins to add activation to.
   * Possible options: SINGLE_BIN, FOUR_NEIGHBORS, EIGHT_NEIGHBORS
   **/
  void initialize(IppiSize imageSize,IppiSize transformSize, NeighborType addMode);

  //! allocates memory for the transform space
  /**
   * \param	image       an image
   * \param	scalefactor transformSize
   * \param	addMode     which bins to add activation to.
   * Possible options: SINGLE_BIN, FOUR_NEIGHBORS, EIGHT_NEIGHBORS
   **/
  template<class IMAGE>
  void initialize(const IMAGE &image, float scalefactor, NeighborType addMode);

  //! allocates memory for the transform space
  /**
   * \param width       width of the image
   * \param height      height of the image
   * \param scalefactor transformSize
   * \param addMode     which bins to add activation to.
   * Possible options: SINGLE_BIN, FOUR_NEIGHBORS, EIGHT_NEIGHBORS
   **/
  void initialize(int width, int height, float scalefactor, NeighborType addMode);

  //! Returns the Map as FloatImage
  const FloatImage &getMap() const;
  //! Finds the location with the maximum activation
  Coord getMaxLoc() const;
  //! Finds the value of the the maximum activation
  float getMax() const;
  //! Returns the activation value at any point
  float getVal(int x, int y) const;
  //! Returns the activation value at any point
  float getVal(const Coord &pt) const;
  //! Clears the transform space
  void clear();
};

}; // namespace NICE

#endif /* _GHOUGH_IMAGE_H */

/*****************************************************************************/
/*
 *  $Log: GHough.h,v $
 *  Revision 1.2  2009/05/28 11:36:30  bajramov
 *  renamed a few things for consistency
 *
 *  Revision 1.1.1.1  2007/05/22 19:26:35  bajramov
 *  limun2
 *
 *  Revision 1.3  2007/02/07 19:09:42  zimmermann
 *  * fixed documentation warnings
 *
 *  Revision 1.2  2006/09/21 14:03:54  mattern
 *  .
 *
 *  Revision 1.1  2006/09/15 15:23:58  mattern
 *  general hough transformation
 *
 */

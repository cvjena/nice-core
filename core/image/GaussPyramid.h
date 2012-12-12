/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#ifndef LIMUN_GAUSSSPYRAMID_H
#define LIMUN_GAUSSSPYRAMID_H


#include "core/image/ColorImageT.h"
#include "core/image/ImageT.h"
#include <vector>

namespace NICE {

/**
 * This class builds a Gaussian resolution hierarchy (pyramid)
 * of an input image.
 */
class GaussPyramid
{
  private:
        float rate;
        IppiPyramid *gPyramid;
        IppiPyramid *lPyramid;
        std::vector<FloatImage> gaussimage;
        std::vector<FloatImage> laplaceimage;

    void buildGaussPyramid(uint levelin, float rate);

  public:
    //! Constructor for fixed number of levels
    /*! \param src Input gray image, also the toplevel image
     *  \param levelin number of pyramid levels you wish to add
     *  \param rate sampling rate {1.5,2.0}
       */
    GaussPyramid(const Image& src, uint levelin, float rate);
    //! Constructor for fixed number of levels
    /*! \param src Input float image, also the toplevel image
     *  \param levelin number of pyramid levels you wish to add
     *  \param rate sampling rate {1.5,2.0}
       */
    GaussPyramid(const FloatImage& src, uint levelin, float rate);
    //! Constructor for fixed size of the smallest image
    /*! \param src Input gray image, also the toplevel image
     *  \param sizeMinX width of the smallest image
     *  \param sizeMinY height of the smallest image
     *  \param rate sampling rate {1.5,2.0}
     */
    GaussPyramid(const Image& src, uint sizeMinX, uint sizeMinY, float rate);
    //! Constructor for fixed size of the smallest image
    /*! \param src Input float image, also the toplevel image
     *  \param sizeMinX width of the smallest image
     *  \param sizeMinY height of the smallest image
     *  \param rate sampling rate {1.5,2.0}
     */
    GaussPyramid(const FloatImage& src, uint sizeMinX, uint sizeMinY, float rate);

    //! Destructor of GaussPyramid
    ~GaussPyramid();

    //! Return const gauss image on level nr as FloatImage
    /*! \param nr the level
     *  \return gauss image on level nr
     */
    const FloatImage &getGauss(uint nr) const;

    //! Return const gauss image on level nr as Image
    /*! \param nr the level
     *  \return gauss image on level nr
     */
    Image getGaussGray(uint nr) const;

    //! Return const laplace image on level nr
    /*! \param nr the level
     *  \return laplace image on level nr
     */
    const FloatImage &getLaplace(uint nr) const;

    //! Return number of levels
    /*! \return number of levels
     */
    int getLevel() const {return gPyramid->level+1;}

    //! Translate the coordinates of the gauss level to the original coordinates.
    Coord CoordOrig(int level, const Coord &coord);
    //!  Translate the coordinates of the original coordinates to the gauss level.
    Coord CoordLevel(int level, const Coord &coord);
    //!  Translate the coordinates one level up.
    Coord CoordUp(int level, const Coord &coord);
    //!  Translate the coordinates one level down.
    Coord CoordDown(int level, const Coord &coord);

    //! Find local minima and maxima
    //void FindLocalDOGMaxMin(std::vector<) const
};

}// namespace

#endif //LIMUN_GAUSSSPYRAMID_H

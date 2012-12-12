
#ifndef _LIMUN_OPERATORST_H
#define _LIMUN_OPERATORST_H

// #ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
//     #include <iocompression/gzbinstream.h>
// #endif
#include <core/basics/binstream.h>


#include "core/image/ippwrapper.h"

#include "core/image/Convert.h"
#include "core/image/ImageT.h"
#include "core/image/ImageT.h"
#include <ostream>


namespace NICE {

template<class P>
inline std::ostream& operator<<(std::ostream &out, const ImageT<P>& img)
{
    for(int y=0;y<img.height();y++) {
        for(int x=0;x<img.width();x++) {
            out << img.getPixelQuick(x,y) << " ";
        }
        out << std::endl;
    }
    return out;
}

inline std::ostream& operator<<(std::ostream &out, const ImageT<Ipp8u>& img)
{
    for(int y=0;y<img.height();y++) {
        for(int x=0;x<img.width();x++) {
            out << static_cast<int>(img.getPixelQuick(x,y)) << " ";
        }
        out << std::endl;
    }
    return out;
}

//#ifdef NICE_USELIB_ZLIB
    template<class P>
    inline obinstream& operator<<(obinstream &out, const ImageT<P>& img)
    {
        out << img.width() << img.height() << sizeof(P);
        for(int y=0;y<img.height();y++) {
            for(int x=0;x<img.width();x++) {
                out << img.getPixelQuick(x,y);
            }
        }
        return out;
    }

    template<class P>
    inline ibinstream& operator>>(ibinstream &in, ImageT<P>& img)
    {
        int width,height,bytedepth;
        in >> width >> height >> bytedepth;
        if(width!=img.width() || height!=img.height())
            img.resize(width,height);
        if(bytedepth!=sizeof(P))
            fthrow(ImageException, "wrong bitdepth while reading from file");
        for(int y=0;y<img.height();y++) {
            for(int x=0;x<img.width();x++) {
                P pixel;
                in >> pixel;
                img.setPixelQuick(x,y,pixel);
            }
        }
        return in;
    }
//#endif

template<class P>
inline std::ostream& operator<<(std::ostream &out, const ColorImageT<P>& img)
{
    for(int y=0;y<img.height();y++) {
        for(int x=0;x<img.width();x++) {
            out << "(" << img.getPixelQuick(x,y,0) << ","
                << img.getPixelQuick(x,y,1) << "," << img.getPixelQuick(x,y,2) << ") ";
        }
        out << std::endl;
    }
    return out;
}

inline std::ostream& operator<<(std::ostream &out, const ColorImageT<Ipp8u>& img)
{
    for(int y=0;y<img.height();y++) {
        for(int x=0;x<img.width();x++) {
            out << "(" << (int)img.getPixelQuick(x,y,0) << ","
                << (int)img.getPixelQuick(x,y,1) << "," << (int)img.getPixelQuick(x,y,2) << ") ";
        }
        out << std::endl;
    }
    return out;
}

/**
* @name Image Operators
* \{
*/

    /**
    * Negates an GrayImage16s
    * @param a GrayImage16s to negate
    * @return GrayImage16s
    */
    inline GrayImage16s operator-(const GrayImage16s& a)
    {
        GrayImage16s result(a.width(),a.height());

        IppStatus ret = ippiMulC_C1RSfs(a.getPixelPointer(), a.getStepsize(),
                                        static_cast<Ipp16s>(-1),
                                        result.getPixelPointer(),
                                        result.getStepsize(), makeROIFullImage(a), 0); //IPP: 0 = no Scaling!

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return result;
    }

    /**
    * Subtracts the FloatImage \c b from the FloatImage \c a and overwrite \c a
    * @param a source FloatImage
    * @param b FloatImage to subtract
    * @return FloatImage
    */
    inline FloatImage& operator-=(FloatImage& a, const FloatImage& b)
    {
        IppStatus ret = ippiSub_C1IR(b.getPixelPointer(), b.getStepsize(),
                                     a.getPixelPointer(), a.getStepsize(),
                                     makeROIFullImage(a));
        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return a;
    }

    /**
    * Subtracts the FloatImage \c b from the FloatImage \c a
    * @param a source FloatImage
    * @param b FloatImage to subtract
    * @return FloatImage
    */
    inline const FloatImage operator-(const FloatImage& a, const FloatImage& b)
    {
        FloatImage result(a.width(), a.height());

        IppStatus ret = ippiSub_C1R(b.getPixelPointer(), b.getStepsize(),
                                    a.getPixelPointer(), a.getStepsize(),
                                    result.getPixelPointer(), result.getStepsize(),
                                    makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return result;
    }

    /**
    * Subtracts the float constant \c c from all Pixels of the FloatImage \c a  and overwrite \c a
    * @param a source FloatImage
    * @param c float constant to subtract
    * @return FloatImage
    */
    inline FloatImage& operator-=(FloatImage& a, Ipp32f c)
    {
        IppStatus ret = ippiSubC_C1IR(c, a.getPixelPointer(), a.getStepsize(),  makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return a;
    }

    /**
    * Subtracts the float value \c c from all Pixels of the FloatImage \c a
    * @param a source FloatImage
    * @param c float value to subtract
    * @return FloatImage
    */
    inline const FloatImage operator-(const FloatImage& a, Ipp32f c)
    {
        FloatImage result(a.width(), a.height());

        IppStatus ret = ippiSubC_C1R(a.getPixelPointer(), a.getStepsize(), c,
                                     result.getPixelPointer(), result.getStepsize(), makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return result;
    }

    /**
    * Adds the FloatImage \c b to the FloatImage \c a and overwrite \c a
    * @param a source FloatImage
    * @param b FloatImage to add
    * @return FloatImage
    */
    inline FloatImage& operator+=(FloatImage& a, const FloatImage& b)
    {
        IppStatus ret = ippiAdd_C1IR(b.getPixelPointer(), b.getStepsize(),
                                     a.getPixelPointer(), a.getStepsize(), makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return a;
    }

    /**
    * Adds the integer constant \c c to the GrayImage16s \c a and overwrite \c a
    * @param a source GrayImage16s
    * @param c integer constant to add
    * @return GrayImage16s
    */
    inline GrayImage16s& operator+=(GrayImage16s& a, const Ipp16s& c)
    {
        IppStatus ret = ippiAddC_C1IRSfs(c, a.getPixelPointer(), a.getStepsize(), makeROIFullImage(a), 0);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return a;
    }

    /**
    * Adds the FloatImage \c b to the FloatImage \c a
    * @param a source FloatImage
    * @param b FloatImage to add
    * @return FloatImage
    */
    inline const FloatImage operator+(const FloatImage& a, const FloatImage& b)
    {
        FloatImage result(a.width(), a.height());

        IppStatus ret = ippiAdd_C1R(b.getPixelPointer(), b.getStepsize(),
                                    a.getPixelPointer(), a.getStepsize(),
                                    result.getPixelPointer(), result.getStepsize(),
                                    makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return result;
    }

    /**
    * Adds the float constant \c c to every pixel of the FloatImage \c a and overwrite \c a
    * @param a source FloatImage
    * @param c float constant to add
    * @return FloatImage
    */
    inline FloatImage& operator+=(FloatImage& a, Ipp32f c)
    {
        IppStatus ret = ippiAddC_C1IR(c, a.getPixelPointer(), a.getStepsize(), makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return a;
    }

    /**
    * Adds the float constant \c c to the FloatImage \c a
    * @param a source FloatImage
    * @param c float constant to add
    * @return FloatImage
    */
    inline const FloatImage operator+(const FloatImage& a, Ipp32f c)
    {
        FloatImage result(a.width(), a.height());

        IppStatus ret = ippiAddC_C1R(a.getPixelPointer(), a.getStepsize(), c,
                                     result.getPixelPointer(), result.getStepsize(),
                                     makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return result;
    }

    /**
    * Multiply the FloatImage \c b with the FloatImage \c a and overwrite \c a
    * @param a source FloatImage
    * @param b FloatImage to multiply with
    * @return FloatImage
    */
    inline FloatImage& operator*=(FloatImage& a, const FloatImage& b)
    {
        IppStatus ret = ippiMul_C1IR(b.getPixelPointer(), b.getStepsize(),
                                     a.getPixelPointer(), a.getStepsize(),
                                     makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return a;
    }

    /**
    * Multiply the FloatImage \c b with the FloatImage \c a
    * @param a source FloatImage
    * @param b FloatImage to multiply with
    * @return FloatImage
    */
    inline const FloatImage operator*(const FloatImage& a, const FloatImage& b)
    {
        FloatImage result(a.width(), a.height());

        IppStatus ret = ippiMul_C1R(b.getPixelPointer(), b.getStepsize(),
                                    a.getPixelPointer(), a.getStepsize(),
                                    result.getPixelPointer(), result.getStepsize(), makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return result;
    }

    /**
    * Multiply the float constant \c c with the FloatImage \c a and overwrite \c a
    * @param a source FloatImage
    * @param c float constant to multiply with
    * @return FloatImage
    */
    inline FloatImage& operator*=(FloatImage& a, Ipp32f c)
    {
        IppStatus ret = ippiMulC_C1IR(c, a.getPixelPointer(), a.getStepsize(), makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return a;
    }

    /**
    * Multiply the gray constant \c c with the Image \c a and overwrite \c a
    * @param a source Image
    * @param c gray constant to multiply with
    * @return Image
    */
    inline Image operator*=(Image& a, Ipp8u c)
    {
        IppStatus ret = ippiMulC_C1IRSfs(c, a.getPixelPointer(), a.getStepsize(), makeROIFullImage(a),0);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return a;
    }

    /**
    * Multiply the float constant \c c with the FloatImage \c a
    * @param a source FloatImage
    * @param c float constant to multiply with
    * @return FloatImage
    */
    inline const FloatImage operator*(const FloatImage& a, Ipp32f c)
    {
        FloatImage result(a.width(), a.height());

        IppStatus ret = ippiMulC_C1R(a.getPixelPointer(), a.getStepsize(), c,
                                     result.getPixelPointer(), result.getStepsize(), makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return result;
    }

    /**
    * Multiply the gray constant \c c with the Image \c a
    * @param a source Image
    * @param c gray constant to multiply with
    * @return Image
    */
    inline const Image operator*(const Image& a, Ipp8u c)
    {
        Image result(a.width(), a.height());

        IppStatus ret = ippiMulC_C1RSfs(a.getPixelPointer(), a.getStepsize(), c,
                                        result.getPixelPointer(), result.getStepsize(),
                                        makeROIFullImage(a),0);

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return result;
    }

    /**
    * Divides the FloatImage \c a by FloatImage \c a and overwrite \c a
    * @param a source FloatImage
    * @param b FloatImage to divide by
    * @return FloatImage
    * @example image_operator.cpp
    */
    inline FloatImage& operator/=(FloatImage& a, const FloatImage& b)
    {
        IppStatus ret = ippiDiv_C1IR(b.getPixelPointer(), b.getStepsize(),
                                     a.getPixelPointer(), a.getStepsize(), makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return a;
    }

    /**
    * Divides the FloatImage \c a by FloatImage \c a
    * @param a source FloatImage
    * @param b FloatImage to divide by
    * @return FloatImage
    */
    inline const FloatImage operator/(const FloatImage& a, const FloatImage& b)
    {
        FloatImage result(a.width(), a.height());

        IppStatus ret  = ippiDiv_C1R(b.getPixelPointer(), b.getStepsize(),
                                     a.getPixelPointer(), a.getStepsize(),
                                     result.getPixelPointer(), result.getStepsize(),
                                     makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return result;
    }

    /**
    * Divides the FloatImage \c a by the the float constant \c c and overwrite \c a
    * @param a source FloatImage
    * @param c float constant to devide by
    * @return FloatImage
    */
    inline FloatImage& operator/=(FloatImage& a, Ipp32f c)
    {
        IppStatus ret = ippiDivC_C1IR(c, a.getPixelPointer(), a.getStepsize(), makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return a;
    }

    /**
    * Divides the FloatImage \c a by the the float constant \c c
    * @param a source FloatImage
    * @param c float constant to devide by
    * @return FloatImage
    */
    inline const FloatImage operator/(const FloatImage& a, Ipp32f c)
    {
        FloatImage result(a.width(), a.height());

        IppStatus ret = ippiDivC_C1R(a.getPixelPointer(), a.getStepsize(), c,
                                     result.getPixelPointer(), result.getStepsize(),
                                     makeROIFullImage(a));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

        return result;
    }

/**
 * \}
 */

} // namespace

#endif // _LIMUN_OPERATORST_H

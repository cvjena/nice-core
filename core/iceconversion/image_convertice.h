/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libicelink - An icelink/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
/**
 * @file convertice.h
 * Conversion to/from ICE images.
 * @note
 * This file requires the ICE library.
 * However, that library is NOT defined as a dependency in the
 * limun image library. If you use this file, you have to use ICE, too.
 * This shouldn't be a problem, as this file is only useful if you are using
 * ICE already.
 */
#ifndef _CONVERTICE_IMAGE_H
#define _CONVERTICE_IMAGE_H

#include "core/image/ImageT.h"
#include "core/image/ColorImageT.h"
#include "core/basics/types.h"
// ICE
#include <image_nonvis.h>

namespace NICE
{

    /**
     * For internal use.
     */
    inline unsigned char invert255(unsigned char value, bool invert)
    {
        if (invert)
        {
            return 255 - value;
        }
        else
        {
            return value;
        }
    }

    /**
     * Create a new \c NICE::Image from an \c ice::Image.
     * @param source The source image.
     * @param invertImage Invert the image? Note: ICE works with inverted images.
     * @param memoryLayout The memory layout for the new \c NICE::Image.
     * @return The new \c NICE::Image (ownership given away!)
     */
    inline NICE::Image*
    createGrayImage(const ice::Image& source,
                    bool invertImage = true,
                    NICE::GrayColorImageCommonImplementation::MemoryLayout memoryLayout
                    = NICE::GrayColorImageCommonImplementation::ippAlignment)
    {
        // auto_ptr for exception safety
        auto_ptr<Image>
        result(new Image(source->xsize, source->ysize, memoryLayout));

        for (int y = 0; y < source->ysize; y++)
        {
            Image::Pixel* cursor = result->getPixelPointerY(y);

            for (int x = 0; x < source->xsize; x++)
            {
                // FIXME GetVal_nocheck ?!
                *cursor = invert255(GetVal(source, x, y), invertImage);
                cursor++;
            }
        }

        return result.release();
    }

    /**
     * Copy an ice::Image to a NICE::Image
     * @param source The source image
     * @param dst The destination image
     * @param invertImage Invert the image? Note: ICE works with inverted images.
     *
     */
    inline void
    copyGrayImage(const ice::Image& source,
                  NICE::Image& dst,
                  bool invertImage = true)
    {
        dst.resize(source->xsize, source->ysize);
        for (int y = 0; y < source->ysize; y++)
        {
            Image::Pixel* cursor = dst.getPixelPointerY(y);
            for (int x = 0; x < source->xsize; x++)
            {
                *cursor = invert255(GetVal(source, x, y), invertImage);
                cursor++;
            }
        }
    }


    /**
     * Create a new \c ice::Image from an \c NICE::Image.
     * @param source The source image.
     * @param invertImage Invert the image? Note: ICE works with inverted images.
     * @return The new \c ice::Image (ownership given away!)
     */
    inline ice::Image createIceImage(const NICE::Image& source,
                                     bool invertImage = true)
    {
        ice::Image result = ice::NewImg(source.width(), source.height(), 255);

        for (int y = 0; y < source.height(); y++)
        {
            const Image::Pixel* cursor = source.getPixelPointerY(y);

            for (int x = 0; x < source.width(); x++)
            {
                // FIXME PutVal_nocheck ?!
                PutVal(result, x, y, invert255(*cursor, invertImage));
                cursor++;
            }
        }

        return result;
    }

    /**
     * Create a new \c NICE::ColorImage from an \c ice::ImageRGB.
     * @param source The source image.
     * @param invertImage Invert the image? Note: ICE works with inverted images.
     * @param memoryLayout The memory layout for the new \c NICE::ColorImage.
     * @return The new \c NICE::ColorImage (ownership given away!)
     */
    inline NICE::ColorImage*
    createColorImage(const ice::ImageRGB& source,
                     bool invertImage = true,
                     NICE::GrayColorImageCommonImplementation::MemoryLayout memoryLayout
                     = NICE::GrayColorImageCommonImplementation::ippAlignment)
    {
        // auto_ptr for exception safety
        auto_ptr<ColorImage>
        //result(new ColorImage(source.xsize(), source.ysize(), memoryLayout));
        result(new ColorImage(source.RedImage()->xsize,
                              source.RedImage()->ysize,
                              memoryLayout));

        for (int y = 0; y < source.RedImage()->ysize; y++)
        {
            ColorImage::Pixel* cursor = result->getPixelPointerY(y);

            for (int x = 0; x < source.RedImage()->xsize; x++)
            {
                // FIXME GetVal_nocheck ?!
                *cursor = invert255(GetVal(source.RedImage(), x, y), invertImage);
                cursor++;
                *cursor = invert255(GetVal(source.GreenImage(), x, y), invertImage);
                cursor++;
                *cursor = invert255(GetVal(source.BlueImage(), x, y), invertImage);
                cursor++;
            }
        }

        return result.release();
    }

    /**
     * Create a new \c ice::ImageRGB from an \c NICE::ColorImage.
     * @param source The source image.
     * @param invertImage Invert the image? Note: ICE works with inverted images.
     * @return The new \c ice::ImageRGB (ownership given away!)
     */
    inline ice::ImageRGB* createIceImageRGB(const NICE::ColorImage& source,
                                            bool invertImage = true)
    {
        ice::ImageRGB* result = new ice::ImageRGB(source.width(), source.height());

        for (int y = 0; y < source.height(); y++)
        {
            const Image::Pixel* cursor = source.getPixelPointerY(y);

            for (int x = 0; x < source.width(); x++)
            {
                PutVal(result->RedImage(), x, y, invert255(*cursor, invertImage));
                cursor++;
                PutVal(result->GreenImage(), x, y, invert255(*cursor, invertImage));
                cursor++;
                PutVal(result->BlueImage(), x, y, invert255(*cursor, invertImage));
                cursor++;
            }
        }

        return result;
    }

    /**
     * Create a new \c NICE::FloatImage from an \c ice::ImageD.
     * @param source The source FloatImage.
     * @param memoryLayout The memory layout for the new \c NICE::FloatImage.
     * @return The new \c NICE::FloatImage (ownership given away!)
     */
    inline NICE::FloatImage*
    createFloatImage(const ice::ImageD& source
                     )
    {
        // auto_ptr for exception safety
        auto_ptr<FloatImage>
        result(new FloatImage(source->xsize, source->ysize));

        for (int y = 0; y < source->ysize; y++)
        {
            FloatImage::Pixel* cursor = result->getPixelPointerY(y);

            for (int x = 0; x < source->xsize; x++)
            {
                // FIXME GetVal_nocheck ?!
                *cursor = GetValD(source, x, y);
                cursor++;
            }
        }

        return result.release();
    }

    /**
     * Copy an ice::ImageD to a NICE::FloatImage
     * @param source The source FloatImage
     * @param dst The destination FloatImage
     */
    inline void
    copyFloatImage(const ice::ImageD& source,
                   NICE::FloatImage& dst)
    {
        dst.resize(source->xsize, source->ysize);
        for (int y = 0; y < source->ysize; y++)
        {
            FloatImage::Pixel* cursor = dst.getPixelPointerY(y);
            for (int x = 0; x < source->xsize; x++)
            {
                *cursor = GetValD(source, x, y);
                cursor++;
            }
        }
    }


    /**
     * Create a new \c ice::ImageD from an \c NICE::FloatImage.
     * @param source The source FloatImage.
     * @return The new \c ice::ImageD (ownership given away!)
     */
    inline ice::ImageD createIceImageD(const NICE::FloatImage& source
                                      )
    {
        ice::ImageD result = ice::NewImgD(source.width(), source.height());

        for (int y = 0; y < source.height(); y++)
        {
            const FloatImage::Pixel* cursor = source.getPixelPointerY(y);

            for (int x = 0; x < source.width(); x++)
            {
                // FIXME PutVal_nocheck ?!
                PutValD(result, x, y, *cursor);
                cursor++;
            }
        }

        return result;
    }

}; // namespace

#endif /* _CONVERTICE_IMAGE_H */

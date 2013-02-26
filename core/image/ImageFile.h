/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
/*! \file ImageFile.h 
    \brief ImageFile class declaration
 */
/*****************************************************************************/
/*
 *  $Author: koch $
 *  $Date: 2009/08/03 15:23:49 $
 *  $Revision: 1.5 $
*/
/*****************************************************************************/
#ifndef _IMAGEFILE_IMAGE_H
#define _IMAGEFILE_IMAGE_H

#include <string>

#include <core/basics/types.h>

#ifdef NICE_USELIB_PNG
  #include <png.h>
#endif

namespace NICE {

template<class P> class GrayColorImageCommonImplementationT;
  
/**
 * This class is used to write images in various formats.
 */
class ImageFile
{
  public:
      typedef enum{FormatUnknown,
          PBM_IMAGE_TEXT, PGM_IMAGE_TEXT, PPM_IMAGE_TEXT,
          PBM_RAW, PGM_RAW, PPM_RAW, PAM_RAW,
          PNG, JPG} Format;

    class Header 
    {
      public:
        int width;
        int height;
        int bitdepth;
        int channel;

	Header() : width(-1), height(-1), 
		   bitdepth(-1), channel(-1) {};
    };

  private:
    std::string filename;
    ImageFile::Format fileformat;
    ImageFile::Header fileheader;
        int datapos;

  /**
  * Read specific PXM file header.
  */  
    void getPXMHeader(); 

#ifdef NICE_USELIB_PNG
  /**
  * Read specific PNG file header.
  */  
    void getPNGHeader(); 
#endif
 
#ifdef NICE_USELIB_JPG
 /**
  * Read specific JPG file header.
  */  
    void getJPGHeader(); 
#endif
  
  //! get fileformat specific header
  void getMyHeader();

  public:
  
  //! Default constructor
  ImageFile();

  //! Constructor with name and optional format specifier.
  /*! \param filename name of the file to write or read an image
   * \param type format of the image if none, file format will be automatically detected \see ImageFile::Format
   */
  ImageFile(const std::string &filename, Format type=FormatUnknown);

  //! Copy-Constructor
  /*! \param arg class to copy
  */
  ImageFile(const ImageFile& arg);

  //! Destructor of ImageFile
  virtual ~ImageFile();

  //! Assignment operator
  /*! \param ex class to copy
   *  \return a reference to this class 
   */
  ImageFile& operator=(const ImageFile& ex);

  /**
   * Get file name.
   * @return image filename
   */  
  const std::string &fileName() const { return filename; }

  /**
   * Get file format.
   * @return image filetype
   */  
  ImageFile::Format fileType() const {  return fileformat; }

  /**
   * Return if image file is a graylevel image. 
   */  
  bool isGray() const;

  /**
   * Get file header.
   * @return image header
   */  
  const ImageFile::Header &getHeader();
  uint height();
  uint width();

  /**
   * Get file comment.
   * @return image comment 
   */  
  std::string getComment();

  /**
   * Read image from file 
   * @param image GrayColorImageCommonImplementationT to read in
   */  
  template<class P>
  void reader(GrayColorImageCommonImplementationT<P> *image);

  /**
   * Write image to file 
   * @param image GrayColorImageCommonImplementationT to be written
   */  
  template<class P>
  void writer(const GrayColorImageCommonImplementationT<P> *image) const;

  /**
   * read pxm image from file
   * @param image GrayColorImageCommonImplementationT to read in
   */  
  template <class P>
  void readerPXM(GrayColorImageCommonImplementationT<P> *image);
  
  /**
   * write pxm image to file
   * @param image GrayColorImageCommonImplementationT to be written
   */  
  template <class P>
  void writerPXM(const GrayColorImageCommonImplementationT<P> *image) const;


#ifdef NICE_USELIB_PNG
  /**
   * Read png image from file 
   * @param image GrayColorImageCommonImplementationT to read in
   */  
  template<class P>
  void readerPNG(GrayColorImageCommonImplementationT<P> *image);

  /**
   * Write png image to file 
   * @param image GrayColorImageCommonImplementationT to be written
   */  
  template<class P>
  void writerPNG(const GrayColorImageCommonImplementationT<P> *image) const;
#endif


#ifdef NICE_USELIB_JPG
  /**
  * Read jpg image from file
  * @param image GrayColorImageCommonImplementationT to read in
  */  
  template<class P>
  void readerJPG(GrayColorImageCommonImplementationT<P> *image);
  
  /**
  * Write jpg image to file 
  * @param image GrayColorImageCommonImplementationT to be written
  * @param quality output qualtiy of the GrayColorImageCommonImplementationT to be written (default=100)
  */  
  template<class P> 
  void writerJPG(const GrayColorImageCommonImplementationT<P> *image, const int quality=100) const;
#endif

#ifdef NICE_USELIB_LIBMAGICK
  template<class P>
  void readerMagick(GrayColorImageCommonImplementationT<P> *image);
  
  template<class P>
  void writerMagick(const GrayColorImageCommonImplementationT<P> *image) const;
#endif

  /**
   * Check the format of a image file
   * @param filename full path and name of the file
   * @return image format
   */  
  static ImageFile::Format name2Format(const std::string &filename);
  
};

} // namespace NICE 

#include <core/image/GrayColorImageCommonImplementationT.h>

//#ifdef __GNUC__
  #include "core/image/ImageFile.tcc"
//#endif

#endif /* _IMAGEFILE_IMAGE_H */


/*****************************************************************************/
/*
 *  $Log: ImageFile.h,v $
 *  Revision 1.5  2009/08/03 15:23:49  koch
 *  deleted unnecessary .h
 *
 *  Revision 1.4  2009/07/22 12:12:01  rodner
 *  - added ImageMagick functionality
 *
 *  Revision 1.3  2009/06/10 08:06:34  rodner
 *  - getHeader support for png/jpg without system("identify ..");
 *
 *  Revision 1.2  2009/05/28 11:36:30  bajramov
 *  renamed a few things for consistency
 *
 *  Revision 1.1.1.1  2007/05/22 19:26:35  bajramov
 *  limun2
 *
 *  Revision 1.14  2007/02/01 15:58:18  bajramov
 *  improved interface for writing image files
 *  added format choice to ImageFileListWriter (to be renamed)
 *
 *  Revision 1.13  2007/01/19 12:27:15  bajramov
 *  moved include from h to tcc
 *
 *  Revision 1.12  2006/10/23 11:30:40  zimmermann
 *  * more general jpg io
 *
 *  Revision 1.11  2006/10/20 17:14:04  zimmermann
 *  * improved jpg io / test
 *
 *  Revision 1.10  2006/10/06 13:21:39  mattern
 *  .
 *
 *  Revision 1.9  2006/08/22 13:35:55  zimmermann
 *  *fixed a little error
 *
 *  Revision 1.8  2006/08/21 15:55:28  mattern
 *  - is gray implemented
 *
 *  Revision 1.7  2006/07/13 12:50:09  mattern
 *  - small fixes
 *
 *  Revision 1.6  2006/05/24 13:22:44  mattern
 *  - extern C fix
 *
 *  Revision 1.5  2006/05/24 13:03:43  mattern
 *  - jpg bugfix
 *  - unsigned signed errors fixed
 *
 *  Revision 1.4  2006/05/22 16:13:24  zimmermann
 *  * added jpeg io to ColorImage/Image/ImageFile
 *
 *  Revision 1.3  2006/03/02 21:11:33  mattern
 *  - bugfixes
 *
 *  Revision 1.2  2006/03/02 14:54:54  mattern
 *  - documenation improved
 *
 *  Revision 1.1  2006/03/02 14:50:33  mattern
 *  - ImageFile added
 *  - more template methods
 *  - ippwrapper improved
 *  - png support
 *
 */

#include <core/image/ImageFile.h>
#include <core/image/ImageT.h>
#include <core/image/ColorImageT.h>
#include <core/image/Convert.h>
#include <core/basics/stringutils.h>
#include <iostream>

#ifdef NICE_USELIB_LIBMAGICK
#include <Magick++.h>
#endif

#ifdef NICE_USELIB_JPG
// a little hack to handle the incompatible INT32 definitions in qt3 and libjpeg
#define INT32 INT32_ALTERNATIVE
extern "C" {
#include <jpeglib.h>
}
#undef INT32
#endif

namespace NICE {

template<class P> class ColorImageT;

#ifdef NICE_USELIB_LIBMAGICK
template<>
void ImageFile::readerMagick ( GrayColorImageCommonImplementationT<unsigned char> *image );

template<>
void ImageFile::writerMagick ( const GrayColorImageCommonImplementationT<unsigned char> *image ) const;
#endif


template<class P>
void ImageFile::reader ( GrayColorImageCommonImplementationT<P> *image )
{
  switch ( fileType() )
  {

#ifdef NICE_USELIB_PNG
    case ImageFile::PNG:
      readerPNG ( image );
      break;
#endif // NICE_USELIB_PNG

#ifdef NICE_USELIB_JPG
    case ImageFile::JPG:
      readerJPG ( image );
      break;
#endif // NICE_USELIB_JPG

    case ImageFile::PPM_RAW:
    case ImageFile::PGM_RAW:
      readerPXM ( image );
      break;
    default:
#ifdef NICE_USELIB_LIBMAGICK
      try {
        readerMagick ( image );
      } catch ( Magick::ErrorBlob & error ) {
        fthrow ( ImageException, std::string ( "Format not yet implemented. (libMagick++ error: " ) + std::string ( error.what() ) + std::string ( ")" ) );
      }
#else
      fthrow ( ImageException, "Format not yet implemented. (try using libMagick++)" );
#endif
  }
}

template<class P>
void ImageFile::writer ( const GrayColorImageCommonImplementationT<P> *image ) const
{
  switch ( fileType() )
  {
    case ImageFile::PNG:
#ifdef NICE_USELIB_PNG
      writerPNG ( image );
#else
#ifdef NICE_USELIB_LIBMAGICK
      try {
        writerMagick ( image );
      } catch ( Magick::Exception ) {
        fthrow ( ImageException, "Format not yet implemented." );
      }
#else
      fthrow ( ImageException, "Format not yet implemented. (try using libMagick)" );
#endif
#endif
      break;

    case ImageFile::JPG:
#ifdef NICE_USELIB_JPG
      writerJPG ( image );
#else
      fthrow ( ImageException, "JPEG format not supported." );
#endif
      break;

    case ImageFile::PPM_RAW:
      if ( image->channels() == 3 )
      {
        writerPXM ( image );
      }
      else
      {
        ColorImageT<P> *rgb = grayToRGB ( *reinterpret_cast<const ImageT<P>*> ( image ) );
        writerPXM ( rgb );
        delete rgb;
      }
      break;
    case ImageFile::PGM_RAW:
      if ( image->channels() == 1 )
        writerPXM ( image );
      else {
        ImageT<P> *gray = rgbToGray ( *reinterpret_cast<const ColorImageT<P>*> ( image ) );
        writerPXM ( gray );
        delete gray;
      }
      break;
    default:
#ifdef NICE_USELIB_LIBMAGICK
      try {
        writerMagick ( image );
      } catch ( Magick::Exception ) {
        fthrow ( ImageException, "Format not yet implemented." );
      }
#else
      fthrow ( ImageException, "Format not yet implemented. (try using libMagick)" );
#endif
  }
}

template <class P>
void ImageFile::readerPXM ( GrayColorImageCommonImplementationT<P> *image )
{
  using namespace std;
  // open the file
  ifstream file ( filename.c_str(), ios::binary );

  // error handling
  if ( !file.good() )
  {
    fthrow ( ImageException, string ( "readPXM: Cannot open " ) + filename );
  }
  if ( datapos == 0 )
    getPXMHeader();
  if ( fileheader.width != image->widthInline() || fileheader.height != image->heightInline() ) {
    image->resize ( fileheader.width, fileheader.height );
  }
  file.seekg ( datapos );

  int srcbytedepth = fileheader.bitdepth / 8;

  if ( srcbytedepth == image->bytedepth() ) { // same bit depth
    if ( fileformat == PPM_RAW || fileformat == PGM_RAW )
    {
      // simple case just write into image
      if ( fileheader.channel == image->channels() )
      {
        for ( int y = 0; y < fileheader.height; y++ )
        {
          file.read ( reinterpret_cast<char*>
                      ( image->getPixelPointerY ( y ) ), fileheader.width*fileheader.channel*srcbytedepth );
        }
      }
      // it is a gray image but should be converted to a rgb image
      else if ( fileheader.channel == 1 )
      {
        for ( int y = 0; y < fileheader.height; y++ ) {
          P *line = new P[fileheader.width];
          file.read ( reinterpret_cast<char *> ( line ), fileheader.width );
          P *target = image->getPixelPointerY ( y );
          P *src = line;
          for ( int x = 0; x < fileheader.width; x++, src++ ) {
            for ( int i = 0;i < image->channels();i++, target++ )
              *target = *src;
		  delete [] line;
          }
        }
      }
      // it is a rgb image that should be converted to a gray image
      else if ( fileheader.channel == 3 && image->channels() == 1 )
      {
        ColorImageT<P> rgb ( fileheader.width, fileheader.height );
        for ( int y = 0; y < fileheader.height; y++ )
        {
          file.read ( reinterpret_cast<char*>
                      ( rgb.getPixelPointerY ( y ) ), fileheader.width*fileheader.channel*srcbytedepth );
        }
        rgbToGray ( rgb, dynamic_cast<ImageT<P> *> ( image ) );
      }
      else
      {
        fthrow ( ImageException, "Format (channels) not yet implemented." );
      }
    } else {
      fthrow ( ImageException, "Format not yet implemented." );
    }
  }
  // different bitdephs
  else
  {
    if ( fileformat == PPM_RAW || fileformat == PGM_RAW ) {
      if ( fileheader.channel == 1 || ( fileheader.channel == 3 && image->channels() == 3 ) ) { // have to cast
        for ( int y = 0; y < fileheader.height; y++ ) {
          Ipp8u *line = new Ipp8u[fileheader.width*fileheader.channel*srcbytedepth];
          file.read ( reinterpret_cast<char *> ( line ), fileheader.width*fileheader.channel*srcbytedepth );
          P *target = image->getPixelPointerY ( y );
          Ipp8u *src = line;
          if ( srcbytedepth == 1 ) {
            for ( int x = 0; x < fileheader.width; x++ ) {
              for ( int i = 0;i < fileheader.channel;i++, src++, target++ )
                *target = static_cast<P> ( *src );
            }
          } else {
            for ( int x = 0; x < fileheader.width; x++ ) {
              for ( int i = 0;i < fileheader.channel;i++, src += srcbytedepth, target++ )
                * target = static_cast<P> ( *reinterpret_cast<Ipp16u *> ( src ) );
            }
          }
		  delete [] line;
        }
      } else if ( fileheader.channel == 3 && image->channels() == 1 ) { // have to cast and to convert
        ColorImageT<P> rgb ( fileheader.width, fileheader.height );
        for ( int y = 0; y < fileheader.height; y++ ) {
          Ipp8u *line = new Ipp8u[fileheader.width*fileheader.channel*srcbytedepth];
          file.read ( reinterpret_cast<char *> ( line ), fileheader.width*fileheader.channel*srcbytedepth );
          P *target = rgb.getPixelPointerY ( y );
          Ipp8u *src = line;
          if ( srcbytedepth == 1 ) {
            for ( int x = 0; x < fileheader.width; x++ ) {
              for ( int i = 0;i < fileheader.channel;i++, src++, target++ )
                *target = static_cast<P> ( *src );
            }
          } else {
            for ( int x = 0; x < fileheader.width; x++ ) {
              for ( int i = 0;i < fileheader.channel;i++, src += srcbytedepth, target++ )
                * target = static_cast<P> ( *reinterpret_cast<Ipp16u *> ( src ) );
            }
          }
		  delete [] line;
        }
        rgbToGray ( rgb, dynamic_cast<ImageT<P> *> ( image ) );
      } else {
        fthrow ( ImageException, "Format (channels) not yet implemented." );
      }
    } else {
      fthrow ( ImageException, "Format not yet implemented." );
    }
  }
}

#ifdef NICE_USELIB_LIBMAGICK
template<class P>
void ImageFile::readerMagick ( GrayColorImageCommonImplementationT<P> *image )
{
  fthrow ( ImageException, "Format not yet implemented (only available for standard images)." );
}

template<class P>
void ImageFile::writerMagick ( const GrayColorImageCommonImplementationT<P> *image ) const
{
  fthrow ( ImageException, "Format not yet implemented (only available for standard images)." );
}
#endif


template <class P>
void ImageFile::writerPXM ( const GrayColorImageCommonImplementationT<P> *image ) const {
  using namespace std;
  ofstream file ( filename.c_str(), ios::binary );
  if ( image->channels() == 1 )
    file << "P5" << endl;
  else if ( image->channels() == 3 )
    file << "P6" << endl;
  else {
    string msg = "Cannot write a ";
    msg += itostr ( image->channels() );
    msg += "-channel format. This is not yet implemented.";
    fthrow ( ImageException, msg );
  }
  file << image->widthInline() << " " << image->heightInline() << endl;
  file << static_cast<int> ( std::pow ( 2.0, image->bitdepth() ) - 1 ) << endl;
  for ( int y = 0; y < image->heightInline(); y++ ) {
    file.write ( reinterpret_cast<const char *> ( image->getPixelPointerY ( y ) ), image->widthInline() *image->channels() *image->bytedepth() );
  }
  file.close();
}

#ifdef NICE_USELIB_PNG
template<class P>
void ImageFile::readerPNG ( GrayColorImageCommonImplementationT<P> *image )
{
  FILE* pFile;
  // open image file
  if ( ( pFile = fopen ( filename.c_str(), "rb" ) ) == NULL ) {
    fthrow ( ImageException, "ImageFile::readerPNG: Cannot open " + filename );
  }

  // read header
  const int headersize = 8; // 8 is the maximum size that can be checked
  png_byte header[headersize];
  fread ( header, 1, headersize, pFile );
  if ( png_sig_cmp ( header, 0, headersize ) ) {
    fclose ( pFile );
    fthrow ( ImageException, "Image is not a PNG file." );
  }
  /* initialize stuff */
  png_structp png_ptr = png_create_read_struct ( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
  if ( !png_ptr ) {
    fclose ( pFile );
    fthrow ( ImageException, "png_create_read_struct failed" );
  }
  png_infop info_ptr = png_create_info_struct ( png_ptr );
  if ( !info_ptr ) {
    fclose ( pFile );
    fthrow ( ImageException, "png_create_info_struct failed" );
  }
  if ( setjmp ( png_jmpbuf ( png_ptr ) ) ) {
    fclose ( pFile );
    fthrow ( ImageException, "Error during init_io" );
  }

  png_init_io ( png_ptr, pFile );
  png_set_sig_bytes ( png_ptr, headersize );
  png_read_info ( png_ptr, info_ptr );

  int width = info_ptr->width;
  int height = info_ptr->height;
  png_byte color_type = info_ptr->color_type;
  png_byte bit_depth = info_ptr->bit_depth;


  // resize image if necessary
  if ( width != image->widthInline() || height != image->heightInline() ) {
    image->resize ( width, height );
  }

  //int number_of_passes = png_set_interlace_handling(png_ptr);
  /** expand palette images to RGB, low-bit-depth grayscale images to 8 bits,
      transparency chunks to full alpha channel; strip 16-bit-per-sample
      images to 8 bits per sample; and convert grayscale to RGB[A] */

  if ( color_type == PNG_COLOR_TYPE_PALETTE )
    png_set_expand ( png_ptr );
  if ( color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8 )
    png_set_expand ( png_ptr );

  if ( png_get_valid ( png_ptr, info_ptr, PNG_INFO_tRNS ) )
    png_set_expand ( png_ptr );
  if ( image->bitdepth() == 8 && bit_depth == 16 ) {
    png_set_strip_16 ( png_ptr );
  }
  if ( image->bitdepth() == 16 && bit_depth == 8 ) {
    fthrow ( ImageException, "convertion from 16 to 8 bit not implemented." );
  }
  switch ( image->channels() ) {
    case 1:
      if ( color_type == PNG_COLOR_TYPE_RGBA ||
           color_type == PNG_COLOR_TYPE_RGB ) {
        png_set_rgb_to_gray_fixed ( png_ptr, 1, -1, -1 );
      }
      if ( color_type == PNG_COLOR_TYPE_GRAY_ALPHA )
        png_set_strip_alpha ( png_ptr );
      break;
    case 3:
      if ( color_type == PNG_COLOR_TYPE_RGBA )
        png_set_strip_alpha ( png_ptr );
      if ( color_type == PNG_COLOR_TYPE_GRAY ||
           color_type == PNG_COLOR_TYPE_GRAY_ALPHA )
        png_set_gray_to_rgb ( png_ptr );
      break;
    case 4:
      break;
    default:
      fthrow ( ImageException, "No or invalid color image->channels()" );
      break;
  }
  png_read_update_info ( png_ptr, info_ptr );
  // read file
  if ( setjmp ( png_jmpbuf ( png_ptr ) ) ) {
    fclose ( pFile );
    fthrow ( ImageException, "Error during read_image" );
  }

  png_bytep * row_pointers = new png_bytep[height];
  for ( int y = 0; y < height; y++ )
    row_pointers[y] = reinterpret_cast<png_bytep> ( image->getPixelPointerY ( y ) );

  png_read_image ( png_ptr, row_pointers );
  delete [] row_pointers;
  png_destroy_read_struct ( &png_ptr, &info_ptr, NULL );
  fclose ( pFile );
}

template<>
void ImageFile::readerPNG ( GrayColorImageCommonImplementationT<Ipp32f> *image );

template<class P>
void ImageFile::writerPNG ( const GrayColorImageCommonImplementationT<P> *image ) const
{
  FILE *pfile;

  // open image file
  if ( ( pfile = fopen ( filename.c_str(), "wb" ) ) == NULL )
    fthrow ( ImageException, "ImageFile::writerPNG: Cannot write " + filename );

  png_structp png_ptr = png_create_write_struct ( PNG_LIBPNG_VER_STRING, png_voidp_NULL,
                        png_error_ptr_NULL, png_error_ptr_NULL );

  if ( !png_ptr ) {
    fclose ( pfile );
    fthrow ( ImageException, "png_create_write_struct failed" );
  }
  png_infop info_ptr = png_create_info_struct ( png_ptr );
  if ( !info_ptr ) {
    png_destroy_write_struct ( &png_ptr, ( png_infopp ) NULL );
    fclose ( pfile );
    fthrow ( ImageException, "png_create_info_struct failed" );
  }
  if ( setjmp ( png_jmpbuf ( png_ptr ) ) ) {
    png_destroy_write_struct ( &png_ptr, &info_ptr );
    fclose ( pfile );
    fthrow ( ImageException, "Error during write_image" );
  }
  png_init_io ( png_ptr, pfile );
  png_infop png_info_ptr = png_create_info_struct ( png_ptr );
  int bit_depth = image->bitdepth();
  int color_type;
  switch ( image->channels() ) {
    case 1:
      color_type = PNG_COLOR_TYPE_GRAY;
      break;
    case 2:
      color_type = PNG_COLOR_TYPE_GRAY_ALPHA;
      break;
    case 3:
      color_type = PNG_COLOR_TYPE_RGB;
      break;
    case 4:
      color_type = PNG_COLOR_TYPE_RGB_ALPHA;
      break;
    default:
      fthrow ( ImageException, "No or invalid color channels" );
      break;
  }
  int interlace_type = PNG_INTERLACE_NONE;
  png_set_IHDR ( png_ptr, png_info_ptr, image->widthInline(), image->heightInline(),
                 bit_depth, color_type, interlace_type, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT );
  /* turn on or off filtering, and/or choose
      specific filters.  You can use either a single
      PNG_FILTER_VALUE_NAME or the logical OR of one
      or more PNG_FILTER_NAME masks. */
  png_set_filter ( png_ptr, 0, PNG_FILTER_AVG );

  /* set the zlib compression level */
  png_set_compression_level ( png_ptr, Z_BEST_COMPRESSION );
  //png_set_compression_level(png_ptr, Z_DEFAULT_COMPRESSION);

  /* set other zlib parameters */
  /*    png_set_compression_mem_level(png_ptr, 8);
     png_set_compression_strategy(png_ptr, Z_DEFAULT_STRATEGY);
     png_set_compression_window_bits(png_ptr, 15);
     png_set_compression_buffer_size(png_ptr, 8192);
     png_set_compression_method(png_ptr, 8); */
  png_write_info ( png_ptr, png_info_ptr );
  for ( int y = 0; y < image->heightInline(); y++ ) {
    //const P *prow=image->getPixelPointerY(y);
    png_byte row[image->widthInline() *image->channels() *image->bytedepth() ];
    memcpy ( row, image->getPixelPointerY ( y ), image->widthInline() *image->channels() *image->bytedepth() );
    png_write_row ( png_ptr, row );
  }
  png_write_end ( png_ptr, info_ptr );
  png_destroy_write_struct ( &png_ptr, &info_ptr );
  fclose ( pfile );
}
#endif


#ifdef NICE_USELIB_JPG

template<class P>
void ImageFile::readerJPG ( GrayColorImageCommonImplementationT<P> *image )
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr         jerr;

  FILE* pFile;
  if ( ( pFile = fopen ( filename.c_str(), "rb" ) ) == NULL )
    fthrow ( ImageException, "ImageFile::readerJPG: Cannot open " + filename );

  cinfo.err = jpeg_std_error ( &jerr );
  jpeg_create_decompress ( &cinfo );
  jpeg_stdio_src ( &cinfo, pFile );
  jpeg_read_header ( &cinfo, FALSE );

  if ( image->channels() != 1 && image->channels() != 3 )
    fthrow ( ImageException, "Format not yet supported" );

  cinfo.out_color_space = image->channels() == 1 ? JCS_GRAYSCALE : JCS_RGB;

  jpeg_start_decompress ( &cinfo );
  int row_stride    = cinfo.output_width * cinfo.output_components;
  JSAMPARRAY buffer = ( *cinfo.mem->alloc_sarray ) ( ( j_common_ptr ) & cinfo, JPOOL_IMAGE, row_stride, 1 );

  // resize image if necessary
  int width  = cinfo.output_width;
  int height = cinfo.output_height;
  if ( width != image->widthInline() || height != image->heightInline() )
    image->resize ( width, height );

  // Bilddaten zeilenweise einlesen
  for ( int y = 0; y < height; ++y ) {
    if ( !jpeg_read_scanlines ( &cinfo, buffer, 1 ) )
      fthrow ( ImageException, "ImageFile::readerJPG: Some Error occured while reading " + filename );

    if ( sizeof ( P ) == sizeof ( Ipp8u ) )
      memcpy ( image->getPixelPointerY ( y ), buffer[0], width*image->channels() );
    else {
      const Ipp8u* pSrc = buffer[0];
      P* pDst           = image->getPixelPointerY ( y );

      for ( int x = 0; x < width*image->channels(); ++x, ++pSrc, ++pDst )
        if ( *pSrc < std::numeric_limits<P>::min() )
          *pDst = std::numeric_limits<P>::min();
        else if ( *pSrc > std::numeric_limits<P>::max() )
          *pDst = std::numeric_limits<P>::max();
        else
          *pDst = static_cast<Ipp8u> ( *pSrc );
    }
  }

  jpeg_finish_decompress ( &cinfo );
  jpeg_destroy_decompress ( &cinfo );
  fclose ( pFile );
}

template<class P>
void ImageFile::writerJPG ( const GrayColorImageCommonImplementationT<P> *image, const int quality ) const
{
  FILE *pfile;
  if ( ( pfile = fopen ( filename.c_str(), "wb" ) ) == NULL )
    fthrow ( ImageException, "ImageFile::writerJPG: Cannot write " + filename );

  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr       jerr;

  cinfo.err = jpeg_std_error ( &jerr );
  jpeg_create_compress ( &cinfo );
  jpeg_stdio_dest ( &cinfo, pfile );

  cinfo.image_width      = image->widthInline();
  cinfo.image_height     = image->heightInline();
  cinfo.input_components = image->channels();

  if ( image->channels() != 1 && image->channels() != 3 )
    fthrow ( ImageException, "Format not yet supported" );

  cinfo.in_color_space = image->channels() == 1 ? JCS_GRAYSCALE : JCS_RGB;

  jpeg_set_defaults ( &cinfo );
  jpeg_set_quality ( &cinfo, quality, TRUE );
  jpeg_start_compress ( &cinfo, TRUE );

  int width  = cinfo.image_width;
  int height = cinfo.image_height;

  JSAMPROW row_pointer[1];
  row_pointer[0] = new Ipp8u[width*image->channels() ];

  for ( int y = 0; y < height; ++y ) {
    if ( sizeof ( P ) == sizeof ( Ipp8u ) )
      memcpy ( row_pointer[0], image->getPixelPointerY ( y ), width*image->channels() );
    else {
      const P* pSrc = image->getPixelPointerY ( y );
      Ipp8u*   pDst = row_pointer[0];
      for ( int x = 0; x < width*image->channels(); ++x, ++pSrc, ++pDst )
        if ( *pSrc < std::numeric_limits<Ipp8u>::min() )
          *pDst = std::numeric_limits<Ipp8u>::min();
        else if ( *pSrc > std::numeric_limits<Ipp8u>::max() )
          *pDst = std::numeric_limits<Ipp8u>::max();
        else
          *pDst = static_cast<Ipp8u> ( *pSrc );
    }

    jpeg_write_scanlines ( &cinfo, row_pointer, 1 );
  }

  jpeg_finish_compress ( &cinfo );
  fclose ( pfile );
  jpeg_destroy_compress ( &cinfo );
}

#endif

}


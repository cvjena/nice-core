/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image/template for new NICE libraries
 * See file License for license information.
 */
/*****************************************************************************/
/*! \file ImageFile.cpp
    \brief ImageFile class definitions
 */
/*****************************************************************************/
/*
 *  $Author: rodner $
 *  $Date: 2010/06/04 08:53:52 $
 *  $Revision: 1.7 $
 */
/*****************************************************************************/

#include <sstream>
#include "core/image/ImageFile.h"
#include "core/image/Convert.h"

#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
    #include "iocompression/pipestream.h"
    #include "iocompression/magic.h"
#endif

#ifdef NICE_USELIB_LIBMAGICK
    #include <Magick++.h>
#endif

namespace NICE {

// Constructors:
// -------------
ImageFile::ImageFile(const std::string &filename, Format type)
{
	this->filename=filename;
	if(type==FormatUnknown)
	{
		fileformat=ImageFile::name2Format(filename);
	}
	else
	{
		fileformat=type;
	}
    	datapos=0;
}

ImageFile::ImageFile()
{
	filename = "";
  	fileformat = FormatUnknown;
  	datapos=0;
}

ImageFile::ImageFile(const ImageFile& ex)
{
	*this=ex;
}

// Operators:
// ----------
ImageFile& ImageFile::operator=(const ImageFile& ex)
{
  filename=ex.filename;
  fileformat=ex.fileformat;
  fileheader=ex.fileheader;
  datapos=ex.datapos;
  return *this;
}

// Destructor:
// -----------
ImageFile::~ImageFile()
{
}
#include <iostream>

#ifdef NICE_USELIB_PNG
template<>
void ImageFile::readerPNG(GrayColorImageCommonImplementationT<Ipp32f> *image)
{
  	switch(image->channels())
	{
	    case 1:
            {
                Image buffer;
                readerPNG(&buffer);
                if(image->widthInline()!=buffer.width() || image->heightInline()!=buffer.height()) {
                        image->resize(buffer.width(), buffer.height());
                }
                grayToFloat(buffer,dynamic_cast<ImageT<Ipp32f>* >(image));
                break;
            }
	    case 3:
            {
                ColorImage buffer;
                readerPNG(&buffer);
                if(image->widthInline()!=buffer.width() || image->heightInline()!=buffer.height()) {
                        image->resize(buffer.width(), buffer.height());
                }
                convertBitDepth(buffer,dynamic_cast<ColorImageT<Ipp32f>* >(image));
                break;
            }
	    default: fthrow(ImageException,"No or invalid color image->channels()");
		break;
  }
}
#endif //NICE_USELIB_PNG

#ifdef NICE_USELIB_LIBMAGICK
    template<>
    void ImageFile::readerMagick(GrayColorImageCommonImplementationT<unsigned char> *image)
    {
		Magick::Image magick_image;
		try {
        	magick_image.read ( filename );
		} catch ( Magick::Warning &error) {
			std::cerr << "libMagick++ warning: " << error.what() << std::endl;
		}
	// FIXME: maybe we should provide the possibility to read images with arbitary memory alignment
        if(image->widthInline()!=(int)magick_image.baseColumns() || image->heightInline()!=(int)magick_image.baseRows()
		    || image->getMemoryLayout() != GrayColorImageCommonImplementation::noAlignment )
		    image->resize ( magick_image.baseColumns(), magick_image.baseRows(), GrayColorImageCommonImplementation::noAlignment );

	if ( image->channels() == 1 ) {
	    // gray value
   	    magick_image.type( Magick::GrayscaleType );
	    magick_image.write ( 0, 0, magick_image.baseColumns(), magick_image.baseRows(),
		    "R", Magick::CharPixel, image->getPixelPointer() );

	} else { // rgb image
	    magick_image.write ( 0, 0, magick_image.baseColumns(), magick_image.baseRows(),
		    "RGB", Magick::CharPixel, image->getPixelPointer() );
	}
	
    }

template<>
void ImageFile::writerMagick(const GrayColorImageCommonImplementationT<unsigned char> *image) const
{
  if ( image->channels() == 1 ) // gray image
  {
      Magick::Image magick_image;
    // checking whether we have not a simple aligned image (block in memory)
    if ( image->rowStepsize() != image->width() )
    {
      // this means that we have a sub image or an IPP image
      // (i.e. some pixels are skipped in each row)
      // The Blob interface of ImageMagick is not flexible enough to handle this case
      //
      // Solution: we have to copy the image :(
      // We do this by creating an empty NICE image
      ImageT<unsigned char> image_noalignment;
      // Setting the memory alignment and copying from image
      image_noalignment.copyFrom ( *image, GrayColorImageCommonImplementation::noAlignment );
      // and doing the conversion to a Magick image
      // the alternative would be to directly copy from image to magick_image without memory
      // operations, but this could be slower
      Magick::Blob blob ( image_noalignment.getPixelPointer(), image_noalignment.width()*image_noalignment.height() );
        magick_image.magick ("GRAY");
            magick_image.read ( blob, Magick::Geometry ( image_noalignment.width(), image_noalignment.height() ), 8 );
        magick_image.write ( filename );
    }
    else
    {
        Magick::Blob blob ( image->getPixelPointer(), image->width()*image->height() );
        
        magick_image.magick ("GRAY");
        magick_image.read ( blob, Magick::Geometry ( image->width(), image->height() ), 8 );
        
        magick_image.write ( filename );
    }
  }
  else // color image
  {
    // see above, the same problems occur for RGB images
    if ( image->rowStepsize() != image->width() )
    {
      ColorImageT<unsigned char> image_noalignment;
      
      image_noalignment.copyFrom ( *image, GrayColorImageCommonImplementation::noAlignment );
      Magick::Image magick_image ( image_noalignment.width(), image_noalignment.height(),
        "RGB", Magick::CharPixel, image_noalignment.getPixelPointer() );
      
      std::string pngEnding ( ".png" );
      // do we currently want to write a png file?
      // if so, adapt writing parameters accordingly 
      //
      // needed for compatibility with png writer
      if ( filename.compare( filename.length() - pngEnding.length(), pngEnding.length(), pngEnding) == 0)
      {
        magick_image.defineValue( "png", "bit-depth", "8");
        magick_image.defineValue( "png", "format", "png8");
      }
      
      magick_image.write ( filename );

    }
    else
    {
      // we do not need the Blob definition here (somehow strange)
      Magick::Image magick_image ( image->width(), image->height(),
      "RGB", Magick::CharPixel, image->getPixelPointer() );
        
      std::string pngEnding ( ".png" );
      // do we currently want to write a png file?
      // if so, adapt writing parameters accordingly 
      //
      // needed for compatibility with png writer
      if ( filename.compare( filename.length() - pngEnding.length(), pngEnding.length(), pngEnding) == 0)
      {
        magick_image.defineValue( "png", "bit-depth", "8");
        magick_image.defineValue( "png", "format", "png8");
      }
      
      magick_image.write ( filename );
    }
  }
}
#endif

ImageFile::Format ImageFile::name2Format(const std::string &filename)
{
    std::string magic;

	#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
		magic=magicString(filename);
		if(magic!="ERROR")
		{
			if(magic=="Netpbm PGM \"rawbits\" image data")
				return ImageFile::PGM_RAW;
			if(magic=="Netpbm PPM \"rawbits\" image data")
				return ImageFile::PPM_RAW;
			if(magic=="PNG image data")
				return ImageFile::PNG;
			if(magic=="JPG image data")
				return ImageFile::JPG;
		};
	#endif

		int pos=filename.find_last_of('.');
		magic=filename.substr(pos);
		if(magic==".pgm" || magic==".PGM")
				return ImageFile::PGM_RAW;
		if(magic==".ppm" || magic==".PPM")
				return ImageFile::PPM_RAW;
		if(magic==".png" || magic==".PNG")
				return ImageFile::PNG;
		if(magic==".jpg" || magic==".JPG")
				return ImageFile::JPG;
		return ImageFile::FormatUnknown;
}

std::string ImageFile::getComment()
{
	if(fileformat==FormatUnknown) {
		fileformat=ImageFile::name2Format(filename);
	}
    std::string comment="";
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
	std::string cmdstring="identify -format \"\%c\" ";
    cmdstring+=filename;
    ipipestream cmd(cmdstring.c_str());
    while(!cmd.eof()) {
        std::string line;
        getline(cmd,line);
        comment += line;
    }
#endif
  return comment;
}

bool ImageFile::isGray() const
{
#ifdef NICE_USELIB_LIMUN_IOCOMPRESSION
	std::string cmdstring="identify -ping ";
    cmdstring+=filename;
    cmdstring+= "| cut -d' ' -f 4";
    ipipestream cmd(cmdstring.c_str());
    while(!cmd.eof()) {
        std::string line;
        getline(cmd,line);
        if(line=="PseudoClass")
            return true;
    }
#endif
    return false;
}

uint ImageFile::width()
{
    if ( fileheader.width < 0 ) 
	getMyHeader();

    if ( fileheader.width < 0 )
	fthrow(Exception, "Negative image width found in file header.");
    
    return (uint)fileheader.width;
}

uint ImageFile::height()
{
    if ( fileheader.height < 0 ) 
	getMyHeader();
    if ( fileheader.height < 0 )
	fthrow(Exception, "Negative image width found in file header.");
    
    return (uint)fileheader.height;
}

const ImageFile::Header &ImageFile::getHeader()
{
    getMyHeader();
    return fileheader;
}

void ImageFile::getMyHeader()
{
    if(fileformat==FormatUnknown) {
	    fileformat=ImageFile::name2Format(filename);
    }
    if(static_cast<int>(fileformat)>0 && static_cast<int>(fileformat)<8) {
	    getPXMHeader();
#ifdef NICE_USELIB_PNG
    } else if ( fileformat == ImageFile::PNG ) {
	    getPNGHeader();
#endif
#ifdef NICE_USELIB_JPG
    } else if ( fileformat == ImageFile::JPG ) {
	    getJPGHeader();
#endif
    } else {
#ifdef NICE_USELIB_LIBMAGICK
	    MagickCore::ImageInfo *image_info=CloneImageInfo((MagickCore::ImageInfo *) NULL);

	    strcpy(image_info->filename, filename.c_str());
	    image_info->ping=MagickCore::MagickBooleanType(1);
	    
	    MagickCore::ExceptionInfo exc_info;
	    GetExceptionInfo(&exc_info);
	    
	    MagickCore::Image *image=MagickCore::PingImage(image_info, &exc_info);
	    
	    fileheader.width = image->columns;
	    fileheader.height = image->rows;
	    MagickCore::DestroyImage(image);
	    MagickCore::DestroyImageInfo(image_info);
#else
	    fthrow(ImageException,"Not implemented without Libmagick");
#endif
	}
}

void ImageFile::getPXMHeader() {
  using namespace std;
  ifstream file(filename.c_str(), ios::binary);

  // error handling
  if(!file.good()) {
    fthrow(ImageException,string("getPXMHeader: Cannot open ") + filename);
  }
  char val;
  file.get(val);
  if(val!='P') {
      file.putback(val);
      fileformat=ImageFile::FormatUnknown;
  }
  file.get(val);
  if(val>'0' && val<'8') {
      fileformat=static_cast<ImageFile::Format>(val-'0');
  }
  if(fileformat==PPM_IMAGE_TEXT || fileformat==PPM_RAW)
      fileheader.channel=3;
  else
      fileheader.channel=1;

  int values=3; // fileheader values
  if(fileformat==PBM_IMAGE_TEXT || fileformat==PBM_RAW) {
      values=2;
      fileheader.bitdepth=1;
  }

  int status=0;
  int i=0, num=0;
  const int bsize = 1024;
  char buffer[bsize];
  while (file.good()&&num<values) {
     file.get(val);
     if(val=='#') { // omit comment
         while (file.good() && val!='\n') {
             file.get(val);
         }
         continue;
     }
     if(val>='0'&& val<='9') {
         status=1;
         buffer[i++]=val;
     } else if(status==1) {
         num++;
         buffer[i++]=' ';
         status=0;
     }
  }
  datapos = file.tellg();
  buffer[i]=0;
  std::stringstream stream;
  stream << buffer;
  int maxval;
  if(values==3)
    stream >> fileheader.width >> fileheader.height >> maxval;
  else
    stream >> fileheader.width >> fileheader.height;
  if(maxval<256)
  	fileheader.bitdepth=8;
  else if (maxval<65536)
  	fileheader.bitdepth=16;
  else
    fileformat=ImageFile::FormatUnknown;
}

#ifdef NICE_USELIB_PNG
void ImageFile::getPNGHeader ()
{
  FILE* pFile;
  // open image file
  if ((pFile = fopen(filename.c_str(), "rb")) == NULL) {
  fthrow(ImageException,"ImageFile::getPNGHeader: Cannot open " + filename);
  }

  // read header
  const int headersize=8; // 8 is the maximum size that can be checked
  png_byte header[headersize];
  fread(header, 1, headersize, pFile);
  if (png_sig_cmp(header, 0, headersize)) {
  fclose(pFile);
  fthrow(ImageException,"Image is not a PNG file.");
  }
  /* initialize stuff */
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
  fclose(pFile);
  fthrow(ImageException,"png_create_read_struct failed");
  }
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
  fclose(pFile);
  fthrow(ImageException,"png_create_info_struct failed");
  }
  if (setjmp(png_jmpbuf(png_ptr))) {
  fclose(pFile);
  fthrow(ImageException,"Error during init_io");
  }

  png_init_io(png_ptr, pFile);
  png_set_sig_bytes(png_ptr, headersize);
  png_read_info(png_ptr, info_ptr);

  fileheader.width = info_ptr->width;
  fileheader.height = info_ptr->height;
  fileheader.bitdepth = info_ptr->bit_depth;
  
  png_byte color_type = info_ptr->color_type;
  if ( color_type == PNG_COLOR_TYPE_GRAY ) 
    fileheader.channel = 1;
  else
    fileheader.channel = 3;
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  fclose(pFile);
}
#endif

#ifdef NICE_USELIB_JPG
void ImageFile::getJPGHeader()
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr         jerr;

    FILE* pFile;
    if ((pFile = fopen(filename.c_str(), "rb")) == NULL)
	fthrow(ImageException,"ImageFile::readerJPG: Cannot open " + filename);

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, pFile);
    jpeg_read_header(&cinfo, FALSE);
    
    // this statement is important also to read
    // image width and height
    jpeg_start_decompress(&cinfo);

    fileheader.width  = cinfo.output_width;
    fileheader.height = cinfo.output_height;
    fileheader.channel = cinfo.out_color_components;
    fileheader.bitdepth = cinfo.num_components; 
    
    fclose(pFile);
}
#endif

} // namespace NICE

/*****************************************************************************/
/*
 *  $Log: ImageFile.cpp,v $
 *  Revision 1.7  2010/06/04 08:53:52  rodner
 *  - bugfixes
 *
 *  Revision 1.6  2009/11/30 12:25:50  rodner
 *  - ImageMagick warning / error issue
 *  - indent problem in SimpleSelector
 *
 *  Revision 1.5  2009/07/22 12:12:01  rodner
 *  - added ImageMagick functionality
 *
 *  Revision 1.4  2009/06/10 08:06:34  rodner
 *  - getHeader support for png/jpg without system("identify ..");
 *
 *  Revision 1.3  2009/06/09 14:02:32  rodner
 *  - bugfix: rect .cpp -> .tcc
 *
 *  Revision 1.2  2009/05/28 11:36:30  bajramov
 *  renamed a few things for consistency
 *
 *  Revision 1.1.1.1  2007/05/22 19:26:35  bajramov
 *  limun2
 *
 *  Revision 1.16  2006/10/23 11:30:40  zimmermann
 *  * more general jpg io
 *
 *  Revision 1.15  2006/10/20 17:14:04  zimmermann
 *  * improved jpg io / test
 *
 *  Revision 1.14  2006/10/06 13:21:39  mattern
 *  .
 *
 *  Revision 1.13  2006/08/22 15:59:32  zimmermann
 *  * added required #ifdef NICE_USELIB_PNG
 *
 *  Revision 1.12  2006/08/21 15:55:28  mattern
 *  - is gray implemented
 *
 *  Revision 1.11  2006/08/21 14:01:33  zimmermann
 *  *fixed some errors
 *
 *  Revision 1.10  2006/07/13 12:50:09  mattern
 *  - small fixes
 *
 *  Revision 1.9  2006/07/13 11:53:51  mattern
 *  - large bug fixes
 *
 *  Revision 1.8  2006/05/24 13:03:43  mattern
 *  - jpg bugfix
 *  - unsigned signed errors fixed
 *
 *  Revision 1.7  2006/05/22 16:13:24  zimmermann
 *  * added jpeg io to ColorImage/Image/ImageFile
 *
 *  Revision 1.6  2006/04/01 14:41:43  mattern
 *  - new copy mode
 *
 *  Revision 1.5  2006/03/31 22:26:35  mattern
 *  *** empty log message ***
 *
 *  Revision 1.4  2006/03/27 19:06:56  mattern
 *  .
 *
 *  Revision 1.3  2006/03/26 01:48:05  mattern
 *  .
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

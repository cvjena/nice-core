/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */


#include <core/image/ippwrapper.h>

#include <core/image/ColorImageT.h>
#include <core/image/ImageT.h>
#include <core/basics/tools.h>
#include <memory>

namespace NICE {

template<class P>
ColorImageT<P>& ColorImageT<P>::operator=(const ColorT<P> &color)
{
#ifdef NICE_USELIB_IPP
    IppiSize ippiSize = {this->width(), this->height() };
  ippiSet_C3R(color.color(), this->getPixelPointer(), this->getStepsize(),
                ippiSize);
#else
  Ipp8u* pos=reinterpret_cast<Ipp8u*>(this->getPixelPointer());
  P *row[this->height()];
    for(int y=0;y<this->height(); ++y) {
    row[y]=reinterpret_cast<P*>(pos);
    pos+=this->getStepsize();
  }
    P *p;
    for(int y=0;y<this->height(); ++y) {
        p=row[y];
        for(int x=0;x<this->width(); ++x) {
            for(int chan=0;chan<3; ++chan,p++) {
          *p=color[chan];
        }
        }
  }
#endif
    return *this;
}

template<class P>
ColorImageT<P>& ColorImageT<P>::operator=(const P c[3])
{
#ifdef NICE_USELIB_IPP
  IppiSize ippiSize = {this->width(), this->height() };
  ippiSet_C3R(c, this->getPixelPointer(), this->getStepsize(),
              ippiSize);
#else
  Ipp8u* pos=reinterpret_cast<Ipp8u*>(this->getPixelPointer());
  P *row[this->height()];
  for(int y=0;y<this->height(); ++y) {
    row[y]=reinterpret_cast<P*>(pos);
    pos+=this->getStepsize();
  }
  P *p;
  for(int y=0;y<this->height(); ++y) {
    p=row[y];
    for(int x=0;x<this->width(); ++x) {
      for(int chan=0;chan<3; ++chan,p++) {
        *p=c[chan];
      }
    }
  }
#endif
  return *this;
}

template <class P>
ColorImageT<P>::ColorImageT(const int width, const int height,
                     const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout) :
		     ColorImageAccess() {
  this->m_columnStepsize = this->channels() * sizeof(P);
  this->allocPixel(width, height, _memoryLayout);
}

template <class P>
ColorImageT<P>::ColorImageT(const ColorImageT<P>& orig,
                     const GrayColorImageCommonImplementation::MemoryLayout copyMode) : GrayColorImageCommonImplementationT<P>(),
		     ColorImageAccess() {
  this->m_columnStepsize = this->channels() * sizeof(P);
  fromRaw(orig.getPixelPointer(), orig.width(), orig.height(),
          orig.getStepsize(), this->toCopyLayout(copyMode, orig));
}

template <class P>
ColorImageT<P>& ColorImageT<P>::operator=(const ColorImageT<P>& orig) {
  this->m_columnStepsize = this->channels() * sizeof(P);
  if(this->m_xsize == orig.width() && this->m_ysize == orig.height()) {
    doFromRaw(orig.getPixelPointer(), orig.getStepsize());
  } else {
    fromRaw(orig.getPixelPointer(), orig.width(), orig.height(),
          orig.getStepsize(), this->toCopyLayout(GrayColorImageCommonImplementation::originalAlignment, orig));
  }
  return *this;
}

template <class P>
ColorImageT<P>::ColorImageT(ColorImageT<P>& orig,
                            const GrayColorImageCommonImplementation::ShallowCopyMode shallow) {
  UNUSED_PARAMETER(shallow);
  this->setForeignPointer(orig.getPixelPointer(), orig.width(), orig.height(),
                    orig.getStepsize(), this->channels() * sizeof(P));
}

template <class P>
ColorImageT<P>::ColorImageT(const P* raw, const int width, const int height,
                            const int stepsize, const GrayColorImageCommonImplementation::MemoryLayout copyMode) {
  this->m_columnStepsize = this->channels() * sizeof(P);
  fromRaw(raw, width, height, stepsize, copyMode);
}

template <class P>
ColorImageT<P>::ColorImageT(P* raw, const int width, const int height,
                            const int stepsize,
                            const GrayColorImageCommonImplementation::ShallowCopyMode shallow)
{
  UNUSED_PARAMETER(shallow);
  this->setForeignPointer(raw, width, height, stepsize, this->channels() * sizeof(P));
}

template <class P>
ColorImageT<P>::ColorImageT(const P* raw, const int width, const int height,
                            const GrayColorImageCommonImplementation::MemoryLayout copyMode)
{
  this->m_columnStepsize = this->channels() * sizeof(P);
  fromRaw(raw, width, height, width * this->channels(), copyMode);
}

template <class P>
ColorImageT<P>::ColorImageT(P* raw,
                     const int width,
                     const int height,
                     const GrayColorImageCommonImplementation::ShallowCopyMode shallow) {
  UNUSED_PARAMETER(shallow);
  this->setForeignPointer(raw, width, height, width * this->channels(), this->channels() * sizeof(P));
}


template <class P>
ColorImageT<P>::ColorImageT() : GrayColorImageCommonImplementationT<P>() {
  this->m_columnStepsize = this->channels() * sizeof(P);
  this->allocPixel(0, 0, GrayColorImageCommonImplementation::ippAlignment);
}


template <class P>
ColorImageT<P>::ColorImageT(const std::string& fileName,
                     const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout)
{
  this->m_columnStepsize = this->channels() * sizeof(P);
  this->allocPixel(0, 0, _memoryLayout);
  this->read(ImageFile(fileName));
}




template <class P>
ColorImageT<P>::ColorImageT(const ColorImageT<P>& orig,
                            const GrayColorImageCommonImplementation::ShallowCopyMode shallow) {
  UNUSED_PARAMETER(shallow);
  setForeignPointerConst(orig.getPixelPointer(), orig.width(), orig.height(),
                         orig.getStepsize(), this->channels() * sizeof(P));
}

template <class P>
ColorImageT<P>::ColorImageT(const P* raw, const int width, const int height,
                            const int stepsize,
                            const GrayColorImageCommonImplementation::ShallowCopyMode shallow) {
  UNUSED_PARAMETER(shallow);
  this->setForeignPointerConst(raw, width, height, stepsize, this->channels() * sizeof(P));
}

template <class P>
ColorImageT<P>::ColorImageT(const ImageT<P>& src1,
                            const ImageT<P>& src2,
                            const ImageT<P>& src3)
{
    if( src1.width()!=src2.width() || src1.height()!=src2.height() ||
        src2.width()!=src3.width() || src2.height()!=src3.height() )
        fthrow(ImageException, "Source Images must have the same size.");

    this->m_columnStepsize = this->channels() * sizeof(P);
    this->resize(src1.width(), src1.height());
    const P *s1, *s2, *s3;
          P *pD;
    for(int y=0; y<this->height(); ++y)
    {
        s1 = src1.getPixelPointerY(y);
        s2 = src2.getPixelPointerY(y);
        s3 = src3.getPixelPointerY(y);
        pD = this->getPixelPointerY(y);
        for(int x=0; x<this->width(); ++x,++s1,++s2,++s3)
        {
            *pD++ = *s1;
            *pD++ = *s2;
            *pD++ = *s3;
        }
    }
}

// // // // //

template <class P>
void ColorImageT<P>::doAllocPixelNoAlignment() {
  this->m_columnStepsize = this->channels() * sizeof(P);
  this->m_rowStepsize = sizeof(P) * this->m_xsize * this->channels();
  this->setPixelPointer(new P[this->m_xsize * this->m_ysize * this->channels()]);
}

template <class P>
void ColorImageT<P>::doAllocPixelIPP() {
  // no IPP in generic implementation (-> specialization in ColorImageT.cpp)
  this->doAllocPixelNoAlignment();
  this->m_memoryLayout = GrayColorImageCommonImplementation::noAlignment;
}

#ifdef NICE_USELIB_IPP
    template <>
    void ColorImageT<Ipp8u>::doAllocPixelIPP();
    template <>
    void ColorImageT<Ipp16s>::doAllocPixelIPP();
    template <>
    void ColorImageT<Ipp32f>::doAllocPixelIPP();
#endif //NICE_USELIB_IPP

// // // // // Destruktor // // // // //

template <class P>
ColorImageT<P>::~ColorImageT<P>() {
}

template <class P>
void ColorImageT<P>::fromRaw(const P* raw,
                        const int width,
                        const int height,
                        const int stepsize,
                        const GrayColorImageCommonImplementation::MemoryLayout copyMode) {
  if (copyMode == GrayColorImageCommonImplementation::internal__foreignPointer || copyMode == GrayColorImageCommonImplementation::originalAlignment) {
    fthrow(ImageException,
      "internal__foreignPointer und originalAlignment not supported here");
  } else {
    this->allocPixel(width, height, copyMode);
    doFromRaw(raw, stepsize);
  }
}

template <class P>
void ColorImageT<P>::doFromRaw(const P* raw, const int stepsize) {
  // no IPP in generic implementation (-> specialization in ColorImageT.cpp)
  for (int y = 0; y < this->height(); y++) {
    const P* line = pointerToPixel3(raw, 0, y, stepsize);
    const P* lineTargetEnd = getPixelPointerYEnd(y);
    for (P* lineTarget = this->getPixelPointerY(y);
         lineTarget < lineTargetEnd; ) {
      *lineTarget++ = *line++;
      *lineTarget++ = *line++;
      *lineTarget++ = *line++;
    }
  }
}
#ifdef NICE_USELIB_IPP
template <>
void ColorImageT<Ipp8u>::doFromRaw(const Ipp8u* raw, const int stepsize);
template <>
void ColorImageT<Ipp16s>::doFromRaw(const Ipp16s* raw, const int stepsize);
template <>
void ColorImageT<Ipp32f>::doFromRaw(const Ipp32f* raw, const int stepsize);
#endif //NICE_USELIB_IPP

template <class P>
P ColorImageT<P>::getPixel(const int x, const int y, const int channel) const {
  if (this->isWithinImage(x, y) && isChannelLegal(channel)) {
    return getPixelQuick(x, y, channel);
  } else {
    fthrow(ImageException,
      "ColorImageT<P>::getPixel: (x,y) or channel out of range.");
  }
}

template <class P>
void ColorImageT<P>::setPixel(const int x,
                         const int y,
                         const int channel,
                         const P value) {
  if (this->isWithinImage(x, y) && isChannelLegal(channel)) {
    setPixelQuick(x, y, channel, value);
  } else {
    fthrow(ImageException,
      "ColorImageT<P>::setPixel: (x,y) or channel out of range.");
  }
}

template <class P>
void ColorImageT<P>::setPixel(const int x, const int y, const ColorT<P> &color) {
  if (this->isWithinImage(x, y)) {
    setPixelQuick(x, y, color);
  } else {
    fthrow(ImageException,
           "ColorImageT<P>::setPixel: (x,y) out of range.");
  }
}


template <class P>
void ColorImageT<P>::setPixelSave(const int x,
                             const int y,
                             const int channel,
                             const P value) {
  if (this->isWithinImage(x, y) && isChannelLegal(channel)) {
    setPixelQuick(x, y, channel, value);
  }
}

template <class P>
void ColorImageT<P>::setPixelSave(const Coord &coord, const ColorT<P> &color)
{
  if (this->isWithinImage(coord.x, coord.y)) {
    setPixelQuick(coord, color);
  }
}

template <class P>
    void ColorImageT<P>::setPixelSave(const int x, const int y, const ColorT<P> &color)
{
  if (this->isWithinImage(x, y)) {
    setPixelQuick(x, y, color);
  }
}

template <class P>
void ColorImageT<P>::setPixel(const int x,
                         const int y,
                         const P value0,
                         const P value1,
                         const P value2) {
  if (this->isWithinImage(x, y)) {
    setPixelQuick(x, y, value0, value1, value2);
  } else {
    fthrow(ImageException,
      "ColorImageT<P>::setPixel: (x,y) out of range.");
  }
}

template <class P>
void ColorImageT<P>::setPixelSave(const int x, const int y,
                                  const P value0, const P value1, const P value2)
{
    if (this->isWithinImage(x, y))
        setPixelQuick(x, y, value0, value1, value2);
}

template <class P>
void ColorImageT<P>::set(const P& value0, const P& value1, const P& value2)
{
    P value[3] = {value0, value1, value2};
    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiSet_C3R(value,
                                    this->getPixelPointer(), this->getStepsize(),
                                    makeROIFullImage(*this));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        P* pSrc;
        for(int y=0; y<this->height(); ++y) {
            pSrc = this->getPixelPointerY(y);
            for(int x=0; x<this->width(); ++x)
                for(int i=0; i<3; ++i)
                    *pSrc++ = value[i];
        }
    #endif // NICE_USELIB_IPP
}

template<class P>
void ColorImageT<P>::mirror(IppiAxis axis)
{
    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiMirror_C3IR(this->getPixelPointer(), this->getStepsize(),
                                        makeROIFullImage(*this), axis);

        if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));

    #else
        if(axis==ippAxsVertical)
            for(int y=0; y<this->height(); ++y)
                for(int x=0; x<this->width()/2; ++x)
                    for(int i=0; i<3; ++i)
                        std::swap((*this)(x,y,i), (*this)(this->width()-1-x,y,i));
        else if(axis==ippAxsHorizontal)
            for(int y=0; y<this->height()/2; ++y)
                for(int x=0; x<this->width(); ++x)
                    for(int i=0; i<3; ++i)
                        std::swap((*this)(x,y,i), (*this)(x,this->height()-1-y,i));
        else {
            this->mirror(ippAxsVertical);
            this->mirror(ippAxsHorizontal);
        }
    #endif // NICE_USELIB_IPP
}

template<class P>
void ColorImageT<P>::transpose()
{
    if(this->width()!=this->height())
        fthrow(ImageException,"Image size must be symetric.");

    #ifdef NICE_USELIB_IPP
        IppStatus ret = ippiTranspose_C3IR(this->getPixelPointer(),
                                           this->getStepsize(),
                                           makeROIFullImage(*this));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else
         for(int y=0; y<this->height(); ++y)
            for(int x=0; x<y; ++x)
                for(int i=0; i<3; ++i)
                    std::swap((*this)(x,y,i), (*this)(y,x,i));
    #endif
}

template <class P>
ColorImageT<P>* ColorImageT<P>::copyRect(const Rect& rect, ColorImageT<P>* dst)
{
    Rect roi           = clipRect(*this, rect);
    ColorImage* result = createResultBuffer(roi.width, roi.height, dst);

    #ifdef NICE_USELIB_IPP
        IppStatus ret         = ippiCopy_C3R(this->getPixelPointerXY(roi.left, roi.top),
                                             this->getStepsize(),
                                             result->getPixelPointer(),
                                             result->getStepsize(), makeROIRect(*this, roi));

        if(ret!=ippStsNoErr)
                fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP
        const P* pSrc;
        P*       pDst;
        for(int y=0; y<roi.height; ++y) {
            pSrc = this->getPixelPointerXY(roi.left, roi.top+y);
            pDst = result->getPixelPointerY(y);
            for(int x=0; x<roi.width*3; ++x,++pSrc,++pDst)
                *pDst = *pSrc;
        }
    #endif // NICE_USELIB_IPP

    return(result);
}

template <class P>
ImageT<P>* ColorImageT<P>::getChannel(const int channel, ImageT<P>* dst) const {

    if (channel >= this->channels()) {
        fthrow(ImageException, "channel number is invalid.");
    }

    ImageT<P>* result = createResultBuffer(this->width(), this->height(), dst);

    #ifdef NICE_USELIB_IPP

        IppStatus ret = ippiCopy_C3C1R(this->getPixelPointer()+channel,
                                       this->getStepsize(),
                                       result->getPixelPointer(),
                                       result->getStepsize(),
                                       makeROIFullImage(*this));

        if(ret!=ippStsNoErr)
            fthrow(ImageException, ippGetStatusString(ret));

    #else // NICE_USELIB_IPP

        const P *pSrc;
              P *pDst;
        for(int y=0; y<this->height(); ++y) {
            pSrc = this->getPixelPointerY(y) + channel;
            pDst = result->getPixelPointerY(y);
            for(int x=0; x<this->width(); ++x,++pDst,pSrc+=this->channels())
                *pDst = *pSrc;
        }

    #endif // NICE_USELIB_IPP

    return result;
}

// PGM
template <class P>
void ColorImageT<P>::readPPM(const char *ppmFileName,
                        const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout) {
 readPPM(std::string(ppmFileName), _memoryLayout);
}

template <class P>
void ColorImageT<P>::readPPM(const std::string& ppmFileName,
                        const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout) {
  // not in generic implementation (-> specialization in ColorImageT.cpp)
  fthrow(ImageException,
    "ColorImageT<P> readPPM currently supported for ColorImageT<Ipp8u> only.");
}
template <>
void ColorImageT<Ipp8u>::readPPM(const std::string& ppmFileName,
                            const GrayColorImageCommonImplementation::MemoryLayout _memoryLayout);

template <class P>
void ColorImageT<P>::writePPM(const char* ppmFileName) const {
  // not in generic implementation (-> specialization in ColorImageT.cpp)
  fthrow(ImageException,
    "ColorImageT<P> writePPM currently supported for ColorImageT<Ipp8u> only.");
}
template <>
void ColorImageT<Ipp8u>::writePPM(const char* ppmFileName) const;

template <class P>
void ColorImageT<P>::writePPM(const std::string& ppmFilename) const {
  writePPM(ppmFilename.c_str());
}

template<class P>
inline bool ColorImageT<P>::operator==(const ColorImageT<P>& g) const
{
  if (this->height() != g.height() || this->width() != g.width()) {
    fthrow(ImageException, "ColorImageT<P> width and height does not match");
  } else if (this->width() == 0 || this->height() == 0) {
    return true;
  }

  const P *pSrc1,*pSrc2;
  for (int i = 0; i < this->height(); ++i) {
    pSrc1 = this->getPixelPointerY(i);
    pSrc2 = g.getPixelPointerY(i);

    for (int j = 0; j < this->width()*3; ++j,++pSrc1,++pSrc2)
      if(*pSrc1!=*pSrc2)
        return false;
  }

  return true;
}

template<class P>
inline bool ColorImageT<P>::operator!=(const ColorImageT<P>& g) const {
    return !(this->operator==(g));
}

template<class P>
inline bool ColorImageT<P>::operator==(const ColorT<P> &color) const
{
  P* pSrc;
  for (int i = 0; i < this->height(); ++i) {
    pSrc = this->getPixelPointerY(i);

    for (int j = 0; j < this->width(); ++j)
      for (int c = 0; c < 3; ++c,++pSrc)
        if(*pSrc!=color[c])
          return false;
  }

  return true;
}

template<class P>
inline bool ColorImageT<P>::operator!=(const ColorT<P> &color) const {
    return !(this->operator==(color));
}

template <class P>
void ColorImageT<P>::draw(Drawable<P> &drawable)
{
    drawable.draw(*this);
}

template <class P>
template <typename DrawableIterator>
void ColorImageT<P>::drawIter(const DrawableIterator begin,
                              const DrawableIterator end)
{
    DrawableIterator it=begin;
    for(;it!=end;it++)
        it->draw(*this);
}

template <class P>
template <typename DrawableIterator>
void ColorImageT<P>::drawIter(const DrawableIterator begin, size_t number)
{
    DrawableIterator it=begin;
    for(uint i=0;i<number;i++,it++)
        it->draw(*this);
}

template <class P>
void ColorImageT<P>::draw(Drawable<P> &drawable, const ColorT<P>& color)
{
    drawable.draw(*this, color);
}

template <class P>
template <typename DrawableIterator>
void ColorImageT<P>::drawIter(const DrawableIterator begin,
                              const DrawableIterator end,
                              const ColorT<P>& color)
{
    DrawableIterator it=begin;
    for(;it!=end;it++)
        it->draw(*this, color);
}

template <class P>
template <typename DrawableIterator>
void ColorImageT<P>::drawIter(const DrawableIterator begin, size_t number,
                              const ColorT<P>& color)
{
    DrawableIterator it=begin;
    for(uint i=0;i<number;i++,it++)
        it->draw(*this, color);
}


} // namespace

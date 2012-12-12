/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#ifndef LIMUN_HISTOGRAM_H
#define LIMUN_HISTOGRAM_H


#include "core/image/ippwrapper.h"

#include "core/image/RectT.h"
#include "core/image/ImageT.h"
#include "core/image/ColorImageT.h"

#include "core/vector/VectorT.h"

namespace NICE {

/**
 * A class for histograms
 */
class Histogram {

public:
    //! STL-like typedef for type of elements
    typedef Ipp32s                  value_type;
    //! STL-like typedef for element reference
    typedef value_type&             reference;
    //! STL-like typedef for const element reference
    typedef const value_type&       const_reference;
    //! STL-like typedef for iterator
    typedef value_type*             iterator;
    //! STL-like typedef for const iterator
    typedef const value_type*       const_iterator;

    /**
    * @name Constructors, factory methods and destructor
    * \{
    */

    /**
    * \}
    * @name Histogram
    * \{
    */

    /**
    * Default constructor.
    */
    Histogram();

    /**
    * Create a empty histogram with \c bins bins.
    * @param bins number of histogram bins
    */
    Histogram(const Ipp32s& bins);

    /**
    * Create a empty histogram with values in the area of \c min to \c max with \c bins equal bins.
    * @param min  lower boundary (included)
    * @param max  upper boundary (not included)
    * @param bins number of histogram bins (if negativ, (\c max - \c min) bins will be used)
    */
    Histogram(const Ipp32s& min, const Ipp32s& max, const Ipp32s& bins=-1);

    /**
    * Calculate a histogram from the source gray image \c src with \c bins equal bins.<br>
    * Only values in the area of \c min to \c max are taken into account during calculation.
    * @param src  source image
    * @param min  lower boundary (included)
    * @param max  upper boundary (not included)
    * @param bins number of histogram bins (if negativ, (\c max - \c min) bins will be used)
    */
    Histogram(const Image& src, const Ipp32s& min, const Ipp32s& max, const Ipp32s& bins=-1);

    /**
    * Calculate a histogram from target \c rect of the source gray image \c src with \c bins equal bins.<br>
    * Only values in the area of \c min to \c max are taken into account during calculation.
    * @param src  source image
    * @param min  lower boundary (included)
    * @param max  upper boundary (not included)
    * @param rect target rect
    * @param bins number of histogram bins (if negativ, (\c max - \c min) bins will be used)
    */
    Histogram(const Image& src, const Ipp32s& min, const Ipp32s& max,
              const Rect& rect, const Ipp32s& bins=-1);

    /**
    * Calculate a histogram from the source color image \c src with \c bins equal bins.<br>
    * The resulting histogram is of size = 3*\c bins .<br>
    * Only values in the area of \c min to \c max are taken into account during calculation.
    * @param src  source image
    * @param min  lower boundary (included)
    * @param max  upper boundary (not included)
    * @param bins number of histogram bins (if negativ, (\c max - \c min) bins will be used)
    */
    Histogram(const ColorImage& src, const Ipp32s& min, const Ipp32s& max, const Ipp32s& bins=-1);

    /**
    * Destructor.
    */
    virtual ~Histogram() {
        delete _data;
    }

    /**
    * \}
    * @name Combined Color Histogram
    * \{
    */

    /**
    * Calculate a combined histogram for the source color image \c src with \c bins equal bins per colorchannel.<br>
    * The resulting histogram is of size (\c bins^2 + \c bins ) if \c noLum == true or<br>
    * (\c bins^3 + \c bins^2 + \c bins) if \c noLum == false
    * @param src   source color image
    * @param min   lower boundary (included)
    * @param max   upper boundary (not included)
    * @param bins  number of histogram bins (if negativ, (\c max - \c min) bins will be used)
    * @param noLum specifies if the first color channel will be ignored, set to \b true to ignore
    */
    Histogram(const ColorImage& src, const Ipp32s& min, const Ipp32s& max,
              const Ipp32s& bins, const bool noLum);

    /**
    * If a combined binned histogram was created, reproject will retrieve the index
    * of the color (\c c1 , \c c2 , \c c3 ) .<br>
    * If the histogram was created with \c noLum == \b true, value \c c1 will be ignored.
    * @param c1 value for the first color channel
    * @param c2 value for the second color channel
    * @param c3 value for the third color channel
    * @return Ipp32u
    * @throws ImageException if no combined histogram is used
    */
    Ipp32u reproject(const Ipp8u& c1, const Ipp8u& c2, const Ipp8u& c3);

    /**
    * \}
    * @name Access Data
    * \{
    */

    /**
    * Access to elements.
    * @param  i Index
    * @return reference
    */
    inline reference operator[](const ptrdiff_t i) {
        return (*_data)[i];
    }

    /**
    * Read access to elements.
    * @param  i Index
    * @return const_reference
    */
    inline const_reference operator[](const ptrdiff_t i) const {
        return (*_data)[i];
    }

    /**
    * Access to range checked elements.
    * @param  i Index
    * @return reference
    */
    inline reference operator()(const ptrdiff_t i) {
        if(isWithin(i))
            return (*_data)[i];
        else
            fthrow(ImageException, "Index out of range.");
    }

    /**
    * Range checked access to histogram bins.
    * @param  i Index
    * @return const_reference
    * @throws ImageException if \c i is out of range (\b minIndex() to \b maxIndex() ).
    */
    inline const_reference operator()(const ptrdiff_t i) const {
        if(isWithin(i))
            return (*_data)[i];
        else
            fthrow(ImageException, "Index out of range.");
    }

    /**
    * Get an iterator pointing to the first element.
    * @return iterator
    */
    inline iterator begin() {
        return _data->begin();
    }

    /**
    * Get a const_iterator pointing to the first element.
    * @return const_iterator
    */
    inline const_iterator begin() const {
        return _data->begin();
    }

    /**
    * Get an iterator pointing beyond the last element.
    * @return iterator
    */
    inline iterator end() {
        return _data->end();
    }

    /**
    * Get an iterator pointing beyond the last element.
    * @return const_iterator
    */
    inline const_iterator end() const {
        return _data->end();
    }

    /**
    * Get a data pointer to the internal memory.
    * @return iterator
    */
    inline iterator getDataPointer() {
        return _data->getDataPointer();
    }

    /**
    * Get a const pointer to the internal memory.
    */
    inline const_iterator getDataPointer() const {
        return _data->getDataPointer();
    }

    /**
    * Assign \c v to all bins of the histogram.
    * @param v value to assign
    */
    inline void set(const value_type v) {
        *_data = v;
    }

    /**
    * Increase bin \c index by 1.
    */
    inline void increaseBin(const value_type index) {
        (*_data)[index]++;
    }

    /**
    * \}
    * @name Operators
    * \{
    */

    /**
    * Copy data from \c v to \c this.
    * @param v new data
    * @return \c *this
    */
    inline Histogram& operator=(const Histogram& v);

    /**
    * Set all bins to value \c element
    * @param element new value of all bins
    */
    inline Histogram& operator=(const_reference element);

    /**
    * \}
    * @name Tools
    * \{
    */

    /**
    * Check if the value is within the border \b minBorder() to \b maxBorder() .
    * @return true if \c val is within the border from \b minBorder() to \b maxBorder() .
    */
    bool isWithin(const ptrdiff_t i) const {
        return i>=_min && i<_max;
    }

    /**
    * Calculate the sum of all bins.
    * @return value_type
    */
    value_type sum() const;

    /**
    * \}
    * @name Basic Properties
    * \{
    */

    /**
    * Return the maximum value of all bins.
    * @return value_type
    */
    value_type min() const {
        return _data->Min();
    }

    /**
    * Return the minimum value of all bins.
    * @return value_type
    */
    value_type max() const {
        return _data->Max();
    }

    /**
    * Return the index of the minimum value of all bins.
    * @return Ipp32u
    */
    Ipp32u minIndex() const;

    /**
    * Return the index of the maximum value of all bins.
    * @return Ipp32u
    */
    Ipp32u maxIndex() const;

    /**
    * Return the number of bins per channel
    * @return Ipp32u
    */
    Ipp32u bins() const {
        return _nobins;
    }

    /**
    * Return the number of color channels the histogram was created from
    * @return Ipp32u
    */
    Ipp32u channels() const {
        return _channels;
    }

    /**
    * Return the minimum border of the histogram value range.
    * @return Ipp32s
    */
    Ipp32s minBorder() const {
        return _min;
    }

    /**
    * Return the maximum border of the histogram value range.
    * @return Ipp32s
    */
    Ipp32s maxBorder() const {
        return _max;
    }

    /**
    * Return the size of the histogram.
    * @return Ipp32s
    */
    Ipp32u size() const {
        return _data->size();
    }

    /**
    * \}
    * @name Transformations
    * \{
    */

    /**
    * Calculate a cumulative histogram. 
    * @return Pointer to IntVector
    */
    IntVector* cumulative();

    /**
    * Calculate a normalized histogram.
    * @return Pointer to FloatVector
    */
    FloatVector* normalized();

    /**
    * \}
    * @name IO Functions
    * \{
    */

    /**
    * Read a histogram from a file \c filename .
    * @param filename source file where to read from
    * @return true if the histogram could be read, false if an error occoured
    */
    bool read(const std::string &filename);

    /**
    * Write a histogram to a file \c filename .
    * @param filename source file where to write the histogram
    * @return true if the histogram could be writed, false if an error occoured
    */
    bool write(const std::string &filename);

    /**
    * \}
    */

private:

    VectorT<value_type>* _data;
    Ipp32u               _channels, _nobins;
    Ipp32s               _min, _max;

    // needed for faster reprojection
    Ipp32u           _b[3];
    Ipp32u           _diff;

    // little helperfunction to init b
    void init_b() {
        _b[2] = _nobins;
        _b[1] = _nobins*_b[2];
        _b[0] = _nobins*_b[1];
    }
};





inline Histogram& Histogram::operator=(const Histogram& v) {
    _min      = v.min();
    _max      = v.max();
    _nobins   = v.bins();
    _channels = v.channels();
    _diff     = _max-_min;

    // delete old data
    if(_data==NULL)
        _data = new VectorT<value_type>(v.size());
    else
        if(_data->size()!=v.size())
            _data->resize(v.size());

    #ifdef NICE_USELIB_IPP
        ippsCopy(v.getDataPointer(), _data->getDataPointer(), _data->size());
    #else
        memcpy(_data->getDataPointer(), v.getDataPointer(), _data->size()*sizeof(value_type));
    #endif

    return *this;
}

inline Histogram& Histogram::operator=(const_reference element) {
    *_data = element;
    return *this;
}

/**
* @name Operators
* \{
*/

/**
* Add histograms \c a and \c b .
* @return Histogram
* @throws ImageException will be thrown if the size of \c a and \c b are not equal.
*/
inline const Histogram operator+(const Histogram& a, const Histogram& b)
{
    if(a.size()!=b.size())
        fthrow(ImageException,"Histogram size is not equal.");

    Histogram result(a.minBorder(), a.maxBorder(), a.bins());

    Histogram::iterator r       = result.begin();
    Histogram::const_iterator j = b.begin();
    for(Histogram::const_iterator i=a.begin(); i!=a.end(); ++i,++j,++r)
        *r = *i+*j;

    return result;
}

/**
* Add histogram \c a to \c this and overwrite \c this .
* @return Histogram
* @throws ImageException will be thrown if the size of \c a and \c b are not equal.
*/
inline Histogram& operator+=(Histogram& a, const Histogram& b)
{
    if(a.size()!=b.size())
        fthrow(ImageException,"Histogram size is not equal.");

    Histogram::const_iterator j = b.begin();
    for(Histogram::iterator i=a.begin(); i!=a.end(); ++i,++j)
        *i += *j;

    return a;
}

/**
* Compare \c a with \c b .
* @param  a source histogram
* @param  b histogram to compare with
* @return \b true if \c a and \c b are equal, \b false if not or if the size of \c a and \c b are not equal.
*/
inline bool operator==(const Histogram& a, const Histogram& b)
{
    if(a.size()!=b.size())
        return false;

    Histogram::const_iterator j = b.begin();
    for(Histogram::const_iterator i=a.begin(); i!=a.end(); ++i,++j)
        if(*i != *j)
            return false;

    return true;
}

/**
* Compare Histogram \c a with \c b .
* @param  a source histogram
* @param  b histogram to compare with
* @return true if \c a and \c b are not equal or if the size of a and b is not equal
*/
inline bool operator!=(const Histogram& a, const Histogram& b)
{
    if(a.size()!=b.size())
        return true;

    Histogram::const_iterator j = b.begin();
    for(Histogram::const_iterator i=a.begin(); i!=a.end(); ++i,++j)
        if(*i == *j)
            return false;

    return true;
}

/**
 * \} 
 */

} // namespace

#endif // LIMUN_HISTOGRAM_H

#ifndef FBASICS_CASTS_H
#define FBASICS_CASTS_H

#include <cmath>

namespace NICE {

/// round_to_nearest_cast: cast to the nearest value in the target domain
template<typename Target, typename Source> Target round_to_nearest_cast(Source x);


// Allg. round - functor
template<typename Target, typename Source>
struct roundToNearest
{
      static  Target cast(Source x) { return static_cast<Target>(x); }
};
                                                                                                                                                                     
// Part. spezialisiert
template<typename Source>
struct roundToNearest<long long, Source>
{
      static  long long cast(Source x) { return static_cast<long long>(floor(x+0.5)); }
};

template<typename Source>
struct roundToNearest<unsigned long long, Source>
{
      static unsigned long long cast(Source x) { return static_cast<unsigned long long>(x+0.5); }
};

template<typename Source>
struct roundToNearest<long, Source>
{
      static  long cast(Source x) { return static_cast<long>(floor(x+0.5)); }
};

template<typename Source>
struct roundToNearest<unsigned long, Source>
{
      static unsigned long cast(Source x) { return static_cast<unsigned long>(x+0.5); }
};

template<typename Source>
struct roundToNearest<int, Source>
{
      static  int cast(Source x) { return static_cast<int>(floor(x+0.5)); }
};

template<typename Source>
struct roundToNearest<unsigned int, Source>
{
      static unsigned int cast(Source x) { return static_cast<unsigned int>(x+0.5); }
};

template<typename Source>
struct roundToNearest<char, Source>
{
      static  char cast(Source x) { return static_cast<char>(floor(x+0.5)); }
};

template<typename Source>
struct roundToNearest<unsigned char, Source>
{
      static unsigned char cast(Source x) { return static_cast<unsigned char>(x+0.5); }
};
                                                                                                                                                                     
template<typename Target, typename Source> Target round_to_nearest_cast(Source x)
{
        return roundToNearest<Target,Source>::cast(x);
}

} // namespace NICE

#endif // FBASICS_CASTS_H

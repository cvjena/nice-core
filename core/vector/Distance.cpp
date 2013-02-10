
#include <core/vector/Distance.h>

namespace NICE {

template<>
Ipp32f EuclidianDistance<Ipp32f>::doCalculate(const VectorT<Ipp32f>& v1, const VectorT<Ipp32f>& v2) const {

    if(v1.size()!=v2.size())
        fthrow(Exception, "Input vectors must have the same size.");

    Ipp32f dist = 0;

    #ifdef NICE_USELIB_IPP

        VectorT<Ipp32f> res(v1.size());

        ippsSub_32f(v1.getDataPointer(), v2.getDataPointer(), res.getDataPointer(), v1.size());
        ippsSqr_32f(res.getDataPointer(), res.getDataPointer(), res.size());

        dist = res.Sum();

    #else // NICE_USELIB_IPP

        const Ipp32f* pSrc1 = v1.getDataPointer();
        const Ipp32f* pSrc2 = v2.getDataPointer();
                
        for(Ipp32u i=0; i<v1.size(); ++i,++pSrc1,++pSrc2)
            dist += (*pSrc1-*pSrc2)*(*pSrc1-*pSrc2);

    #endif // NICE_USELIB_IPP

    dist = std::sqrt(dist);

    return dist;
}

template<>
Ipp32f BhattacharyyaDistance<Ipp32f>::doCalculate(const VectorT<Ipp32f>& v1, const VectorT<Ipp32f>& v2) const {

    if(v1.size()!=v2.size())
        fthrow(Exception, "Input vectors must have the same size.");

    Ipp32f B;

    #ifdef NICE_USELIB_IPP

        VectorT<Ipp32f> v1f(v1);
        v1f *= v2;

        ippsSqrt(v1f.getDataPointer(), v1f.getDataPointer(), v1f.size());
        ippsSum(v1f.getDataPointer(), v1f.size(), &B);
    
    #else // NICE_USELIB_IPP

        B = 0.0;
        for(uint i=0; i<v1.size(); ++i)
            B += std::sqrt(v1[i]*v2[i]);

    #endif // NICE_USELIB_IPP

    return std::sqrt(1-B);
}

}

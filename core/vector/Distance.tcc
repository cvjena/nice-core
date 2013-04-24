
namespace NICE {

template<class T>
T VectorDistance<T>::calculate(const VectorT<T>& v1 , const VectorT<T>& v2) const {

    return doCalculate(v1,v2);
}

template<class T>
T VectorDistance<T>::operator()(const VectorT<T>& v1 , const VectorT<T>& v2) const {

    return doCalculate(v1,v2);
}

template<class T>
T EuclidianDistance<T>::doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const {

    if(v1.size()!=v2.size())
        _THROW_EVector("Input vectors must have the same size. v1: ");

    T dist = T(0);

    // FIXME BUG in version using IPP
//     #ifdef NICE_USELIB_IPP
//
//         VectorT<Ipp32f> v1f(v1.size()), v2f(v2.size());
//
//         ippsConvert(v1.getDataPointer(), v1f.getDataPointer(), v1.size());
//         ippsConvert(v2.getDataPointer(), v2f.getDataPointer(), v2.size());
//
//         ippsSub_32f(v1f.getDataPointer(), v2f.getDataPointer(), v1f.getDataPointer(), v1f.size());
//         ippsSqr_32f(v1f.getDataPointer(), v1f.getDataPointer(), v1f.size());
//
//         dist = v1f.Sum();
//
//     #else // NICE_USELIB_IPP

        const T* pSrc2 = v2.begin();
        for(const T* pSrc1 = v1.begin();
            pSrc1 < v1.end();
            ++pSrc1, ++pSrc2) {
          dist += (*pSrc1-*pSrc2)*(*pSrc1-*pSrc2);
        }

//     #endif // NICE_USELIB_IPP

    return T(std::sqrt(dist));
}


template<class T>
T MahalanobisDistance<T>::doCalculate( const VectorT<T>& v1, const VectorT<T>& v2 ) const
{
  if ( v1.size()!=v2.size() )
    _THROW_EVector( "Input vectors must have the same size." );

  if ( v1.size()!=m_matrix.rows() )
    _THROW_EVector( "Input vectors must have the same size as matrix." );

  VectorT<T> difference(v1);
  difference -= v2;

  VectorT<T> tmp(difference.size());
  tmp.multiply(m_matrix, difference);

  T dist = std::sqrt(difference.scalarProduct(tmp));

  return dist;
}


template<class T>
T ManhattanDistance<T>::doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const {

    if(v1.size()!=v2.size())
        _THROW_EVector("Input vectors must have the same size.");

    T d = 0;
    ippsNormDiff_L1(v1.getDataPointer(),v2.getDataPointer(),v1.size(),&d);
    return d;
};





template<class T>
T MaximumDistance<T>::doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const {

    if(v1.size()!=v2.size())
        _THROW_EVector("Input vectors must have the same size.");

    T d = 0;
    ippsNormDiff_Inf(v1.getDataPointer(),v2.getDataPointer(),v1.size(),&d);
    return d;
};





template<class T>
T MedianDistance<T>::doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const {

    if(v1.size()!=v2.size())
        _THROW_EVector("Input vectors must have the same size.");

    VectorT<T> r(v1);
    r-=v2;
    r.absInplace();
    r.sortAscend();
    return r[r.size()/2];
};





/**
 * @struct SinDistance
 * @brief  calculate the sinus of the in-between angle
 */
template<class T>
T SinDistance<T>::doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const {

    if(v1.size()!=v2.size())
        _THROW_EVector("Input vectors must have the same size.");

    T d  = 0;
    T d1 = 0;
    T d2 = 0;

    #ifdef NICE_USELIB_IPP

        ippsNorm_L2(v1.getDataPointer(), v1.size(), &d1);
        ippsNorm_L2(v2.getDataPointer(), v2.size(), &d2);
        if(isZero(d1)) d1=T(1.0);
        if(isZero(d2)) d2=T(1.0);
        ippsDotProd(v1.getDataPointer(),v2.getDataPointer(),v1.size(),&d);
        d = d/(d1*d2);
        d = static_cast<T>(sqrt(1-d*d));

    #else // NICE_USELIB_IPP

        typename VectorT<T>::const_iterator it  = v1.getDataPointer();
        typename VectorT<T>::const_iterator it2 = v2.getDataPointer();
        typename VectorT<T>::const_iterator end = v1.getDataPointer() + v1.size();

        for(; it < end; it++, it2++) {
            d1 += *it* *it;
            d2 += *it2* *it2;
        }
        if(isZero(d1))
            d1=T(1.0);
        else
            d1=sqrt(d1);
        if(isZero(d2))
            d2=T(1.0);
        else
            d2=sqrt(d2);

        it  = v1.getDataPointer();
        it2 = v2.getDataPointer();

        for(; it < end; it++, it2++)
            d += *it * *it2;

        d=d/(d1*d2);
        d=sqrt(T(1.0)-d*d);

    #endif // NICE_USELIB_IPP

    return d;
};




/**
 * @struct CosDistance
 * @brief  calculate the cosinus of the in-between angle
 */
template<class T>
T CosDistance<T>::doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const {

    if(v1.size()!=v2.size())
        _THROW_EVector("Input vectors must have the same size.");
	Ipp32f val=0.0;
	if((v1.normL2()*v2.normL2())>1e-8)
	{
		val = (v1.scalarProduct(v2))/(v1.normL2()*v2.normL2());
	}
    
    if(val>=0.0)
	{
		return static_cast<T>(static_cast<T>(1.0)-val);
	}
	else
	{
		return static_cast<T>(static_cast<T>(1.0)+val);
	}
};





template<class T>
T Chi2Distance<T>::doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const {

    if(v1.size()!=v2.size())
        _THROW_EVector("Input vectors must have the same size.");

    T d  = 0;
    T d1 = 0;
    T d2 = 0;
    Ipp32f div,fac;

    #ifdef NICE_USELIB_IPP

        ippsNorm_L2(v1.getDataPointer(),v1.size(),&d1);
        ippsNorm_L2(v2.getDataPointer(),v2.size(),&d2);
        if(isZero(d1)) d1=1;
        if(isZero(d2)) d2=1;
        typename VectorT<T>::const_iterator it2 = v2.getDataPointer();
        typename VectorT<T>::const_iterator end = v1.getDataPointer() + v2.size();
        typename VectorT<T>::const_iterator it = v1.getDataPointer();

        for(; it < end; it++, it2++) {
            div  = (*it/d1 + *it2/d2);

            //div  = div==0?1e-6:div;
            if (std::fabs(div) < std::numeric_limits<T>::epsilon()) {
              div = std::numeric_limits<T>::epsilon();
            }

            fac  = *it/d1-div;
            d   += static_cast<T>(fac*fac/div);
        }
    #else // NICE_USELIB_IPP

        typename VectorT<T>::const_iterator it2 = v2.getDataPointer();
        typename VectorT<T>::const_iterator end = v2.getDataPointer() + v2.size();

        for(; it2 < end; it2++) {
            d2 += *it2;
        }
        if(d2==0) d2=1;
        typename VectorT<T>::const_iterator it = v1.getDataPointer();
        end = v1.getDataPointer() + v1.size();
        for(; it < end; it++) {
            d1 += *it;

        }
        if(isZero(d1)) d1=1;
        it = v1.getDataPointer();
        it2 = v2.getDataPointer();
        for(; it < end; it++, it2++) {
            div=(*it/d1 + *it2/d2)/2.;
            if (std::fabs(div) < std::numeric_limits<T>::epsilon()) {
              div = std::numeric_limits<T>::epsilon();
            }
            fac=*it/d1-div;
            d+=fac*fac/div;
        }
    #endif // NICE_USELIB_IPP

    return d;
};






template<class T>
T SphericalDistance<T>::doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const {

    if(v1.size()!=v2.size())
        _THROW_EVector("Input vectors must have the same size.");

    return static_cast<T>(acos(sin(v1[1])*sin(v2[1])+cos(v1[1])*cos(v2[1])*cos(v1[0]-v2[0])));
};





template<class T>
T KLDistance<T>::doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const {

    if(v1.size()!=v2.size())
        _THROW_EVector("Input vectors must have the same size.");

    Ipp32f res = 0.0;
    typename VectorT<T>::const_iterator it2 = v2.begin();
    for(typename VectorT<T>::const_iterator it1 = v1.begin(); it1!=v1.end(); ++it1,++it2)
        if(*it1>0 && *it2>0)
            res += *it1 * log(*it1 / static_cast<float>(*it2));

    return static_cast<T>(res);
};




template<class T>
SwappedKLDistance<T>::SwappedKLDistance() {

    pKLDistance = new KLDistance<T>();
}

template<class T>
SwappedKLDistance<T>::~SwappedKLDistance() {

    delete pKLDistance;
}

template<class T>
T SwappedKLDistance<T>::doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const {

    if(v1.size()!=v2.size())
        _THROW_EVector("Input vectors must have the same size.");

    return pKLDistance->calculate(v2, v1);
}





template<class T>
ExtendedKLDistance<T>::ExtendedKLDistance() {

    pKLDistance = new KLDistance<T>();
}

template<class T>
ExtendedKLDistance<T>::~ExtendedKLDistance() {

    delete pKLDistance;
}

template<class T>
T ExtendedKLDistance<T>::doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const {

    if(v1.size()!=v2.size())
        _THROW_EVector("Input vectors must have the same size.");

    return static_cast<T>((pKLDistance->calculate(v1, v2)+pKLDistance->calculate(v2, v1))/2.0);
}



template<class T>
T BhattacharyyaDistance<T>::doCalculate(const VectorT<T>& v1, const VectorT<T>& v2) const {

    if(v1.size()!=v2.size())
        _THROW_EVector("Input vectors must have the same size.");

    Ipp32f B;

    #ifdef NICE_USELIB_IPP

        VectorT<Ipp32f> v1f(v1.size()), v2f(v2.size());

        ippsConvert(v1.getDataPointer(), v1f.getDataPointer(), v1.size());
        ippsConvert(v2.getDataPointer(), v2f.getDataPointer(), v2.size());

        v1f *= v2f;

        ippsSqrt(v1f.getDataPointer(), v1f.getDataPointer(), v1f.size());
        ippsSum(v1f.getDataPointer(), v1f.size(), &B);

    #else // NICE_USELIB_IPP

        B = 0.0;
        for(int i=0; i<v1.size(); ++i)
            B += std::sqrt(v1[i]*v2[i]);

    #endif // NICE_USELIB_IPP

    return static_cast<T>(std::sqrt(1-B));
}

template<class T>
T ScalarProductDistance<T>::doCalculate(const VectorT<T>& v1, const VectorT<T>& v2)const  {

    if(v1.size()!=v2.size())
        _THROW_EVector("Input vectors must have the same size.");

    VectorT<T> t1(v1);

    t1 *= v2;

    return -t1.Sum();
}

} // namespace NICE

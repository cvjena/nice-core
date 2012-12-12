#ifndef TRIPLETINCLUDE
#define TRIPLETINCLUDE

namespace NICE {

template <class T1, class T2, class T3>
      struct triplet
      {
        T1 first;
        T2 second;
        T3 third;

      triplet ();
      triplet (const T1& x, const T2& y, const T3& z)
      {
        first = x;
        second = y;
        third = z;
      }
      template <class U1, class U2, class U3>
        triplet (const triplet<U1, U2, U3>& x) {
            first = x.first;
            second = x.second;
            third = x.third;
        }

      // Two keys are equivalent if the comparison function for the keys is false in both directions
      bool operator< ( const triplet<T1, T2, T3> & t ) const
      {
        if (first < t.first) return true;
	else if ( first > t.first ) return false;
	else {
	    if (second < t.second) return true;
	    else if ( second > t.second ) return false;
	    else {
		if (third < t.third) return true;
		else return false;
	    }
	}
      }

      bool operator== ( const triplet<T1, T2, T3> & t ) const
      {
	return ( (t.first == first) && (t.second == second) && (t.third == third) );
      } 
};

}

#endif

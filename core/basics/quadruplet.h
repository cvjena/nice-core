#ifndef quadrupletINCLUDE
#define quadrupletINCLUDE

namespace NICE {

/** @brief quadruplet extension, similar to pair */
template <class T1, class T2, class T3, class T4>
      struct quadruplet
      {
        T1 first;
        T2 second;
        T3 third;
        T4 fourth;

      quadruplet ();
      quadruplet (const T1& x, const T2& y, const T3& z, const T4 & q)
      {
        first = x;
        second = y;
        third = z;
	fourth = q;
      }
      template <class U1, class U2, class U3, class U4>
        quadruplet (const quadruplet<U1, U2, U3, U4>& x) {
            first = x.first;
            second = x.second;
            third = x.third;
	    fourth = x.fourth;
        }

      // Two keys are equivalent if the comparison function for the keys is false in both directions
      bool operator< ( const quadruplet<T1, T2, T3, T4> & t ) const
      {
        if (first < t.first) return true;
	else if ( first > t.first ) return false;
	else {
	    if (second < t.second) return true;
	    else if ( second > t.second ) return false;
	    else {
		if (third < t.third) return true;
		else if (third > t.third) return false;
		else {
		    if (fourth < t.fourth) return true;
		    else return false;
		}
	    }
	}
      }

      bool operator== ( const quadruplet<T1, T2, T3, T4> & t ) const
      {
	return ( (t.first == first) && (t.second == second) && (t.third == third) 
	    && (t.fourth == fourth) );
      } 
};

}

#endif

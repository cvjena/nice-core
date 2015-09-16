/*
   Example files for explicit opaque templates
*/

#include "OpaqueT.h"

namespace NICE {
	// Implementations
	template<class T>void OpaqueT<T>::CallMe(T arg) {
		std::cout << arg;
	}
}

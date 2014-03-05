/*
   Example files for explicit opaque templates
*/

#include <iostream>
#include <string>

#include "OpaqueT.h"
#include "OpaqueT.tcc"

namespace NICE {
		// Explicit instances
		template class OpaqueT<std::string>;
		template class OpaqueT<int>;
}

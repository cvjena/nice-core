/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#ifndef _EVECTORBASE_H_
#define _EVECTORBASE_H_

#include <string>
#include <sstream>
#include <stdexcept>

namespace NICE {

/**
 * @brief  Base class for VectorT
 * @author Ferid Bajramovic
 */
class VectorBase 
{
	public:
		//! Mode for constructor with external storage support.
		enum Mode{copy, external};
};

}

#ifdef __GNUC__
//#include "core/vector/VectorBase.tcc"
#endif

#endif

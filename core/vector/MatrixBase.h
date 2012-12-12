/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#ifndef _EMATRIXBASE_BASICMATRIX_H
#define _EMATRIXBASE_BASICMATRIX_H

#include <string>
#include <sstream>
#include <stdexcept>

namespace NICE {

/**
 * @brief  Base class for MatrixT
 * @author Ferid Bajramovic
 */
class MatrixBase {
public:
  //! Mode for constructor with external storage support.
  enum Mode {copy, external};
};

}

#ifdef __GNUC__
//#include "core/vector/MatrixBase.tcc"
#endif

#endif // _EMATRIXBASE_BASICMATRIX_H

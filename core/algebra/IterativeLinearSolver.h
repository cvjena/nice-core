/** 
* @file IterativeLinearSolver.h
* @author Erik Rodner
* @date 12/21/2011

*/
#ifndef _NICE_ITERATIVELINEARSOLVERINCLUDE
#define _NICE_ITERATIVELINEARSOLVERINCLUDE

#include "core/vector/VectorT.h"
#include "GenericMatrix.h"

namespace NICE {
  
/** @class IterativeLinearSolver
 * abstract interface for iterative linear solvers working with GenericMatrix 
 *
 * @author Erik Rodner
 */
class IterativeLinearSolver
{

    protected:

    public:

		/** simple constructor */
		IterativeLinearSolver();
		  
		/** simple destructor */
		virtual ~IterativeLinearSolver();

    /**
    * @brief Solve the linear System A*x = b, where A is indirectly presented
    * by the GenericMatrix gm
    *
    * @param gm GenericMatrix providing matrix-vector multiplications
    * @param b Vector on the right hand side of the system
    * @param x initial and final estimate
    *
    * @return method specific status information
    */
    virtual int solveLin ( const GenericMatrix & gm, const Vector & b, Vector & x ) = 0;
};

}

#endif

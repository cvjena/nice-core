/** 
* @file FirstOrderRasmussen.h
* @author Erik Rodner
* @date 01/25/2010

*/
#ifndef _NICE_FIRSTORDERRASMUSSENINCLUDE
#define _NICE_FIRSTORDERRASMUSSENINCLUDE

#include "core/optimization/gradientBased/OptimizationAlgorithmFirst.h"
#include "core/optimization/gradientBased/OptimizationProblemFirst.h"

namespace NICE {
  
/** @class FirstOrderRasmussen
 * C/C++ implementation of Carl Edward Rasmussens matlab optimization code.
 * Conjugate gradient optimization (Polack-Ribiere flavour) and line
 * search using quadratic and cubuc approximation.
 * Details: http://www.kyb.tuebingen.mpg.de/bs/people/carl/code/minimize/
 *
 * \ingroup optimization_algorithms
 * @author Erik Rodner
 */
class FirstOrderRasmussen : public NICE::OptimizationAlgorithmFirst
{

    protected:
	
		/** Don't reevaluate within 0.1 of the limit of the current bracket */
		double c_int;
		/** Extrapolate maximum c_ext times the current step-size */
		double c_ext;
		/** Max c_max function evaluations per line search */
		uint c_max;

		/** Maximum allowed slope ratio */
		double c_ratio;

		/** Some constants controlling the Wolfe-Powell conditions,
		 *  details are described in the code. */
		double c_sig;
		double c_rho;
		
		/** Abort optimization if gradient norm (L2) is lower than this threshold */
		double epsilonG;

		/* If length is positive, it gives the maximum number of line searches, if negative its
		 * absolute gives the maximum allowed number of function evaluations. */
		int length;

		/** print debug information */
		bool verbose;
	
		/** optimization algorithm */
		void doOptimizeFirst(NICE::OptimizationProblemFirst& problem);

    public:
  
		/** simple constructor */
		FirstOrderRasmussen( bool verbose = true );
		  
		/** simple destructor */
		virtual ~FirstOrderRasmussen();

		/** abort optimization if gradient norm (L2) is lower than this threshold */
		void setEpsilonG ( double _epsilonG ) { epsilonG = _epsilonG; };

		/* if the parameter is positive, it gives the maximum number of line searches, if negative its
		 * absolute gives the maximum allowed number of function evaluations. */
		void setMaxIterations ( int _length ) { length = _length; };

     
};

}

#endif

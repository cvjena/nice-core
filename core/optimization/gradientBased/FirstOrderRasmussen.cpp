/** 
* @file FirstOrderRasmussen.cpp
* @brief c/c++ implementation of rasmussens optimization method
* @author Erik Rodner
* @date 01/25/2010

*/
#include <iostream>

#include "FirstOrderRasmussen.h"

#include <core/basics/Log.h>

using namespace std;
using namespace NICE;

FirstOrderRasmussen::FirstOrderRasmussen( bool _verbose )
	: verbose(_verbose)
{
	c_int = 0.1;  // don't reevaluate within 0.1 of the limit of the current bracket
	c_ext = 3.0;  // extrapolate maximum 3 times the current step-size
	c_max = 20;   // max 20 function evaluations per line search
	c_ratio = 10; // maximum allowed slope ratio
	
	/* SIG and RHO are the constants controlling the Wolfe-
	 * % Powell conditions. SIG is the maximum allowed absolute ratio between
	 * % previous and new slopes (derivatives in the search direction), thus setting
	 * % SIG to low (positive) values forces higher precision in the line-searches.
	 * % RHO is the minimum allowed fraction of the expected (from the slope at the
	 * % initial point in the linesearch). Constants must satisfy 0 < RHO < SIG < 1.
	 * % Tuning of SIG (depending on the nature of the function to be optimized) may
	 * % speed up the minimization; it is probably not worth playing much with RHO */
	c_sig = 0.1;
	c_rho = c_sig / 2.0; 

	// set maximum function evaluations to 100
	length = -100;

	epsilonG = 1e-5; // if gradient norm is lower than this threshold -> exit
}

FirstOrderRasmussen::~FirstOrderRasmussen()
{
}

void FirstOrderRasmussen::doOptimizeFirst(OptimizationProblemFirst& problem)
{
	/** Comments of Carl Edward Rasmussen (2006-09-08).
	 *
	 * The code falls naturally into 3 parts, after the initial line search is
	 * started in the direction of steepest descent. 1) we first enter a while loop
	 * which uses point 1 (p1) and (p2) to compute an extrapolation (p3), until we
	 * have extrapolated far enough (Wolfe-Powell conditions). 2) if necessary, we
	 * enter the second loop which takes p2, p3 and p4 chooses the subinterval
	 * containing a (local) minimum, and interpolates it, unil an acceptable point
	 * is found (Wolfe-Powell conditions). Note, that points are always maintained
	 * in order p0 <= p1 <= p2 < p3 < p4. 3) compute a new search direction using
	 * conjugate gradients (Polack-Ribiere flavour), or revert to steepest if there
	 * was a problem in the previous line-search. Return the best value so far, if
	 * two consecutive line-searches fail, or whenever we run out of function
	 * evaluations or line-searches. During extrapolation, the "f" function may fail
	 * either with an error or returning Nan or Inf, and minimize should handle this
	 * gracefully. */

	/** reimplementation comments (Erik)
	 * I just converted the matlab code manually to this nasty piece of C/C++ code.
	 * The only changes are due to the apply/unapply mechanism of nice optimization
	 * interface. I also skipped some unneccessary gradient computations. */
	double red = 1.0;

	uint i = 0;
	bool ls_failed = false;
	double f0 = problem.objective();
  if ( verbose )
    cerr << "FirstOrderRasmussen: initial value of the objective function is " << f0 << endl;

	problem.computeGradient();
	Vector df0 = problem.gradientCached();

	if ( length < 0 ) i++;

	Vector s = - 1.0 * df0;
	double d0 = - s.scalarProduct(s);
	double d1, d2, d3;
	double d4 = d0;
	double x1, x2;
	double x4 = 0.0;
	double x3 = red / (1-d0);

	double f1, f2, f3;
	double f4 = f0;
	Vector df3 (df0.size());
	Vector df2 (df0.size());
	Vector df1 (df0.size());
	Vector dF0 (df0.size());
	double F0;
	Vector X0delta ( problem.position().size());
	
	while ( i < (uint)abs(length) )
	{
		if ( verbose )
			std::cerr << "Iteration " << i << " / " << abs(length) << " " << " objective function = " << f0 << std::endl;
		i = i + (length>0);

		if ( df0.normL2() < epsilonG ) {
			if ( verbose )
				Log::debug() << "FirstOrderRasmussen: low gradient " << df0.normL2() << " < " << epsilonG << " = epsilonG" << std::endl;
			break;
		}

		X0delta.set(0.0);
		F0 = f0;
		dF0 = df0;

		double M;
		if ( length > 0 ) 
			M = c_max;
		else
			M = std::min(c_max, -length-i);

    // perform a line search method (as far as I know)
		while (1) 
		{
			x2 = 0;
			f2 = f0;
			d2 = d0;
			f3 = f0;
			df3 = df0;
			bool success = false;
			while ( !success && (M>0) )
			{
				M = M -1; i = i + (length<0);

				problem.applyStep ( x3*s );
				f3 = problem.objective();
				if ( finite(f3) ) success = true;
				
				if ( !success && (M>0) ) 
					problem.unapplyStep ( x3*s );

				if ( !finite(f3) )
        {
					x3 = (x2 + x3) / 2.0;
        }
			}
			problem.computeGradient();
			df3 = problem.gradientCached();
			problem.unapplyStep ( x3 * s );

			if ( f3 < F0 ) {
				X0delta = x3 * s;
				F0 = f3;
				dF0 = df3;
			}

			d3 = df3.scalarProduct (s);
			if ( (d3 > c_sig * d0) || (f3 > f0 + x3*c_rho*d0) || (M==0) )
				break;

			x1 = x2; f1 = f2; d1 = d2;
			x2 = x3; f2 = f3; d2 = d3;

			double A = 6*(f1-f2) + 3*(d2+d1)*(x2-x1);
			double B = 3*(f2-f1)-(2*d1+d2)*(x2-x1);
			x3 = x1-d1*pow((x2-x1),2)/(B+sqrt(B*B-A*d1*(x2-x1)));
			if ( !finite(x3) || (x3 < 0 ) )
      {
				x3 = x2*c_ext;
			} else if (x3 > x2 * c_ext) {
				x3 = x2*c_ext;
			} else if (x3 < x2 + c_int*(x2 - x1) ) {
				x3 = x2 + c_int*(x2-x1);
      }
			
		}

		while ( ( (abs(d3) > -c_sig*d0) || (f3 > f0+x3*c_rho*d0) ) && (M > 0) )
		{
			if ( (d3 > 0) || (f3 > f0+x3*c_rho*d0) )
			{
				x4 = x3; f4 = f3; d4 = d3;
			} else {
				x2 = x3; f2 = f3; d2 = d3;
			}

			if ( f4 > f0 ) {
				x3 = x2-(0.5*d2*pow((x4-x2),2))/(f4-f2-d2*(x4-x2));
			} else {
        // we observed that this computation can be critical 
        // and instable
				double A = 6*(f2-f4)/(x4-x2)+3*(d4+d2);
				double B = 3*(f4-f2)-(2*d2+d4)*(x4-x2);

        // small values of A (1e-6) have a big influence on x3
				x3 = x2+(sqrt(B*B-A*d2*pow(x4-x2,2))-B)/A;
			}

			if ( !finite(x3) ) {
				x3 = (x2 + x4) / 2.0;
      }

			x3 = std::max(std::min(x3, x4-c_int*(x4-x2)),x2+c_int*(x4-x2));
			problem.applyStep ( x3*s );
			f3 = problem.objective();
			problem.computeGradient();
			df3 = problem.gradientCached();
			problem.unapplyStep ( x3*s );

			if ( f3 < F0 ) {
				X0delta = x3 * s;
				F0 = f3;
				dF0 = df3;
			}
			M = M - 1;
			i = i + (length < 0);
			d3 = df3.scalarProduct ( s );
		}

		if ( (abs(d3) < - c_sig * d0) && (f3 < f0 + x3 * c_rho * d0) )
		{
			problem.applyStep ( x3 * s );
      if ( verbose )
        cerr << "FirstOrderRasmussen: new objective value " << f3 << endl;


			f0 = f3;
			s = ( df3.scalarProduct(df3) - df0.scalarProduct(df3))/(df0.scalarProduct(df0)) * s - df3;
			df0 = df3;
			d3 = d0; d0 = df0.scalarProduct(s);
			if ( d0 > 0 ) {
				s = -1.0 * df0; d0 = - s.scalarProduct(s);
			}

			x3 = x3 * std::min(c_ratio, d3/(d0-std::numeric_limits<float>::min()) );
			ls_failed = false;
		} else {
			problem.applyStep ( X0delta );
			f0 = F0;
			df0 = dF0;
			// if maximum number of iterations exceeded or line
			// search failed twice in a row
			if ( ls_failed || (i > (uint)abs(length) ) )
			{
        if ( (i > (uint)abs(length)) && verbose )
          cerr << "FirstOrderRasmussen: maximum number of iterations reached" << endl;
        else if ( verbose )
          cerr << "FirstOrderRasmussen: line search failed twice" << endl;
				break;
			}
			s = - 1.0 * df0;
			d0 = - s.scalarProduct(s);
			x3 = 1.0/(1.0 - d0);
			ls_failed = true;
		}

	}

}

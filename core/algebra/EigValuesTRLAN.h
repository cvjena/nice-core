#ifndef EIGVALUESTRLANINCLUDE
#define EIGVALUESTRLANINCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string.h>


#include "EigValues.h"


namespace NICE {

/** real symmetric eigenproblem, the eigenpairs returned by the method solve are ordered increasingly
 * (needs the TRLAN library, is not thread-safe!)
 */
class EigValuesTRLAN : public EigValues {

  private:
    int magnitude;
    int restarting_scheme;
    double tolerance;
    int max_mult;
    int mult_flops;
    bool verbose;

  public:

    /**
    * @brief Init the TRLAN lanczos routine with the following parameters
    *
    * @param magnitude Specifies the nature of the EigValuesTRLAN, find eigenpair with respect to the k largest (magnitude>0)
    * @param restarting_scheme restarting scheme of TRLAN
    * @param tolerance stop criterion (abs. resudual |A*x-lambda*x|?)
    * @param max_mult  maximum number of matrix-vector multiplications to perform
    * @param mult_flops number of flops per matrix multiplication (used for statistics calculation)
    */
    EigValuesTRLAN ( int magnitude = 1,
                     int restarting_scheme = 1,
                     double tolerance = 1e-8,
                     int max_mult = -1,
                     int mult_flops = -1 );

    /** destructor */
    ~EigValuesTRLAN() {};

    /**
       * @param data matrix interface that does allow matrix-vector multiplications
       * @param k number of eigenvalues/eigenvectors
       * @param eigenvectors output Eigenvectors as Matrix
       * @param eigenvalues output Eigenvalues as Vector
       */
    virtual void getEigenvalues ( const GenericMatrix &data, NICE::Vector & eigenvalues, NICE::Matrix & eigenvectors, uint k );
};


} // namespace

#endif

/**
* @file EigValues.h
* @brief Computing eigenvalues and eigenvectors
* @author Michael Koch,Erik Rodner
* @date 08/19/2008

*/
#ifndef EigValuesINCLUDE
#define EigValuesINCLUDE

#include "GenericMatrix.h"

namespace NICE
{

/** Computing eigenvalues and eigenvectors */
class EigValues
{

  protected:

  public:

    /**
      * @param data matrix interface that does allow matrix-vector multiplications
      * @param k number of eigenvalues/eigenvectors
      * @param eigenvectors output Eigenvectors as Matrix
      * @param eigenvalues output Eigenvalues as Vector
      */
    virtual void getEigenvalues ( const GenericMatrix & data,
                                  NICE::Vector & eigenvalues,
                                  NICE::Matrix & eigenvectors, uint k ) = 0;

    virtual ~EigValues ()
    {
    };

};

/** arnoldi iteration */
class EVArnoldi : public EigValues
{
  protected:
    uint maxiterations;
    double mindelta;
    bool verbose;

  public:
    EVArnoldi ( bool verbose = false, uint _maxiterations = 100, double _mindelta = 0.01 )
        : maxiterations ( _maxiterations ), mindelta ( _mindelta )
    {
      this->verbose = verbose;
    };

    /**
      * Arnoldi Iteration, to get k first eigenvectors and eigenvalues
      * @param data matrix interface that does allow matrix-vector multiplications
      * @param k number of eigenvalues/eigenvectors
      * @param eigenvectors output Eigenvectors as Matrix
      * @param eigenvalues output Eigenvalues as Vector
      */
    void getEigenvalues ( const GenericMatrix & data, NICE::Vector & eigenvalues,
                          NICE::Matrix & eigenvectors, uint k );
};


} // namespace

#endif

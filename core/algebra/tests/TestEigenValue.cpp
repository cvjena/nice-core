/**
 * @file TestEigenValue.cpp
 * @brief TestEigenValue
 * @author Michael Koch
 * @date Di Aug 4 2009
 */

#include "TestEigenValue.h"
#include <string>

#include "core/basics/cppunitex.h"
#include "core/basics/numerictools.h"
#include "core/vector/Distance.h"

#include "core/algebra/EigValues.h"
#include "core/algebra/EigValuesTRLAN.h"
#include "core/algebra/GenericMatrix.h"
#include "core/algebra/GMStandard.h"

using namespace std;
using namespace NICE;

CPPUNIT_TEST_SUITE_REGISTRATION(TestEigenValue);

void TestEigenValue::setUp()
{
}

void TestEigenValue::tearDown()
{
}

void TestEigenValue::TestEigenValueComputation()
{
    // size of the matrix
    uint rows = 100;
    uint cols = rows;
  
    // number of eigenvalues used
    uint k = 10;
    uint maxiterations =  200;
    double mindelta = 1e-8;

    
    double sparse_prob = 0.3;
    int trlan_magnitude = 1;

    NICE::Matrix T(rows, cols, 0.0);

    // use a fixed seed, its a test case
    srand48(0);

    // generate random symmetric matrix
    for (uint i = 0 ; i < rows ; i++)
        for (uint j = i ; j < cols ; j++)
        {
            if (sparse_prob != 0.0)
                if (drand48() < sparse_prob)
                    continue;
            T(i, j) = drand48();
            T(j, i) = T(i, j);
        }

    // create a positive definite matrix
    T = T*T;

    EigValues *eig;
    for (int trlan = 0;trlan <= 1;trlan++) //this is creepy but funny
    {
        if (trlan) //this is creepy but saves lot of code
        {
#ifdef NICE_USELIB_TRLAN
            eig = new EigValuesTRLAN(trlan_magnitude);
#else
            cerr << "EigValuesTRLAN is not checked, because TRLAN was not installed." << endl;
            break;
#endif
        }
        else
        {
            eig = new EVArnoldi(false, maxiterations, mindelta);
        }

        NICE::Vector eigvalues_dense;
        NICE::Matrix eigvect_dense;
        NICE::Vector eigvalues_sparse;
        NICE::Matrix eigvect_sparse;

        GMStandard Tg(T);
        eig->getEigenvalues(Tg, eigvalues_dense, eigvect_dense, k);

        GMSparse Ts(T);
        eig->getEigenvalues(Ts, eigvalues_sparse, eigvect_sparse, k);

        // test property
        NICE::EuclidianDistance<double> eucliddist;
        for (uint i = 0 ; i < k ; i++)
        {
            NICE::Vector v_dense = eigvect_dense.getColumn(i);
            double lambda_dense = eigvalues_dense[i];
            NICE::Vector Tv_dense;
            Tv_dense.multiply(T, v_dense);
            NICE::Vector lv_dense = v_dense;
            lv_dense *= lambda_dense;
            double err_dense = eucliddist(Tv_dense, lv_dense);

            // check whether the eigenvector definition holds
            NICE::Vector v_sparse = eigvect_sparse.getColumn(i);
            double lambda_sparse = eigvalues_sparse[i];
            NICE::Vector Tv_sparse;
            Tv_sparse.multiply(T, v_sparse);
            NICE::Vector lv_sparse = v_sparse;
            lv_sparse *= lambda_sparse;
            double err_sparse = eucliddist(Tv_sparse, lv_sparse);

//             cerr << "||Av - lambda v|| (dense) = " << err_dense << endl;
//             cerr << "||Av - lambda v|| (sparse) = " << err_sparse << endl;

            // use relative errors instead of absolute errors
            err_sparse /= Tv_sparse.normL2();
            err_dense /= Tv_dense.normL2();

        
            CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0,err_dense,1e-2);
            CPPUNIT_ASSERT_DOUBLES_EQUAL_NOT_NAN(0.0,err_sparse,1e-2);
        }
    }
}

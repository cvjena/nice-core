/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - An core/vector/template for new NICE libraries
 * See file License for license information.
 */

#ifdef NICE_USELIB_CPPUNIT

#include "TestDistance.h"
#include <string>
#include <exception>

using namespace NICE;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( TestDistance );

void TestDistance::setUp() {
}

void TestDistance::tearDown() {
}

void TestDistance::testConstructor() {
}

void TestDistance::testDistance() {

    Ipp32u size = 5;

    VectorT<Ipp32f> v1(size), v2(size);
    for(Ipp32u i=0; i<size; ++i) {
        v1[i] =   i;
        v2[i] = 2*i;
    }


    VectorDistance<Ipp32f>* vDist;

    ManhattanDistance<Ipp32f>           manDist;
    EuclidianDistance<Ipp32f>           eucDist;    
    MaximumDistance<Ipp32f>             maxDist;
    MedianDistance<Ipp32f>              medDist;
    Chi2Distance<Ipp32f>                chiDist;
    SphericalDistance<Ipp32f>           sphDist;
    SinDistance<Ipp32f>                 sinDist;
    CosDistance<Ipp32f>                 cosDist;
    KLDistance<Ipp32f>                  klDist;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(eucDist(v1,v2), 5.47723, 1e-5);
    vDist = &eucDist;
    CPPUNIT_ASSERT_DOUBLES_EQUAL((*vDist).calculate(v1,v2), eucDist.calculate(v1,v2), 1e-10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL((*vDist)(v1,v2), eucDist(v1,v2), 1e-10);

    vDist = &manDist;
    CPPUNIT_ASSERT_DOUBLES_EQUAL((*vDist)(v1,v2), manDist(v1,v2), 1e-10);

    vDist = &maxDist;
    CPPUNIT_ASSERT_DOUBLES_EQUAL((*vDist)(v1,v2), maxDist(v1,v2), 1e-10);

    vDist = &medDist;
    CPPUNIT_ASSERT_DOUBLES_EQUAL((*vDist)(v1,v2), medDist(v1,v2), 1e-10);

    vDist = &chiDist;
	// A delta greater than 1e-10 is on some machines too large (especially 32bit)
    CPPUNIT_ASSERT_DOUBLES_EQUAL((*vDist)(v1,v2), chiDist(v1,v2), 1e-7);

    vDist = &sphDist;
    CPPUNIT_ASSERT_DOUBLES_EQUAL((*vDist)(v1,v2), sphDist(v1,v2), 1e-10);

    vDist = &sinDist;
    CPPUNIT_ASSERT_DOUBLES_EQUAL((*vDist)(v1,v2), sinDist(v1,v2), 1e-10);

    vDist = &cosDist;
    CPPUNIT_ASSERT_DOUBLES_EQUAL((*vDist)(v1,v2), cosDist(v1,v2), 1e-10);

    vDist = &klDist;
    CPPUNIT_ASSERT_DOUBLES_EQUAL((*vDist)(v1,v2), klDist(v1,v2), 1e-10);   
}

void TestDistance::testEuclidianDistance() {

    {
        Ipp32f _d1[6] = {0.2, 0.15, 0.3, 0.05, 0.1, 0.2};   
        Ipp32f _d2[6] = {0.4, 0.1 , 0.1, 0.1,  0.2, 0.1};

        FloatVector v1(_d1, 6), v2(_d2, 6);

        EuclidianDistance<Ipp32f> eDist;

        Ipp32f eucDist = eDist(v1, v2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.324037, eucDist, 1e-6);
    }

    {
        Ipp8u _d1[6] = {1, 2, 2, 4, 3, 1};
        Ipp8u _d2[6] = {2, 2, 3, 1, 2, 3};

        VectorT<Ipp8u> v1(_d1, 6), v2(_d2, 6);

        EuclidianDistance<Ipp8u> eDist;

        Ipp8u eucDist = eDist(v1, v2);

        CPPUNIT_ASSERT_EQUAL(4, static_cast<int>(eucDist));
    }
}

void TestDistance::testCosinusDistance() {

    {
        Ipp32f _d1[6] = {0.2, 0.15, 0.3, 0.05, 0.1, 0.2};   
        Ipp32f _d2[6] = {0.4, 0.1 , 0.1, 0.1,  0.2, 0.1};

        FloatVector v1(_d1, 6), v2(_d2, 6);

        CosDistance<Ipp32f> cDist;
        
        Ipp32f cosDist = cDist(v1, v2);
		
		CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2335809, cosDist, 1e-6);
		//parallel
		Ipp32f _d3[6] = {0.2, 0.1, 0.3, 0.05, 0.1, 0.2};   
		Ipp32f _d4[6] = {0.4, 0.2 , 0.6, 0.1,  0.2, 0.4};

		FloatVector v3(_d3, 6), v4(_d4, 6);
        
		cosDist = cDist(v3, v4);
		
		CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, cosDist, 1e-6);
    }
}

void TestDistance::testScalarProductDistance() {

    Ipp32f _d1[6] = {0.2, 0.15, 0.3, 0.05, 0.1, 0.2};   
    Ipp32f _d2[6] = {0.4, 0.1 , 0.1, 0.1,  0.2, 0.1};

    FloatVector v1(_d1, 6), v2(_d2, 6);

    ScalarProductDistance<Ipp32f> spdDist;
        
    Ipp32f spDist = spdDist(v1, v2);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.17, spDist, 1e-6);
}

void TestDistance::testBhattacharyyaDistance() {

    Ipp32f _d1[6] = {0.2, 0.15, 0.3, 0.05, 0.1, 0.2};   
    Ipp32f _d2[6] = {0.4, 0.1 , 0.1, 0.1,  0.2, 0.1};

    FloatVector v1(_d1, 6), v2(_d2, 6);

    BhattacharyyaDistance<Ipp32f> bhDist;
        
    Ipp32f bDist = bhDist(v1, v2);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2606228, bDist, 1e-6);
}

void TestDistance::testKLDistance() {

    Ipp32f _d1[6] = {0.2, 0.15, 0.3, 0.05, 0.1, 0.2};   
    Ipp32f _d2[6] = {0.4, 0.0 , 0.0, 0.0,  0.2, 0.1};

    FloatVector v1(_d1, 6), v2(_d2, 6);

    KLDistance<Ipp32f> klDist;
    SwappedKLDistance<Ipp32f> sklDist;
    ExtendedKLDistance<Ipp32f> eklDist;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.0693147, klDist(v1, v2), 1e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.346574, sklDist(v1, v2), 1e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.138629, eklDist(v1, v2), 1e-6);
}

#endif

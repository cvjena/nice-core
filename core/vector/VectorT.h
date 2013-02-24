/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libbasicvector - A simple vector library
 * See file License for license information.
 */
#ifndef _EVECTOR_BASICVECTOR_H
#define _EVECTOR_BASICVECTOR_H

#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstddef> // needed for ptrdiff_t


#include "core/vector/ippwrapper.h"

#include <core/basics/binstream.h>

#ifdef NICE_USELIB_LINAL
    #include <LinAl/vectorC.h>
#endif

#ifdef NICE_USELIB_OPENMP
#include <omp.h>
#endif

#include "core/vector/VectorBase.h"

namespace NICE {

template<class ElementType>
class MatrixT;
template<class ElementType>
class RowMatrixT;

/**
 * @class VectorT
 * @brief  VectorT is a simple vector template class
 * @author Ferid Bajramovic (based on \c extarray from ckolumbus)
 *
 * \c VectorT is a simple vector class which provides the (optional) ability
 * to use externally allocated memory as storage.
 * The main features are:
 * - In concept an efficient implementation of a mathematical vector
 * - An array-like storage class
 * - Support for externally allocated memory
 * - Ability to get pointer to internal memory
 * - Thus the ability to <b>directly</b> interface with other libraries such as
 *   LinAl without time consuming data copying
 *
 * @note VectorT objects can only be copied and assigned to each other to
 *       a limited degree. This means that care has to be taken when putting
 *       VectorT objects into STL containers (such as std::vector).
 *       Example: Resizing a std::vector<VectorT> will work, as elements will be
 *       copied to new EVectors. However, std::vector<VectorT>::erase() will
 *       only work when all (subsequent) VectorT objects have the same size.
 *       (Details may depend on the implemenation of the STL.)
 *
 * @example basicvector_vector_overview.cpp
 */
template<class ElementType>
class VectorT : public VectorBase {
public:
    //! STL-like typedef for type of elements
    typedef ElementType value_type;

    //! STL-like typedef for const element reference
    typedef const ElementType& const_reference;

    //! STL-like typedef for iterator
    typedef ElementType* iterator;

    //! STL-like typedef for const iterator
    typedef const ElementType* const_iterator;

    //! STL-like typedef for element reference
    typedef ElementType& reference;

    /**
    * @name constructor
    * \{
    */

    /**
    * @brief Create an empty \c VectorT with size zero.
    *
    * Such an object is actually useless, but sometimes you may need to have
    * such instances to initalize some data structure.
    * The only way to turn such an object into something useful is operator=().
    */
    VectorT();

    /**
    * @brief Create an \c VectorT with size \c size.
    *        Data will not be initialized.
    * @param size Size of the \c VectorT
    */
    explicit VectorT(const size_t size);

    /**
    * @brief Create an \c VectorT with size \c size.
    *        Data will be initialized to \c element.
    * @param size Size of the \c VectorT
    * @param element Initial value of all elements
    */
    VectorT(const size_t size, const ElementType& element);

    /**
    * @brief Create an \c VectorT of size \c size.
    *        It will be initialized with the data pointed to by \c _data.
    *
    * That is the first \c size elements of \c _data will be copied.
    * @param _data Data to be copied
    * @param size Size
    */
    VectorT(const ElementType* _data, const size_t size);

    /**
    * @brief Create an \c VectorT of size \c size
    *        with optionally external storage.
    *
    * It will be initialized with the data pointed to by \c _data.
    * The parameter _external control whether the data will be copied or
    * the pointer \c _data is directly kept as storage for the \c VectorT.
    * In case of external storage the data will not be deleted in the destructor.
    * @param _data External data storage
    * @param size Size of the external storage
    * @param mode Storage mode: keep external memory or copy data.
    */
    VectorT(ElementType* _data, const size_t size,
            const VectorBase::Mode mode = copy);

    /**
    * @brief Create an \c VectorT as a copy of the data in \c v
    * @param v data
    */
    explicit VectorT(const std::vector<ElementType>& v);

    /**
    * @brief Read from input stream.
    * @param input Read from here
    */
   explicit VectorT(std::istream& input, const bool & AwAFormat=false);

    //! copy constructor
    VectorT(const VectorT<ElementType>& v);


    /**
    * \}
    * @name destructor
    * \{
    */
    virtual ~VectorT();

    /**
    * \}
    * @name access functions
    * \{
    */

    /**
    * @brief Create a const VectorT of size \c size
    *        with <b>external</b> storage.
    *
    * It will be initialized with the data pointed to by %_data.
    * The data will not be deleted in the destructor.
    * @param _data External data storage
    * @param size Size of the external storage
    */
    inline static const VectorT<ElementType>* createConst(const ElementType* _data,
                                            const size_t size);

    /**
    * @brief Read access to elements.
    * @param i Index
    * @return Element (as const reference)
    * @example basicvector_vector_access_operator1.cpp
    */
    inline const_reference operator[](const ptrdiff_t i) const {
        return constData[i];
    }

    /**
    * @brief Read access to range checked elements.
    * @param i Index
    * @return Element (as const reference)
    * @example basicvector_vector_access_operator2.cpp
    */
    inline const_reference operator()(const ptrdiff_t i) const;

    /**
    * @brief Get a const pointer to the internal memory.
    */
//     operator ElementType const* () const { return constData; }

    /**
    * @brief Get a const_iterator pointing to the first element.
    *
    * (Actually the same as \c getDataPointer())
    * @example basicvector_vector_access_iterator.cpp
    */
    inline const_iterator begin() const { return constData; }

    /**
    * @brief Get an iterator pointing beyond the last element.
    */
    inline const_iterator end() const { return constData + dataSize; }

        /**
    * @brief Access to elements.
    * @param i Index
    * @return Element
    */
    inline const ElementType& get(const ptrdiff_t i) { return data[i]; }

    /**
    * @brief Access to elements.
    * @param i Index
    * @param v value to assign
    * @return Element
    */
    inline void set(const ptrdiff_t i, const ElementType& v) { data[i] = v; }

    /**
    * @brief Access to elements.
    * @param i Index
    * @return Element (as reference)
    */
    inline reference operator[](const ptrdiff_t i) { return data[i]; }

    /**
    * @brief Access to range checked elements.
    * @param i Index
    * @return Element (as reference)
    */
    inline reference operator()(const ptrdiff_t i);

    /**
    * @brief append a vector (this function is extremely inefficient,
    *  because we have to dealloc and copy the whole vector.
    *  For efficiency reasons std::vector might be the better solution.
    * @param v vector which we appended to the current vector
    */
    void append ( const VectorT<ElementType> & v );

    /**
    * @brief append a value to the vector (this function is extremely inefficient,
    *  because we have to dealloc and copy the whole vector.
    *  For efficiency reasons std::vector might be the better solution.
    * @param v value which is appended to the current vector
    */
    void append ( const ElementType & v );

    /**
    * @brief copy a range of the vector
    * @param i start index
    * @param k end index
    */
    VectorT<ElementType> getRange ( const ptrdiff_t i, const ptrdiff_t j ) const;

    /**
    * @brief get a vector which uses the same memory as the current
    * vector in a specific range
    * @param i start index
    * @param j end index
    */
    VectorT<ElementType> getRangeRef ( const ptrdiff_t i, const ptrdiff_t j );

    /**
    * @brief Get a pointer to the internal memory.
    */
//     inline operator ElementType* () { return data; }

    /**
    * Get a pointer to the internal memory.
    * @example basicvector_vector_access_pointer.cpp
    */
    inline ElementType* getDataPointer() { return data; }

    /**
    * Get a const pointer to the internal memory.
    * @example basicvector_ippusage.cpp
    */
    inline const ElementType* getDataPointer() const { return constData; }

    /**
    * @brief Get an iterator pointing to the first element.
    *
    * (Actually the same as \c getDataPointer())
    */
    inline iterator begin() { return data; }

    /**
    * @brief Get an iterator pointing beyond the last element.
    */
    inline iterator end() { return data + this->dataSize; }

    /**
    * @brief Return the size of this VectorT.
    * @return Size of this VectorT.
    */
    inline size_t size() const { return dataSize; }

    /**
    * \}
    * @name statistical functions
    * \{
    */

    /**
    * Scalar product "this * v"
    * @param v Second factor
    * @return this * v
    */
    inline ElementType scalarProduct(const VectorT<ElementType>& v) const;

    /**
    * Sum of elements
    * @return Sum of elements
    */
    inline ElementType Sum() const;

    /**
    * Mean of elements
    * @return Mean of elements
    * @example basicvector_vector_meanstddev.cpp
    */
    inline ElementType Mean() const;

    /**
    * Median of elements
    * @return Median of elements
    */
    inline ElementType Median() const;

    /**
    * Median of elements
    * @return Median of elements
    */
    VectorT<ElementType> CircularMean(const Ipp32s& size);

    /**
    * Maximum of elements
    * @return Max of elements
    * @example basicvector_vector_maxmin.cpp
    */
    inline ElementType Max() const;

    /**
    * Return the Index of the maximum of elements
    * @return index of maximum
    */
    inline int MaxIndex() const;

    /**
    * Minimum of elements
    * @return Min of elements
    */
    inline ElementType Min() const;

    /**
    * Return the Index of the mimimum of elements
    * @return index of mimimum
    */
    inline int MinIndex() const;

    /**
    * StdDev of elements
    * @return StdDev of elements
    */
    inline ElementType StdDev() const;

    /**
    * \}
    * @name sorting
    * \{
    */

    /**
    * Sort elements in an ascending order.
    * @example basicvector_vector_sort.cpp
    */
    inline void sortAscend();

    /**
    * @brief sort elements in an descending order.
    */
    inline void sortDescend();
	 
    /**
    * @brief sort elements in an descending order.
    */
    inline void sortDescend(VectorT<int> & permutation);

    /**
    * \}
    * @name norms
    * \{
    */

    /**
    * computes the infinity norm of the vector (maximum norm)
    * @return infinity vector norm
    * @example basicvector_vector_norm.cpp
    */
    inline ElementType normInf() const;

    /**
    * computes the L1 norm of the vector (manhattan norm)
    * @return L1 vector norm
    */
    inline ElementType normL1() const;

    /**
    * computes the L2 norm of the vector (euclidean norm)
    * @return L2 vector norm
    */
    inline ElementType normL2() const;

    /**
    * \}
    * @name normalization
    * \{
    */

    /**
    * Normalize this vector with respect to the infinity norm (maximum norm).
    */
    inline void normalizeInf() {
        operator/=(normInf());
    }

    /**
    * Normalize this vector with respect to the L1 norm (manhattan norm).
    */
    inline void normalizeL1() {
        operator/=(normL1());
    }

    /**
    * Normalize this vector with respect to the L2 norm (euclidean norm).
    */
    inline void normalizeL2() {
        operator/=(normL2());
    }

    /**
    * \}
    * @name operators
    * \{
    */

    /**
    * @brief Compare \c v with \c this.
    * @pre Size of \c v and \c this must be equal
    * @param v data to compare with
    * @return true if \c v and \c this are equal
    */
    inline bool operator== (const VectorT<ElementType>& v) const;

    /**
    * @brief Compare \c v with \c this.
    * @pre Size of \c v and \c this must be equal
    * @param v data to compare with
    * @return true if \c v and \c this are not equal
    */
    inline bool operator!= (const VectorT<ElementType>& v) const;

        /**
    * @brief Copy data from \c v to \c this.
    * @param v New data
    * @return \c *this
    */
    inline VectorT<ElementType>& operator=(const VectorT<ElementType>& v);

    /**
    * @brief Set all elements to value \c element
    * @param element New value of all elements
    */
    inline VectorT<ElementType>& operator=(const ElementType& element);

    /**
    * @brief Add \c e to each element of \c this.
    * @param e value
    * @return \c *this
    * @example basicvector_vector_operator.cpp
    */
    inline VectorT<ElementType>& operator+= (const ElementType& e);

    /**
    * @brief Subtract \c e from each element of \c this.
    * @param e value
    * @return \c *this
    */
    inline VectorT<ElementType>& operator-= (const ElementType& e);

    /**
    * @brief Multiply each element of \c this with \c e.
    * @param e value
    * @return \c *this
    */
    inline VectorT<ElementType>& operator*= (const ElementType& e);

    /**
    * @brief Divide each element of \c this through \c e.
    * @param e value
    * @return \c *this
    */
    inline VectorT<ElementType>& operator/= (const ElementType& e);

    /**
    * @brief Add \c v to \c this.
    * @pre Size of \c v and \c this must be equal
    * @param v New data
    * @return \c *this
    */
    inline VectorT<ElementType>& operator+= (const VectorT<ElementType>& v);

    /**
    * @brief Subtract \c v from \c this.
    * @pre Size of \c v and \c this must be equal
    * @param v New data
    * @return \c *this
    */
    inline VectorT<ElementType>& operator-= (const VectorT<ElementType>& v);

    /**
    * @brief Multiplicate elementwise \c v to \c this.
    * @pre Size of \c v and \c this must be equal
    * @param v New data
    * @return \c *this
    */
    inline VectorT<ElementType>& operator*= (const VectorT<ElementType>& v);

    /**
    * @brief Divide elementwise \c v from \c this.
    * @pre Size of \c v and \c this must be equal
    * @param v New data
    * @return \c *this
    */
    inline VectorT<ElementType>& operator/= (const VectorT<ElementType>& v);

    /**
    * \}
    * @name random vector data initialization
    * \{
    */

    /**
    * @brief Create a vector with uniform distributed values.
    * @param size vector length
    * @param min minimum value
    * @param max maximum value
    * @param seed seed for random generator
    * @return a vector with uniform distributed values
    */
    inline static VectorT<ElementType> UniformRandom(const size_t size, ElementType min,
                                                     ElementType max, unsigned int seed);

	/**
    * @brief Create a vector with uniform distributed values with the global seed and 
	* without using IPP 
    * @param size vector length
    * @param min minimum value
    * @param max maximum value
    * @return a vector with uniform distributed values
    */
    inline static VectorT<ElementType> UniformRandom(const size_t size, ElementType min,
                                                     ElementType max);

    /**
    * @brief Create a vector with Gaussian distributed values using IPP if available.
	* Note: IPP seems to be not as robust as the standard Box-Muller method implemented
	* in randGaussDouble. To use this method you can run GaussRandom without a seed
	* and set the seed manually with initRand(true, seed) from numerictools.
    * @param size vector length
    * @param mean  mean of Gaussian distribution
    * @param stdev standard derivation of Gaussian distribution
    * @param seed seed for random generator
    * @return a vector with Gaussian distributed values
    */
    inline static VectorT<ElementType> GaussRandom(const size_t size, ElementType mean,
                                                   ElementType stdev, unsigned int seed);

	/**
    * @brief Create a vector with Gaussian distributed values without using the IPP function.
	* Set the seed manually with initRand (numerictools).
    * @param size vector length
    * @param mean  mean of Gaussian distribution
    * @param stdev standard derivation of Gaussian distribution
    * @return a vector with Gaussian distributed values
    */
    inline static VectorT<ElementType> GaussRandom(const size_t size, ElementType mean,
                                                   ElementType stdev);

    /**
    * \}
    * @name math functions
    * \{
    */

    /**
    * Matrix Vector multiplication: this = a^{T if atranspose} * v
    * The formats of this, a and v must be consistent.
    * If this is empty (size 0x0), it will be resize.
    * @param a matrix to multiply
    * @param v vector to multiply
    * @param atranspose use a.transpose() instead of a
    * @throw Exception if formats are inconsistent
    * @example basicvector_vector_multiply.cpp
    */
    void multiply(const MatrixT<ElementType>& a,
                    const VectorT<ElementType>& v,
                    bool atranspose=false);

    /**
    * Vector Matrix  multiplication: this = v * a^{T if atranspose}
    * The formats of this, v and a must be consistent.
    * If this is empty (size 0x0), it will be resize.
    * @param v vector to multiply
    * @param a matrix to multiply
    * @param atranspose use a.transpose() instead of a
    * @throw Exception if formats are inconsistent
    */
    void multiply(const VectorT<ElementType>& v,
                    const MatrixT<ElementType>& a,
                    bool atranspose=false);

    /**
    * Matrix Vector multiplication: this = a^{T if atranspose} * v
    * The formats of this, a and v must be consistent.
    * If this is empty (size 0x0), it will be resize.
    * @param a matrix to multiply
    * @param v vector to multiply
    * @param atranspose use a.transpose() instead of a
    * @throw Exception if formats are inconsistent
    */
    void multiply(const RowMatrixT<ElementType>& a,
                    const VectorT<ElementType>& v,
                    bool atranspose=false);

    /**
    * Vector Matrix  multiplication: this = v * a^{T if atranspose}
    * The formats of this, v and a must be consistent.
    * If this is empty (size 0x0), it will be resize.
    * @param v vector to multiply
    * @param a matrix to multiply
    * @param atranspose use a.transpose() instead of a
    * @throw Exception if formats are inconsistent
    */
    void multiply(const VectorT<ElementType>& v,
                    const RowMatrixT<ElementType>& a,
                    bool atranspose=false);

    /**
    * Return a matrix (size: size() x size()) representing
    * the cross product of this vector with another vector:
    * "result * v = this x v".
    */
    MatrixT<ElementType> toCrossProductMatrix() const;

    /**
    * \}
    * @name shift functions
    * \{
    */

    /**
    * left shift a vector circular by \c b bins
    * @param b number of bins
    * @return left shifted vector
    */
    VectorT<ElementType> LShiftCircular(const uint b);

    /**
    * left shift a vector circular by \c b bins (inplace)
    * @param b number of bins
    */
    void LShiftCircularInplace(const uint b);

    /**
    * right shift a vector circular by \c b bins
    * @param b number of bins
    * @return left shifted vector
    */
    VectorT<ElementType> RShiftCircular(const uint b);

    /**
    * right shift a vector circular by \c b bins (inplace)
    * @param b number of bins
    */
    void RShiftCircularInplace(const uint b);


    /**
    * \}
    * @name other functions
    * \{
    */

    /**
    * @brief Change the number of VectorT elements
    * @param size New size of the \c VectorT
    * @throw std::runtime_error if using external storage and \c size > \c size()
    * @note Changing the size of the vector invalidates all iterators
    *       and pointers held to the data. resize(0) empties the vector.
    */
    inline void resize(size_t size);

    /**
    * @brief set vector size to zero and free memory
    */
    inline void clear(void);

    /**
    * @brief Reverse the order of the VectorT elements.
    */
    inline void flip();

    /**
    * @brief Set all elements to value \c element
    * @param element New value of all elements
    */
    inline void set(const ElementType& element) {
        *this = element;
    }

    /**
    * @brief replace all elements by their absolute value
    */
    inline void absInplace();

    /**
    * @brief return a vector with the absolute values of this vector
    */
    inline VectorT<ElementType> abs() const;

    /**
    * @brief Returns 'true' if the memory is allocated externally
    * @return true if external storage
    */
    inline bool isExternal() const { return externalStorage; }

    /**
     * @brief Compare \c v with \c this.
     * @pre Size of \c v and \c this must be equal
     * @param a data to compare with
     * @param threshold difference of each entry which can be neglected
     * @return true if \c v and \c this are equal
     */
    inline bool isEqual(const VectorT<ElementType> &v, ElementType threshold=static_cast<ElementType>(0)) const;

    /**
    * @brief convert to a STL vector
    *
    * @return copy of the vector as a STL vector
    */
  	inline std::vector<ElementType> std_vector () const;

    /**
    * @brief convert the vector to a really simple hash value
    *
    * @return hash value
    */
    unsigned long getHashValue () const;

    #ifdef NICE_USELIB_LINAL

    /**
    * \}
    * @name LinAl functions
    * \{
    */

    /**
    * Copy data form \c v.
    */
    explicit VectorT(const LinAl::VectorC<ElementType>& v);

    /**
    * @brief Copy data from \c v to \c this.
    * @param v New data
    * @return \c *this
    */
    inline VectorT<ElementType>& operator=(const LinAl::VectorCC<ElementType>& v);

    /**
    * Shallow copy data to LinAl vector
    */
    inline LinAl::VectorCC<ElementType> linalCol() {
        return LinAl::VectorCC<ElementType>(data, size(), true);
    }

    /**
    * Copy data to LinAl vector
    */
    inline LinAl::VectorCC<ElementType> linalCol() const {
        return LinAl::VectorCC<ElementType>(data, size());
    }

    /**
    * Shallow copy data to LinAl vector
    */
    inline LinAl::VectorCR<ElementType> linalRow() {
        return LinAl::VectorCR<ElementType>(data, size(), true);
    }

    /**
    * Copy data to LinAl vector
    */
    inline LinAl::VectorCR<ElementType> linalRow() const {
        return LinAl::VectorCR<ElementType>(data, size());
    }
#endif // NICE_USELIB_LINAL

    /**
    * \}
    */

protected:
  /**
   * Are we using external storage?
   */
  bool externalStorage;

  /**
   * Const pointer to the data.
   */
  const ElementType* constData;

  /**
   * Pointer to the data.
   * @note This has to point to the same adress as constData!
   *       (NULL is only const data is available)
   */
  ElementType* data;

  /**
   * Size of the vector
   */
  size_t dataSize;

  void setDataPointer(ElementType* _data, size_t _size,
                             bool _externalStorage) {
    data = _data;
    constData = _data;
    dataSize = _size;
    externalStorage = _externalStorage;
  }

  void setConstDataPointer(const ElementType* _data, size_t _size) {
    data = NULL;
    constData = _data;
    dataSize = _size;
    externalStorage = true;
  }
};

template <class ElementType>
inline std::istream&
operator >> (std::istream& input, VectorT<ElementType>& v) {
  VectorT<ElementType> result(input);
  v.resize(result.size());
  v = result;
  return input;
}

template<class ElementType>
inline std::ostream&
operator << (std::ostream& output, const VectorT<ElementType>& v) {
  output << v.size() << " < ";
  for (size_t i = 0; i < v.size(); i++) {
    output << v[i] << " ";
  }
  output << ">";
  return output;
}

//#ifdef NICE_USELIB_ZLIB
template <class Tp>
inline NICE::ibinstream& operator>>(NICE::ibinstream& s, VectorT<Tp> &r)
{
  unsigned int size;
  s >> size;
  r.resize(size);
  typename VectorT<Tp>::iterator it=r.begin();
  for(;it!=r.end();it++)
    s>>*it;
  return s;
}

template <class Tp>
inline NICE::obinstream& operator<<(NICE::obinstream& s, const VectorT<Tp>& r)
{
  unsigned int size=r.size();
  s<<size;
  typename VectorT<Tp>::const_iterator it=r.begin();
  for(;it!=r.end();it++)
    s << *it;
  return s;
}
//#endif

typedef VectorT<bool>   BoolVector;
typedef VectorT<char>   CharVector;
typedef VectorT<int>    IntVector;
typedef VectorT<float>  FloatVector;
typedef VectorT<double> Vector;

// additional operators

/** vector addition */
template <class Tp>
inline VectorT<Tp> operator+ ( const VectorT<Tp> & x, const VectorT<Tp> & y )
{
    VectorT<Tp> dst (x);
    dst += y;
    return dst;
}

/** vector substratction */
template <class Tp>
inline VectorT<Tp> operator- ( const VectorT<Tp> & x, const VectorT<Tp> & y )
{
    VectorT<Tp> dst (x);
    dst -= y;
    return dst;
}

/** multiply a vector with a scalar */
template <class Tp>
inline VectorT<Tp> operator* ( const VectorT<Tp> & x, double s )
{
    VectorT<Tp> dst (x);
    dst *= s;
    return dst;
}

/** multiply a vector with a scalar */
template <class Tp>
inline VectorT<Tp> operator* ( double s, const VectorT<Tp> & x )
{
    VectorT<Tp> dst (x);
    dst *= s;
    return dst;
}


} // namespace

#include "core/vector/MatrixT.h"
#include "core/vector/RowMatrixT.h"

//#ifdef __GNUC__
#include "core/vector/VectorT.tcc"
//#endif

#endif // _EVECTOR_BASICVECTOR_H

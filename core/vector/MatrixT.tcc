#include <string>
#include <sstream>
#include <stdexcept>
#include <limits>

#include "core/basics/Exception.h"
#define _THROW_EMatrix(string) fthrow(Exception, string)
#include "core/vector/ippwrapper.h"
#include "core/vector/MatrixT.h"
#include "vector"
#include <algorithm>

namespace NICE
{

	template<typename ElementType>
	inline MatrixT<ElementType>::MatrixT()
	{
		setDataPointer(NULL, 0, 0, false);
	}

	template<typename ElementType>
	inline MatrixT<ElementType>::MatrixT(const size_t rows, const size_t cols)
	{
		setDataPointer(new ElementType[rows * cols], rows, cols, false);
	}

#ifdef NICE_USELIB_LINAL
	template<typename ElementType>
	inline MatrixT<ElementType>::MatrixT(const LinAl::Matrix<ElementType>& m)
	{
		setDataPointer(new ElementType[m.rows() * m.cols()],
					   m.rows(), m.cols(), false);
		for (unsigned int j = 0; j < cols(); j++)
		{
			for (unsigned int i = 0; i < rows(); i++)
			{
				(*this)(i, j) = m(i, j);
			}
		}
	}

	template<typename ElementType>
	inline MatrixT<ElementType>&
	MatrixT<ElementType>::operator=(const LinAl::Matrix<ElementType>& v)
	{
		if (rows() * cols() == 0 && !externalStorage && getDataPointer() == NULL)
		{
			setDataPointer(new ElementType[v.rows() * v.cols()],
				 v.rows(), v.cols(), false);
		}
		else if (this->rows() != (unsigned int) v.rows()
				 || this->cols() != (unsigned int) v.cols())
		{
			this->resize(v.rows(), v.cols());
		}
		for (unsigned int j = 0; j < cols(); j++)
		{
			for (unsigned int i = 0; i < rows(); i++)
			{
				(*this)(i, j) = v(i, j);
			}
		}
		return *this;
	}
#endif // NICE_USELIB_LINAL

	template<typename ElementType>
	inline MatrixT<ElementType>::MatrixT(const size_t rows, const size_t cols,
										 const ElementType& element)
	{
		setDataPointer(new ElementType[rows * cols], rows, cols, false);
		ippsSet(element, getDataPointer(), rows * cols);
	}

	template<typename ElementType>
	inline MatrixT<ElementType>::MatrixT(const ElementType* _data,
										 const size_t rows, const size_t cols)
	{
		setDataPointer(new ElementType[rows * cols], rows, cols, false);
		ippsCopy(_data, getDataPointer(), rows * cols);
	}

	template<typename ElementType>
	inline MatrixT<ElementType>::MatrixT(ElementType* _data,
										 const size_t rows, const size_t cols,
										 const MatrixBase::Mode mode)
	{
		switch (mode)
		{
			case external:
				setDataPointer(_data, rows, cols, true);
				break;
			case copy:
				setDataPointer(new ElementType[rows * cols], rows, cols, false);
				ippsCopy(_data, getDataPointer(), rows * cols);
				break;
			default:
				setDataPointer(NULL, 0, 0, false);
				_THROW_EMatrix("Unknown Mode-enum.");
		}
	}

//template <class ElementType>
//inline MatrixT<ElementType>::MatrixT(std::istream& input) {
//  input >> dataSize;
//  setDataPointer(new ElementType[dataSize], dataSize, false);
//
//  char c;
//  input >> c;
//  if (c != '<') {
//    _THROW_EMatrix("syntax error reading MatrixT");
//  }
//
//  unsigned int i = -1;
//  while (true) {
//    std::string s;
//    input >> s;
//    if (s == ">") {
//      break;
//    }
//    i++;
//    if (i > dataSize) {
//      _THROW_EMatrix("syntax error reading MatrixT");
//    }
//    std::stringstream st(s);
//    ElementType x;
//    st >> x;
//    getDataPointer()[i] = x;
//  }
//}

	template<typename ElementType>
	MatrixT<ElementType>::MatrixT(const MatrixT<ElementType>& v)
	{
		setDataPointer(new ElementType[v.rows() * v.cols()],
					   v.rows(), v.cols(), false);
		ippsCopy(v.getDataPointer(), getDataPointer(), v.rows() * v.cols());
	}

	template<typename ElementType>
	inline MatrixT<ElementType>::~MatrixT()
	{
		if (!externalStorage && data != NULL)
		{
			delete[] data;
			setDataPointer(NULL, 0, 0, false);
		}
	}

	template<typename ElementType>
	void MatrixT<ElementType>::resize(size_t _rows, size_t _cols)
	{
		if (rows() * cols() == _rows * _cols)
		{
			m_rows = _rows;
			m_cols = _cols;
			return;
		}

		if (externalStorage)
		{
			if (_rows * _cols < rows() * cols())
			{
				m_rows = _rows;
				m_cols = _cols;
				return;
			}
			_THROW_EMatrix("Cannot resize MatrixT (external storage used)");
		}

		if (getDataPointer() != NULL)
		{
			size_t oldRows = rows();
			size_t oldCols = cols();
			ElementType* tmp = getDataPointer();
			setDataPointer(new ElementType[_rows * _cols], _rows, _cols, false);
			ippsCopy(tmp, getDataPointer(), std::min(_rows * _cols, oldRows * oldCols));
			delete[] tmp;
		}
		else
		{
			setDataPointer(new ElementType[_rows * _cols], _rows, _cols, false);
		}
	}

	template<class ElementType>
	inline const MatrixT<ElementType>*
	MatrixT<ElementType>::createConst(const ElementType* _data,
									  const size_t rows, const size_t cols)
	{
		MatrixT<ElementType>* result = new MatrixT<ElementType>;
		result->setConstDataPointer(_data, rows, cols);
		return result;
	}

	template<class ElementType>
	inline const VectorT<ElementType> MatrixT<ElementType>::getColumnRef(uint i) const
	{
		const VectorT<ElementType> column(constData[i * rows()], rows(), VectorBase::external);
		return column;
	}

	template<class ElementType>
	inline VectorT<ElementType> MatrixT<ElementType>::getColumnRef(uint i)
	{
		VectorT<ElementType> column(data + (i * rows()), rows(), VectorBase::external);
		return column;
	}

	template<class ElementType>
	inline VectorT<ElementType> MatrixT<ElementType>::getColumn(uint i) const
	{
		VectorT<ElementType> column(constData + i * rows(), rows());
		return column;
	}

	template<class ElementType>
	inline VectorT<ElementType> MatrixT<ElementType>::getRow(uint i) const
	{
		VectorT<ElementType> row(cols());
		for (uint j = 0;j < cols();j++)
		{
			row(j) = (*this)(i, j);
		}
		return row;
	}

	template<class ElementType>
	inline ElementType MatrixT<ElementType>::Max() const
	{
		ElementType max = - std::numeric_limits<ElementType>::max();
		for (uint i = 0 ; i < rows(); i++)
			for (uint j = 0 ; j < cols(); j++)
				if ((*this)(i, j) > max)
					max = (*this)(i, j);
		return max;
	}

	template<class ElementType>
	inline ElementType MatrixT<ElementType>::Min() const
	{
		ElementType min = std::numeric_limits<ElementType>::max();
		for (uint i = 0 ; i < rows(); i++)
			for (uint j = 0 ; j < cols(); j++)
				if ((*this)(i, j) < min)
					min = (*this)(i, j);
		return min;
	}

	template<class ElementType>
	inline bool
	MatrixT<ElementType>::operator==(const MatrixT<ElementType>& v) const
	{
		if (this->rows() != v.rows() || this->cols() != v.cols())
		{
			throw std::invalid_argument(
				"MatrixT::operator==(): v.rows/cols() != rows/cols()");
		}
		else if (rows() == 0 || cols() == 0)
		{
			return true;
		}
		for (unsigned int j = 0; j < cols(); j++)
		{
			for (unsigned int i = 0; i < rows(); i++)
			{
				if (!(operator()(i, j) == v(i, j)))
				{
					return false;
				}
			}
		}
		return true;
	}

	template<class ElementType>
	inline bool
	MatrixT<ElementType>::operator!=(const MatrixT<ElementType>& v) const
	{
		if (this->rows() != v.rows() || this->cols() != v.cols())
		{
			throw std::invalid_argument(
				"MatrixT::operator==(): v.rows/cols() != rows/cols()");
		}
		else if (rows() == 0 || cols() == 0)
		{
			return false;
		}
		for (unsigned int j = 0; j < cols(); j++)
		{
			for (unsigned int i = 0; i < rows(); i++)
			{
				if (!(operator()(i, j) == v(i, j)))
				{
					return true;
				}
			}
		}
		return false;
	}


	template<typename ElementType>
	inline MatrixT<ElementType>&
	MatrixT<ElementType>::operator=(const MatrixT<ElementType>& v)
	{
		if (rows() * cols() == 0 && !externalStorage && getDataPointer() == NULL)
		{
			setDataPointer(new ElementType[v.rows() * v.cols()],
						   v.rows(), v.cols(), false);
		}
		else if (this->rows() != v.rows() || this->cols() != v.cols())
		{
			this->resize(v.rows(), v.cols());
		}
		ippsCopy(v.getDataPointer(), getDataPointer(), v.rows() * v.cols());
		return *this;
	}

	template<typename ElementType>
	inline MatrixT<ElementType>&
	MatrixT<ElementType>::operator=(const ElementType& element)
	{
		ippsSet(element, getDataPointer(), this->rows() * this->cols());
		return *this;
	}

	template<typename ElementType>
	void MatrixT<ElementType>::transposeInplace()
	{
		if (rows() != cols())
		{
			_THROW_EMatrix("transposeInplace(): matrix has to be quadratic");
		}

		for (unsigned int j = 1; j < cols(); j++)
		{
			for (unsigned int i = 0; i < j; i++)
			{
				std::swap((*this)(i, j), (*this)(j, i));
			}
		}
	}

	template<typename ElementType>
	MatrixT<ElementType> MatrixT<ElementType>::transpose() const
	{
		MatrixT<ElementType> result(cols(), rows());
// ifdef NICE_USELIB_IPP
		size_t tsize = sizeof(ElementType);
		IppStatus ret = ippmTranspose_m(getDataPointer(), tsize, rows() * tsize,
										cols(), rows(), result.getDataPointer(),
										tsize, cols() * tsize);
		if (ret != ippStsNoErr)
		{
			_THROW_EMatrix(ippGetStatusString(ret));
		}
// #else
//   for (unsigned int j = 0; j < cols(); j++) {
//     for (unsigned int i = 0; i < rows(); i++) {
//       result(j, i) = (*this)(i, j);
//     }
//   }
// #endif
		return result;
	}

#define _DEFINE_EMATRIX_AUGMENTED_ASSIGNMENT(_Op, _Name)               \
template<class ElementType>                                            \
inline MatrixT<ElementType> &                                          \
MatrixT<ElementType>::operator _Op##= (const ElementType& v) {         \
  ipps##_Name##C_I(v, getDataPointer(), this->rows() * this->cols());  \
  return *this;                                                        \
}

	_DEFINE_EMATRIX_AUGMENTED_ASSIGNMENT( + , Add)
	_DEFINE_EMATRIX_AUGMENTED_ASSIGNMENT(-, Sub)
	_DEFINE_EMATRIX_AUGMENTED_ASSIGNMENT(*, Mul)
	_DEFINE_EMATRIX_AUGMENTED_ASSIGNMENT( / , Div)

#define _DEFINE_EMATRIX_ASSIGNMENT(_Op, _Name)                            \
template<class ElementType>                                               \
inline MatrixT<ElementType> &                                             \
MatrixT<ElementType>::operator _Op##= (const MatrixT<ElementType>& v) {   \
  if(this->rows() != v.rows() || this->cols() != v. cols())               \
     _THROW_EMatrix("MatrixT: different data size");                      \
  ipps##_Name##_I(v.getDataPointer(), getDataPointer(),                   \
                  this->rows() * this->cols());                           \
  return *this;                                                           \
}

	_DEFINE_EMATRIX_ASSIGNMENT( + , Add)
	_DEFINE_EMATRIX_ASSIGNMENT(-, Sub)
//_DEFINE_EMATRIX_ASSIGNMENT(*, Mul)
//_DEFINE_EMATRIX_ASSIGNMENT(/, Div)

	template<typename ElementType>
	void MatrixT<ElementType>::setBlock(uint top, uint left,
										MatrixT<ElementType> m)
	{
		if (rows() < m.rows() + top || cols() < m.cols() + left)
		{
			_THROW_EMatrix("Matrix setBlock: target matrix too small.");
		}

		// FIXME use IPP?
		for (unsigned int j = 0; j < m.cols(); j++)
		{
			for (unsigned int i = 0; i < m.rows(); i++)
			{
				(*this)(i + top, j + left) = m(i, j);
			}
		}
	}
	
  template<typename ElementType>
  void MatrixT<ElementType>::setRow(const uint & row, const NICE::VectorT<ElementType> & v)
  {
    if (cols() < v.size() )
    {
      _THROW_EMatrix("Matrix setRow: target matrix too small.");
    }
    
    if (row >= rows() )
    {
      _THROW_EMatrix("Matrix setRow: row does not specify a proper row index.");
    }
    
    // FIXME use IPP?
    for (unsigned int j = 0; j < v.size(); j++)
    {
      (*this)(row, j) = v[j];
    }
  }

  template<typename ElementType>
  void MatrixT<ElementType>::exchangeRows(const uint & r1, const uint & r2)
  {
    //is r1 a proper row index?
    if ( r1 > this->rows() )
    {
      _THROW_EMatrix("Matrix exchangeRows: r1 does not specify a proper row index.");
    }   
    
    //is r2 a proper row index?
    if ( r2 > this->rows() )
    {
      _THROW_EMatrix("Matrix exchangeRows: r2 does not specify a proper row index.");
    }      
    
    NICE::VectorT<ElementType> tmp (this->getRow(r1));
    this->setRow(r1, this->getRow(r2));
    this->setRow(r1, tmp);   
  }

	template<typename ElementType>
	void MatrixT<ElementType>::addToBlock(uint top, uint left,
										  MatrixT<ElementType> m)
	{
		if (rows() < m.rows() + top || cols() < m.cols() + left)
		{
			_THROW_EMatrix("Matrix setBlock: target matrix too small.");
		}

		// FIXME use IPP?
		for (unsigned int j = 0; j < m.cols(); j++)
		{
			for (unsigned int i = 0; i < m.rows(); i++)
			{
				(*this)(i + top, j + left) += m(i, j);
			}
		}
	}

	template<typename ElementType>
	void MatrixT<ElementType>::addIdentity(double scale)
	{
		unsigned int m = std::min(rows(), cols());
		for (unsigned int i = 0; i < m; i++)
		{
			(*this)(i, i) += scale;
		}
	}
  
  template<typename ElementType>
  void MatrixT<ElementType>::addDiagonal( const VectorT<ElementType> & D )
  {
    unsigned int m = std::min(rows(), cols());
    if ( D.size() != m ) 
			_THROW_EMatrix("Matrix addDiagonal: inconsistent size of vector and diagonal elements.");

		for (unsigned int i = 0; i < m; i++)
		{
			(*this)(i, i) += D[i];
		}
  }
	
  template<typename ElementType>	
  void MatrixT<ElementType>::addScaledMatrix( const ElementType & scale , const MatrixT<ElementType>& m)
  {
    if ( (rows() != m.rows()) || (cols() != m.cols()) )
    {
      _THROW_EMatrix("Matrix addScaledMatrix: target matrix not of the same size.");
    }
    
    for (unsigned int j = 0; j < m.cols(); j++)
    {
      for (unsigned int i = 0; i < m.rows(); i++)
      {
        (*this)(i, j) += scale * m(i, j);
      }
    }    
  }

	template<typename ElementType>
	void MatrixT<ElementType>::tensorProduct(const VectorT<ElementType>& v,
			const VectorT<ElementType>& w)
	{
		if (v.size() != w.size())
		{
			_THROW_EMatrix("Matrix tensorProduct: inconsistent sizes of factors.");
		}
		if (rows() == 0 && cols() == 0)
		{
			resize(v.size(), w.size());
		}
		if (rows() != v.size() || cols() != w.size())
		{
			_THROW_EMatrix("Matrix multiplication: inconsistent size of result matrix.");
		}

		// FIXME use IPP?
		for (unsigned int j = 0; j < cols(); j++)
		{
			for (unsigned int i = 0; i < rows(); i++)
			{
				(*this)(i, j) = v[i] * w[j];
			}
		}
	}

	template<typename ElementType>
	void MatrixT<ElementType>::addTensorProduct(double lambda, const VectorT<ElementType>& v,
			const VectorT<ElementType>& w)
	{
		if (v.size() != w.size())
		{
			_THROW_EMatrix("Matrix tensorProduct: inconsistent sizes of factors.");
		}
		if (rows() == 0 && cols() == 0)
		{
			resize(v.size(), w.size());
			set(0.0);
		}
		if (rows() != v.size() || cols() != w.size())
		{
			_THROW_EMatrix("Matrix multiplication: inconsistent size of result matrix.");
		}

		for (unsigned int j = 0; j < cols(); j++)
		{
			for (unsigned int i = 0; i < rows(); i++)
			{
				(*this)(i, j) += lambda * v[i] * w[j];
			}
		}
	}

	template<typename ElementType>
	void MatrixT<ElementType>::multiply(const MatrixT<ElementType>& a,
										const MatrixT<ElementType>& b,
										bool atranspose,
										bool btranspose)
	{
		if (this == &a || this == &b)
		{
			_THROW_EMatrix(
				"Matrix multiplication: a and b must not be the same object as this.");
		}

		size_t arows, acols;
		if (atranspose)
		{
			arows = a.cols();
			acols = a.rows();
		}
		else
		{
			arows = a.rows();
			acols = a.cols();
		}

		size_t brows, bcols;
		if (btranspose)
		{
			brows = b.cols();
			bcols = b.rows();
		}
		else
		{
			brows = b.rows();
			bcols = b.cols();
		}

		if (acols != brows)
		{
			_THROW_EMatrix("Matrix multiplication: inconsistent sizes of factors.");
		}
		if (rows() == 0 && cols() == 0)
		{
			resize(arows, bcols);
		}
		if (rows() != arows || cols() != bcols)
		{
			_THROW_EMatrix("Matrix multiplication: inconsistent size of result matrix.");
		}

#ifdef NICE_USELIB_IPP
		size_t tsize = sizeof(ElementType);
		IppStatus ret;
		if (atranspose)
		{
			if (btranspose)
			{
				ret = ippmMul_tt(b.getDataPointer(), b.rows() * tsize, tsize, b.rows(), b.cols(),
								 a.getDataPointer(), a.rows() * tsize, tsize, a.rows(), a.cols(),
								 this->getDataPointer(), rows() * tsize, tsize);
			}
			else
			{
				ret = ippmMul_mt(b.getDataPointer(), b.rows() * tsize, tsize, b.rows(), b.cols(),
								 a.getDataPointer(), a.rows() * tsize, tsize, a.rows(), a.cols(),
								 this->getDataPointer(), rows() * tsize, tsize);
			}
		}
		else
		{
			if (btranspose)
			{
				ret = ippmMul_tm(b.getDataPointer(), b.rows() * tsize, tsize, b.rows(), b.cols(),
								 a.getDataPointer(), a.rows() * tsize, tsize, a.rows(), a.cols(),
								 this->getDataPointer(), rows() * tsize, tsize);
			}
			else
			{
				ret = ippmMul_mm(b.getDataPointer(), b.rows() * tsize, tsize, b.rows(), b.cols(),
								 a.getDataPointer(), a.rows() * tsize, tsize, a.rows(), a.cols(),
								 this->getDataPointer(), rows() * tsize, tsize);
			}
		}
		if (ret != ippStsNoErr)
			_THROW_EMatrix(ippGetStatusString(ret));
#else
		// FIXME not very efficient
		ElementType ela, elb;
		for (unsigned int j = 0; j < cols(); j++)
		{
			for (unsigned int i = 0; i < rows(); i++)
			{
				ElementType sum = ElementType(0);
				for (unsigned int k = 0; k < acols; k++)
				{
					ela = atranspose ? a(k, i) : a(i, k);
					elb = btranspose ? b(j, k) : b(k, j);
					sum += ela * elb;
				}
				(*this)(i, j) = sum;
			}
		}
#endif
	}

	template<typename ElementType>
	bool MatrixT<ElementType>::containsNaN() const
	{
		for (unsigned int c = 0; c < cols(); c++)
		{
			for (unsigned int r = 0; r < rows(); r++)
			{
				if (NICE::isNaN((*this)(r, c)))
				{
					return true;
				}
			}
		}
		return false;
	}

	template<typename ElementType>
	inline bool MatrixT<ElementType>::isEqual(const MatrixT<ElementType> &a, ElementType threshold) const
	{
		if (this->rows() != a.rows() || this->cols() != a.cols())
			_THROW_EMatrix("MatrixT: different data size");
		for (unsigned int j = 0; j < cols(); j++)
		{
			for (unsigned int i = 0; i < rows(); i++)
			{
				if (fabs((*this)(i, j) - a(i, j)) > threshold)
					return false;
			}
		}
		return true;
	}

	template<typename ElementType>
	ElementType MatrixT<ElementType>::squaredFrobeniusNorm() const
	{
		double sum = ElementType(0);
		for (unsigned int j = 0; j < cols(); j++)
		{
			for (unsigned int i = 0; i < rows(); i++)
			{
				sum += square((*this)(i, j));
			}
		}
		return static_cast<ElementType>(sum);
	}

	template<typename ElementType>
	ElementType MatrixT<ElementType>::trace() const
	{
		double sum = ElementType(0);
		for (unsigned int j = 0; j < std::min(cols(),rows()); j++)
		{
			sum += (*this)(j, j);
		}
		return static_cast<ElementType>(sum);
	}

	template<typename ElementType>
	ElementType MatrixT<ElementType>::bilinear(const VectorT<ElementType> & v) const
	{
		double sum = ElementType(0);
		if ((this->rows() != this->cols()) || (v.size() != this->rows()))
			_THROW_EMatrix("MatrixT: different data size");
		for (unsigned int j = 0; j < cols(); j++)
		{
			for (unsigned int i = 0; i < rows(); i++)
			{
				sum += (*this)(i, j) * v[i] * v[j];
			}
		}
		return static_cast<ElementType>(sum);
	}

	template<typename ElementType>
	void MatrixT<ElementType>::normalizeColumnsL1()
	{
		for (unsigned int j = 0 ; j < cols() ; j++)
		{
			ElementType sum = 0.0;
			for (unsigned int i = 0 ; i < rows() ; i++)
				sum += fabs((double)(*this)(i, j));
			if (sum > 1e-20)
				for (unsigned int i = 0 ; i < rows() ; i++)
					(*this)(i, j) /= sum;
		}
	}

	template<typename ElementType>
	void MatrixT<ElementType>::normalizeRowsL1()
	{
		for (unsigned int i = 0 ; i < rows() ; i++)
		{
			ElementType sum = 0.0;
			for (unsigned int j = 0 ; j < cols() ; j++)
				sum += fabs((double)(*this)(i, j));
			if (sum > 1e-20)
				for (unsigned int j = 0 ; j < cols() ; j++)
					(*this)(i, j) /= sum;
		}
	}

  /** get sub-matrix */
  template<class ElementType>
  MatrixT<ElementType> MatrixT<ElementType>::operator()(const uint row_tl,
                    const uint col_tl,
                    const uint row_br,
                    const uint col_br) const
  {
    if ( (row_tl>row_br+1)||(row_br>=rows())||
	       (col_tl>col_br+1)||(col_br>=cols()) ) 
      _THROW_EMatrix("MatrixT: wrong specification of sub-matrix");
    MatrixT<ElementType> tm(row_br-row_tl+1,col_br-col_tl+1);
    for (uint i=row_tl;i<=row_br;i++) 
      for (uint j=col_tl;j<=col_br;j++) {
        tm(i-row_tl,j-col_tl) = (*this)(i,j);
      }
    return tm;
  }


	/** Matrix addition */
	template<class ElementType>
	MatrixT<ElementType> operator+(const MatrixT<ElementType> & a, const MatrixT<ElementType> & b)
	{
		MatrixT<ElementType> dst(a);
		dst += b;
		return dst;
	}

	/** Matrix substraction */
	template<class ElementType>
	MatrixT<ElementType> operator-(const MatrixT<ElementType> & a, const MatrixT<ElementType> & b)
	{
		MatrixT<ElementType> dst(a);
		dst -= b;
		return dst;
	}

	/** Matrix (right) multiplication with a scalar */
	template<class ElementType>
	MatrixT<ElementType> operator*(const MatrixT<ElementType> & a, const double s)
	{
		MatrixT<ElementType> dst(a);
		dst *= s;
		return dst;
	}

	/** Matrix (left) multiplication with a scalar */
	template<class ElementType>
	MatrixT<ElementType> operator*(const double s, const MatrixT<ElementType> & a)
	{
		MatrixT<ElementType> dst(a);
		dst *= s;
		return dst;
	}

	/** Matrix multiplication with a vector */
	template<class ElementType>
	VectorT<ElementType> operator*(const MatrixT<ElementType> & a, const VectorT<ElementType> & b)
	{
		VectorT<ElementType> dst;
		dst.multiply(a, b);
		return dst;
	}

	/** Matrix multiplication with a matrix */
	template<class ElementType>
	MatrixT<ElementType> operator*(const MatrixT<ElementType> & a, const MatrixT<ElementType> & b)
	{
		MatrixT<ElementType> dst;
		dst.multiply(a, b);
		return dst;
	}
	
	template<class ElementType>
	void kroneckerProduct (const MatrixT<ElementType>& A, const MatrixT<ElementType>& B, MatrixT<ElementType>& dst)
	{
		dst.resize ( A.rows() * B.rows(), A.cols() * B.cols() );
		
		for (uint iA = 0 ; iA < A.rows(); iA++ )
			for (uint jA = 0 ; jA < A.cols(); jA++ )
				for (uint iB = 0 ; iB < B.rows(); iB++ )
					for (uint jB = 0 ; jB < B.cols(); jB++ )
						dst( iA*B.rows() + iB, jA*B.cols() + jB ) = A(iA,jA) * B(iB,jB);

	}

	template <typename T>
	void kroneckerProductMultiplication ( const MatrixT<T> & A, const MatrixT<T> & B, const Vector & x, Vector & y )
	{
		if ( x.size() != A.cols() * B.cols() )
			fthrow(Exception, "The size of matrix A and B do not fit to the size of the given vector.");

		y.resize ( A.rows() * B.rows() );

		Matrix X ( A.cols(), B.cols() );
		uint k = 0;
		for ( uint i = 0 ; i < A.cols(); i++ )
			for ( uint j = 0 ; j < B.cols(); j++,k++ )
				X(i,j) = x[k];

		// result in matrix form Y^T = (B * X^T) * A^T
		// Y = A X B^T

		Matrix Y;
		Matrix XBt;
		XBt.multiply ( X, B, false, true );
		Y.multiply ( A, XBt );

		// Y has size B.rows() and A.rows()

		k = 0;
		for ( uint i = 0 ; i < A.rows(); i++ )
			for ( uint j = 0 ; j < B.rows(); j++,k++ )
				y[k] = Y(i,j);
	}


	template <typename T>
	void blockwiseMultiplication ( const MatrixT<T> & A, uint blockSize, const Vector & x, Vector & y )
	{
		if ( x.size() != A.cols() * blockSize )
			fthrow(Exception, "The size of matrix A and the block size do not fit to the size of the given vector.");

		y.resize ( A.rows() * blockSize );

		Matrix X ( A.cols(), blockSize );
		uint k = 0;
		for ( uint i = 0 ; i < A.cols(); i++ )
			for ( uint j = 0 ; j < blockSize; j++,k++ )
				X(i,j) = x[k];

		// result in matrix form Y^T = X^T * A^T
		// Y = A X

		Matrix Y;
		Y.multiply ( A, X );

		// Y has size blockSize and A.rows()
		k = 0;
		for ( uint i = 0 ; i < A.rows(); i++ )
			for ( uint j = 0 ; j < blockSize; j++,k++ )
				y[k] = Y(i,j);
	}
	
	/**
	* @brief Delete one specified row by copying every data but of this row to a temporal storage, resizing M and assigning the tmp data to the resized matrix
	* @author Alexander Lütz
	* @date  07/10/2011
	* @param int index of col which shall be deleted (const, reference)
	*/
	template <typename T>
	void MatrixT<T>::deleteRow ( const int & index)
	{
		if ( (0 > index) || ((*this).rows() <= (uint)index))
			fthrow(Exception, "MatrixT::deleteRow -- The given index is not valid.");
		MatrixT<T> tmp((*this).rows()-1,(*this).cols());
		for (uint i = 0; i < (*this).rows(); i++)
		{
			for (uint j = 0; j < (*this).cols(); j++)
			{
				if (i < (uint) index)
				{
					tmp(i,j) = (*this)(i,j);
				} else if (i > (uint) index)
				{
					tmp(i-1,j) = (*this)(i,j);
				}
			}
		}
		(*this).resize(tmp.rows(), tmp.cols());
		(*this) = tmp;
	}
	
	/**
	* @brief Delete one specified col by copying every data but of this col to a temporal storage, resizing M and assigning the tmp data to the resized matrix
	* @author Alexander Lütz
	* @date  07/10/2011
	* @param int index of col which shall be deleted (const, reference)
	*/
	template <typename T>
	void MatrixT<T>::deleteCol ( const int & index)
	{
		if ( (0 > index) || ((*this).cols() <= (uint) index))
			fthrow(Exception, "MatrixT::deleteCol -- The given index is not valid.");
		MatrixT<T> tmp((*this).rows(),(*this).cols()-1);
		for (uint i = 0; i < (*this).rows(); i++)
		{
			for (uint j = 0; j < (*this).cols(); j++)
			{
				if (j < (uint) index)
				{
					tmp(i,j) = (*this)(i,j);
				} else if (j > (uint) index)
				{
					tmp(i,j-1) = (*this)(i,j);
				}
			}
		}
		(*this).resize(tmp.rows(), tmp.cols());
		(*this) = tmp;
	}
	
	/**
	* @brief Delete multiple specified rows by copying every data but of this rows to a temporal storage, resizing M and assigning the tmp data to the resized matrix
	* @author Alexander Lütz
	* @date  07/10/2011
	* @param  std::vector<int> indices of cols which shall be deleted (not const, reference, sorted afterwards)
	*/
	//not const, because they get sorted
	template <typename T>
	void MatrixT<T>::deleteRows ( std::vector<int> & indices)
	{
		for (std::vector<int>::const_iterator it = indices.begin(); it != indices.end(); it++)
		{
			if ( (0 > *it) || ((*this).rows() <= (uint) *it))
				fthrow(Exception, "MatrixT::deleteRows -- The given indices are not valid.");
		}
		
		sort (indices.begin(), indices.begin() + indices.size());
		
		int row_counter(0);
		MatrixT<T> tmp((*this).rows()-indices.size(),(*this).cols());
		for (uint i = 0; i < (*this).rows(); i++)
		{
			for (uint j = 0; j < (*this).cols(); j++)
			{
				if (i == (uint) indices[row_counter])
				{
					row_counter++;
					break; //break inner j-loop
				}
				else
					tmp(i-row_counter,j) = (*this)(i,j);
			}
		}
		(*this).resize(tmp.rows(), tmp.cols());
		(*this) = tmp;
	}
	
	/**
	* @brief Delete multiple specified cols by copying every data but of this cols to a temporal storage, resizing M and assigning the tmp data to the resized matrix
	* @author Alexander Lütz
	* @date  07/10/2011
	* @param  std::vector<int> indices of rows which shall be deleted (not const, reference, sorted afterwards)
	*/
	//not const, because they get sorted
	template <typename T>
	void MatrixT<T>::deleteCols ( std::vector<int> & indices)
	{
		for (std::vector<int>::const_iterator it = indices.begin(); it != indices.end(); it++)
		{
			if ( (0 > *it) || ((*this).cols() <= (uint) *it))
				fthrow(Exception, "MatrixT::deleteCols -- The given indices are not valid.");
		}
		
		sort (indices.begin(), indices.begin() + indices.size());
		
		int col_counter(0);
		MatrixT<T> tmp((*this).rows(),(*this).cols()-indices.size());
		//TODO check wether this is sufficient according to the way we keep the matrices in the storage!
		for (uint j = 0; j < (*this).cols(); j++)
		{
			for (uint i = 0; i < (*this).rows(); i++)
			{
				if (j == (uint) indices[col_counter])
				{
					col_counter++;
					break; //break inner j-loop
				}
				else
					tmp(i,j-col_counter) = (*this)(i,j);
			}
		}
		(*this).resize(tmp.rows(), tmp.cols());
		(*this) = tmp;
	}
} // namespace

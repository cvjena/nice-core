/** 
* @file VVector.h
* @brief vector of vector
* @author Erik Rodner
* @date 02/15/2008
*/
#ifndef VVECTORINCLUDE
#define VVECTORINCLUDE

#include <vector>
#include <ostream>
#include "VectorT.h"
#include "MatrixT.h"
#include "core/basics/Persistent.h"



namespace NICE {

/** STL vector of NICE vectors */
class VVector : public std::vector<NICE::Vector>, public Persistent
{

    protected:
	size_t bufsize;
  bool ioUntilEndOfFile;

    public:

	/** possible file formats */
	enum {
		/** use standard NICE vector I/O */
	    FILEFORMAT_NICE = 0,
	    FILEFORMAT_LINE,
		/** write binary double values, use this for large-scale datasets */
	    FILEFORMAT_BINARY_DOUBLE,
		/** write values as unsigned char, be careful with truncation */
	    FILEFORMAT_BINARY_CHAR
	};
  
	/** simple constructor */
	VVector();
	
	VVector( const std::string & filename );
	
	/**
	 * constructor creates $count NICE::Vectors of size dim
	 * @param count number of vectors
	 * @param dim size of each Vector
	 */
	VVector( int count, int dim);
	
	/**
	 * resizes the VVector and clear everything
	 * @param count number of vectors
	 * @param dim size of each Vector
	 */
	void reSize(int count, int dim);
      
	/** simple destructor */
	virtual ~VVector();
     
	virtual void clear ();
	virtual void restore ( std::istream & is, int format = 0 );
	virtual void store ( std::ostream & os, int format = 0 ) const;

	void setBufSize ( size_t bufsize );

	void sort ( size_t index );

	/** convert this data structure to a non-dynamic nice matrix 
	 * @param dst the destination matrix (will be resized)
	 * @param rowOriented if true (std) the elements of VVector (of type NICE::Vector)
	 * are stored as rows in the resulting matrix (otherwise as columns)
	 * */
	void toMatrix ( NICE::Matrix & dst, bool rowOriented = true ) const;
  
  inline void print (std::ostream& output)
  {
    if (this->size() > 0)
    {
      output << this->size() << " x " << (*this)[0].size() << std::endl;
      for (size_t r = 0; r < this->size(); r++) {
        for (size_t c = 0; c < (*this)[r].size(); c++) {
          output << (*this)[r][c] << " ";
        }
        output << std::endl;
      }
    }
    else
    {
      output << "VVector is empty" << std::endl;
    }
  }
  
  inline void setIoUntilEndOfFile(const bool & _ioUntilEndOfFile){ ioUntilEndOfFile = _ioUntilEndOfFile;};
  inline bool getIoUntilEndOfFile(){return ioUntilEndOfFile;};
  
};


} // namespace

#endif

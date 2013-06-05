/** 
* @file VVector.h
* @brief vector of vector
* @author Erik Rodner, Alexander Freytag
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
  
    /**
   * @class VVector
   * @brief STL vector of NICE vectors
   * @author Erik Rodner, Alexander Freytag
   * @date 02/15/2008
   * @NOTE We make the inheritance of Persisent virtual, in order to allow classes to implement VVector and Persistent separately, as it is done for example in CodebookPrototypes in vislearning/features/simplefeatures
  */  

class VVector : public std::vector<NICE::Vector>, virtual public Persistent
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
  
  inline void setIoUntilEndOfFile(const bool & _ioUntilEndOfFile){ ioUntilEndOfFile = _ioUntilEndOfFile;};
  inline bool getIoUntilEndOfFile(){return ioUntilEndOfFile;};  

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
  
  /** Append another VVector to this
  * @param _2ndVec the destination matrix (will be resized)
  * @param _copyData whether to copy the actual data or just to re-direct this->end and 2ndVec.begin() (default: false, i.e., just re-direct)
  * @date 03-06-2013 (dd-mm-yyyy) 
  * @author Alexander Freytag
  * */  
  void append ( const NICE::VVector & _2ndVec, const bool & _copyData = false );
  
  /** compare a second VVector with this, return true is considered as equal
  * @param _B a second VVector
  * @param _tolerance threshold for acceptable difference in a single dimension (default: 10e-8)
  * @date 05-06-2013 (dd-mm-yyyy) 
  * @author Alexander Freytag
  * */   
  bool isEqual ( const NICE::VVector & _B, const double & _tolerance = 10e-8) ;
  
};


} // namespace

#endif

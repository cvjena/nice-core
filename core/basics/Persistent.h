#ifndef PERSISTENTINCLUDE
#define PERSISTENTINCLUDE

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

#include "core/basics/Exception.h"

namespace NICE {

DEFINE_NICE_EXCEPTION ( IOException )

 /** 
 * @class Persistent
 * @brief Persistent interface inspired by EGST
 * @author 
 */ 
 
class Persistent {

 
  public:
    // Interface specifications
    virtual void restore ( std::istream & is, int format = 0 ) = 0;
    virtual void store ( std::ostream & os, int format = 0 ) const = 0;
    virtual void clear () = 0;


    // Provided functions and overloaded stream operators
    virtual ~Persistent () {};
    
    // just to prevent senseless compiler warnings
    Persistent() {};

    inline std::ostream& operator>> ( std::ostream& os )
    {
      store ( os );
      return os;
    }

    inline std::istream& operator<< ( std::istream& is )
    {
      clear ();
      restore ( is );
      return is;
    }

    inline std::istream& operator>= ( std::istream& is )
    {
      restore ( is );
      return is;
    }

    inline std::string & operator<< ( std::string& s )
    {
      std::ostringstream os;
      store ( os );
      s = os.str();
      return s;
    }

    inline const std::string & operator>> ( const std::string & s )
    {
      std::istringstream is ( s );
      clear ();
      restore ( is );
      return s;
    }

    inline const std::string & operator>= ( const std::string & s )
    {
      std::istringstream is ( s );
      restore ( is );
      return s;
    }


    /** read */
    virtual inline void read ( const std::string& s, int format = 0 )
    {
      std::ifstream ifs ( s.c_str(), std::ios::in );

      if ( ! ifs.is_open() )
        fthrow ( IOException, "Persistent: unable to read data file " + s + " !!\n" );

      clear();
      restore ( ifs, format );

      ifs.close();
    }

    virtual inline void load ( const std::string& s, int format = 0 )
    {
      read ( s, format );
    }


    virtual inline void readWithoutOverwrite ( const std::string& s, int format = 0 )
    {
      std::ifstream ifs ( s.c_str(), std::ios::in );

      if ( ! ifs.is_open() )
        fthrow ( IOException, "Persistent: unable to read data file " + s + " !!\n" );

      restore ( ifs, format );

      ifs.close();
    }

    virtual inline void save ( const std::string& s, int format = 0 ) const
    {
      std::ofstream ofs ( s.c_str(), std::ios::out );

      if ( ! ofs.is_open() )
        fthrow ( IOException, "Persistent: unable to save data file " + s + " !!\n" );

      store ( ofs, format );

      ofs.close();
    }

    virtual inline void write ( const std::string& s, int format = 0 ) const
    {
      save ( s, format );
    }
    
    virtual inline std::string createStartTag( const std::string & s_varName ) const 
    {
      return "<" + s_varName + ">";
    }
    
    virtual inline std::string createEndTag( const std::string & s_varName ) const 
    {
      return "</" + s_varName + ">";
    }
    
    virtual inline std::string removeStartTag( const std::string & s_varName ) const 
    {
      return s_varName.substr( 1, s_varName.length() -2 );
    }
    
    virtual inline std::string removeEndTag( const std::string & s_varName ) const 
    {
      return s_varName.substr( 2, s_varName.length() -3 );
    }

    virtual inline bool isStartTag( const std::string & s_varName,  const std::string & s_matchingVarName ) const 
    {
      return (    ( s_varName.length() > 2 ) &&   // min length
                  ( s_varName.substr( 0, 1 ).compare( "<" ) == 0 ) &&  // proper beginning of a start-tag
                  ( removeStartTag(s_varName).compare(s_matchingVarName) == 0 ) // start tag matches given section name
             );
    }     
    
    virtual inline bool isEndTag( const std::string & s_varName,  const std::string & s_matchingVarName ) const 
    {
      return (    ( s_varName.length() > 3 ) &&   // min length
                  ( s_varName.substr( 0, 2 ).compare( "</" ) == 0 ) &&  // proper beginning of an end-tag
                  ( removeEndTag(s_varName).compare(s_matchingVarName) == 0 ) // end tag matches given section name
             );
    }    

};


} // namespace

#endif

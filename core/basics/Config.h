/** 
* @file Config.h
* @brief configuration mgt
* @author Erik Rodner
* @date 2006-03-12
*/
#ifndef CONFIGINCLUDE
#define CONFIGINCLUDE

#include <iostream>
#include <map>

#include <math.h>
#include <string>
#include <vector>

#include "StructuredMap.h"
#include "core/basics/Persistent.h"
  
namespace NICE {

/** @brief This class provides general configuration management. */
class Config : public NICE::Persistent
{
  public:
  	  enum {
		  CONFIG_OVERWRITE_VALUES = 0,
		  CONFIG_DO_NOT_OVERWRITE_VALUES
	  };

  protected:
      /** storing all config double values */
      StructuredMap<double> confD;
      /** storing all config integer values */
      StructuredMap<int> confI;
      /** storing all config boolean valzes */
      StructuredMap<bool> confB;
      /** storing all config strings */
      StructuredMap<std::string> confS;

      void addArgBoolean ( const std::string & section, const std::string & key );

	  /** add a setting */
	  void addKeyValuePair ( const std::string & section,
			     const std::string & key, 
			     const std::string & value );

    /** storing help text for a section/key pair */
      std::map<std::string, std::string> helpTexts;

    /** storing all aux. options (for use with argv, argc) */
	  std::vector<std::string> moreOptions;
    
    /** read until end of file fore restore (default: yes)*/
    bool ioUntilEndOfFile;

    /** stores filename the config was created from*/
    std::string m_sConfigFilename;
  public:

      /** simplest constructor, create an empty config */
      Config ();

      /** simple constructor
	  @param configfn config file name */
      Config( const std::string & configfn );
      
      /** read config data from arguments 
	  @param argc number of arguments
	  @param argv arguments */
      Config ( int argc, 
	       char **argv );

	  /** copy constructor */
	  Config ( const Config & conf );

      /** simple destructor */
      virtual ~Config();

      /** get string value or abort the whole
	  program when no value is given
	  @param key name of the variable
      */
      std::string gS(const std::string & key) const;

      /** get string value or abort the whole program
	  when no value is given 
	  @param block name of the block 
	  @param key name of the variable
      */
      std::string gS(const std::string & block, const std::string & key) const;

      /** get string value, if non-existant its standard
          value is used
	  @param block name of the block 
	  @param key name of the variable
	  @param defv default value of the variable
     */
      virtual std::string gS(const std::string & block, const std::string & key, const std::string & defv) const;

      /** */
      virtual double gD(const std::string & key) const;
      virtual double gD(const std::string & block, const std::string & key) const;
      virtual double gD(const std::string & block, const std::string & key, const double defv) const;
     
      virtual int gI(const std::string & key) const;
      virtual int gI(const std::string & block, const std::string & key) const;
      virtual int gI(const std::string & block, const std::string & key, const int defv) const;
 
      virtual bool gB(const std::string & key) const;
      virtual bool gB(const std::string & block, const std::string & key) const;
      virtual bool gB(const std::string & block, const std::string & key, const bool defv) const;
      /** } */

      void getAllS ( const std::string & block, std::map< std::string, std::string > & list ) const; 
      void getAllD ( const std::string & block, std::map< std::string, double> & list ) const; 
      void getAllI ( const std::string & block, std::map< std::string, int > & list ) const; 
      void getAllB ( const std::string & block, std::map< std::string, bool > & list ) const; 

      void getAllBlocks ( std::set< std::string > & list ) const;
	  
	  /** set values */
      void sD(const std::string & block, const std::string & key, const double defv);
      void sI(const std::string & block, const std::string & key, const int defv);
      void sB(const std::string & block, const std::string & key, const bool defv);
      void sS(const std::string & block, const std::string & key, const std::string & defv);
	  

      /** read values from arguments 
	  @param argc number of arguments
	  @param argv list c-strings as provided by main-functions
      */
      void readFromArguments ( int argc, char **argv );

      /** check whether a key exists
	  @param block block of the variable
	  @param key name of the variable
      */
      bool keyExists ( const std::string & block, const std::string & key ) const;

      /** returns the filename the config was created by*/
      std::string getFilename() const{ return m_sConfigFilename;}

      /**
       * @brief Returns the given filename as an absolute path relative to this config file' location
       *
       * If p_Filename is not a relative path, then the filepath is alread absolute and just return that!
       *
       * @param p_Filename filename being relative or absolute
       * @return absolute filename
       */
      std::string getAbsoluteFilenameRelativeToThisConfig(const std::string &p_Filename) const;

      /** add a help text */
      void addHelp ( const std::string & block, const std::string & key,
		     const std::string & helpText );

      /** get help text */
      std::string help ( const std::string & block, const std::string & key ) const;

      /** write all values of the config */
	  void store (std::ostream & os, int format = 0) const;

	  /** read config values from a stream
	  @param is input stream
	  @param format can be CONFIG_DO_NOT_OVERWRITE_VALUES or CONFIG_OVERWRITE_VALUES
      */
	  void restore (std::istream & is, int format = 0);

	  /** clear all values */
	  void clear ();

	  /** get more options (command line arguments not covered by config values */
	  const std::vector<std::string> & getMoreOptions() { return moreOptions; };
    
    /** set the flag wether we restore a config and read until end of file or until a precise statement*/
    void setIoUntilEndOfFile(const bool & _ioUntilEndOfFile) { ioUntilEndOfFile = _ioUntilEndOfFile;};
	  
};


} // namespace

#endif

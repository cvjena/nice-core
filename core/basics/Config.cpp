// STL includes
#include <assert.h>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <set>

// nice-core includes
#include "core/basics/Exception.h"
#include "core/basics/Config.h"
#include "core/basics/ossettings.h"
#include "core/basics/StringTools.h"
#include "core/basics/FileName.h"

using ::std::endl;
using ::std::vector;
using ::std::string;
using ::std::istream;
using ::std::ostream;
using ::std::ios;
using ::std::map;

#undef DEBUGCONFIG
#define DEBUGPRINT printf

namespace NICE {

Config::Config ()
{
  ioUntilEndOfFile = true;
}

Config::Config ( const std::string & configfn )
{
  if ( configfn.size() >0 ) {
    read(configfn);
  }
  ioUntilEndOfFile = true;
  m_sConfigFilename = configfn;
}

Config::Config ( int argc, 
         char **argv )
{
  readFromArguments ( argc, argv );
  std::string configfile = gS("main", "config", "" );
  
  std::cerr << "configfile: " << configfile << std::endl;
  ioUntilEndOfFile = gB("main", "ioUntilEndOfFile", true );
  if ( configfile.size() > 0 )
    readWithoutOverwrite ( configfile.c_str(), CONFIG_DO_NOT_OVERWRITE_VALUES /*do not overwrite values*/ );
}

Config::Config ( const Config & conf ) : Persistent()
{
  ioUntilEndOfFile = true;
  m_sConfigFilename = conf.m_sConfigFilename;
	confB.copyFrom ( conf.confB );
	confD.copyFrom ( conf.confD );
	confI.copyFrom ( conf.confI );
	confS.copyFrom ( conf.confS );
}

Config::~Config()
{
}

void Config::clear()
{
#if defined DEBUGCONFIG
	DEBUGPRINT( "Config: clear ...\n" );
#endif
  confB.clear();
  confD.clear();
  confI.clear();
	confS.clear();
}

void Config::addKeyValuePair ( const std::string & block,
			       const std::string & key, 
			       const std::string & value )
{
    vector<string> submatches;
#if defined DEBUGCONFIG
	DEBUGPRINT( "Config: analyzing value %s\n", value.c_str() );
#endif
    if ( StringTools::regexMatch ( value, "^ *([-[:digit:]]+) *;?$", submatches ) &&
	     (submatches.size() == 2) ) {
#if defined DEBUGCONFIG
	    DEBUGPRINT ( "Config: integer value\n");
#endif
	    int v;
	    v = StringTools::convert<int> ( submatches[1] );
	    confI.store ( block, key, v );
    } else if ( value.compare("true") == 0 ) {
#if defined DEBUGCONFIG
	    DEBUGPRINT( "Config: boolean value\n");
#endif
		confB.store ( block, key, true );
    } else if ( value.compare("false") == 0 ) {	    
#if defined DEBUGCONFIG
	    DEBUGPRINT ( "Config: boolean value\n");
#endif
		confB.store ( block, key, false );
    } else if ( StringTools::regexMatch ( value, "^ *([-e.[:digit:]]+) *;?$", submatches ) &&
	     (submatches.size() == 2) ) 
    {
	double v;
	if ( ! StringTools::convert<double> ( submatches[1], v )  ) 
	{
	    DEBUGPRINT ( "Config: please ask Erik to debug this part of Config.cpp\n");
	    exit(-1);
	}
	#if defined DEBUGCONFIG
	    DEBUGPRINT ( "Config: double value\n");
	#endif
	confD.store ( block, key, v );
    } else {
#if defined DEBUGCONFIG
	    DEBUGPRINT ( "Config: string value\n");
#endif
		string trimValue = value;
	    StringTools::trimbounds ( trimValue, '\"' );
	    StringTools::trimbounds ( trimValue, '\'' );
	    confS.store ( block, key, trimValue );
    }
}

void Config::readFromArguments ( int argc, char **argv )
{
    std::string section;
    std::string key;
    std::string value;
    ioUntilEndOfFile = true;

    for ( int i = 1 ; i < argc ; i++ )
    {
      if ( argv[i] == NULL ) break;
      std::string arg ( argv[i] );

      vector<string> submatches;
      bool match = false;

      match = StringTools::regexMatch ( arg, "^--?([[:alpha:]][[:alpha:][:digit:]_-]*):([[:alpha:][:digit:]_-]+)", submatches );
      if ( (match) && (submatches.size() == 3) ) {
        if ( key.size() > 0 ) {
          addArgBoolean ( section, key );
        }
        section = submatches[1];
        key     = submatches[2];
        continue;
      }

      match = StringTools::regexMatch ( arg, "^--?([[:alpha:]][[:alpha:][:digit:]_-]*)", submatches );
      if ( (match) && (submatches.size() == 2) ) {
        if ( key.size() > 0 )	
        {
          addArgBoolean ( section, key );
        }
        section = "main";
        key = submatches[1];
        continue;
      }

      value = string(argv[i]);

      if ( key.size() <= 0 )
      {
        // add to more options
        moreOptions.push_back ( value );
        continue;
      }

  #if defined DEBUGCONFIG
      cout << "Config: add command line option: " << section << ":" << key << " = " << value << endl;
  #endif
      addKeyValuePair ( section, key, value );

      key = "";
    }
 
    if ( key.size() > 0 )
		addArgBoolean ( section, key );
}

void Config::addArgBoolean ( const std::string & section, const std::string & key )
{
    vector<string> submatches;
    if ( StringTools::regexMatch ( key, "^no-(.*)$", submatches )
		&& (submatches.size() == 2) )
    {
		confB.store ( section, submatches[1], false );
    } else {
		confB.store ( section, key, true );
    }
}

void Config::restore (istream & is, int format)
{
    std::string block = "main";
    std::string key;
    std::string value;
    std::string line;
    int count = 0;
    
    //check for the first word
    //if this is "Config::store--PreciseTermination" then we do not read until eof
    //but bis the precise termination statement "Config::store--done" arises
    std::string firstWord;
    if (! is.eof() )
    {
      is >> firstWord;
      if ( firstWord.compare( "Config::store--PreciseTermination" ) == 0)
      {
          ioUntilEndOfFile = false;
      }
      else
          ioUntilEndOfFile = true;
    }
    
    //jump to the beginning of the file
    is.clear();
    is.seekg(0, ios::beg);

    //we keep the while-loop untached, but break out of ioUntilEndOfFile is false and we reached the termination-statement
    while (! is.eof()) 
    {
      size_t i=0;

      if ( !getline(is, line) )
        break;
      
      //do we have to check for the precise termination statement and reaches it yet?
      if ( (!ioUntilEndOfFile) &&  (line.compare("Config::store--done") == 0) ) 
        break;

      if ( line.size() <= 0 ) 
        continue;

      size_t len = line.size();
      count++;
      if ( (len < 1) || (line[0] == '#' ) )
        continue;

      line = StringTools::chomp ( line );
      len = line.size();

  #if defined DEBUGCONFIG
      DEBUGPRINT ("Config: (%d) '%s' (len = %d) / %s\n", static_cast<int>(count), line.c_str(), static_cast<int>(len),
        block.c_str());
  #endif

      while ( ( (line[i] == '\t') || (line[i]==' ') ) && (i<len)) i++;
      if ( i == len ) continue;
      
      if ( line[i] == '[' ) {
        size_t j = i+1;
        while ((line[j]!=']') && (j<len)) j++;
        if ( (j == len) || (i==j-1) ) continue;

        block = line.substr( i+1, j-i-1 );
  #if defined DEBUGCONFIG
        DEBUGPRINT ("Config: reading block %s\n", block.c_str());
  #endif
        StringTools::normalize_string(block);
        continue;
      }

      if ( line[i] == '%' ) {
        size_t j = i+1;
        while ((line[j]!='%') && (j<len)) j++;
        if ( (j == len) || (i==j-1) ) continue;

        std::string includefile = line.substr( i+1, j-i-1 );

  #if defined DEBUGCONFIG
        DEBUGPRINT ("Config: including config file %s\n", includefile.c_str());
  #endif
        StringTools::normalize_string ( includefile );

        readWithoutOverwrite ( includefile.c_str(), format );
        continue;
      }
      
      size_t p = i;
      while ( (line[p]!='=') && (p<len) ) p++;
      if ( (p >= len-1) || (p<=i) ) continue;
      key = line.substr( i, p-i );
      value = line.substr( p+1 ); // with only one argument, substr copies from the specified position until the end of the string

      StringTools::normalize_string(value);
      StringTools::normalize_string(key);
    //	transform(key.begin(), key.end(), key.begin(), ::tolower);

  #if defined DEBUGCONFIG
      DEBUGPRINT ("Config: found key value pair (%s,%s) in section %s\n", 
        key.c_str(), value.c_str(), block.c_str());
  #endif

      if ( (format == CONFIG_OVERWRITE_VALUES) || ( !keyExists(block, key) ) )
        addKeyValuePair ( block, key, value );

    }

#if defined DEBUGCONFIG
    DEBUGPRINT ("Config: successfully loaded.\n" );
    DEBUGPRINT ("Config: %d double values\n", static_cast<int>(confD.size()) );
    DEBUGPRINT ("Config: %d integer values\n", static_cast<int>(confI.size()) );
    DEBUGPRINT ("Config: %d bool values\n", static_cast<int>(confB.size()) );
    DEBUGPRINT ("Config: %d std::string values\n", static_cast<int>(confS.size()) );
#endif
}
      
bool Config::keyExists ( const std::string & block, const std::string & key ) const
{
    return ( confS.keyExists ( block, key ) || 
             confI.keyExists ( block, key ) ||
	     confB.keyExists ( block, key ) ||
             confD.keyExists ( block, key ) );
}

void Config::addHelp ( const std::string & block, const std::string & key,
		     const std::string & helpText )
{
    helpTexts[ block + "::" + key ] = helpText;
}

std::string Config::help ( const std::string & block, const std::string & key ) const
{
    std::string k = block + "::" + key;
    map<string, string>::const_iterator i = helpTexts.find(k);
    if ( i == helpTexts.end() )
	return "no helping information for this variable, sorry!";
    else
	return i->second;
}


std::string Config::gS(const std::string & key) const
{
    return gS(key, "main");
}

std::string Config::gS(const std::string & block, const std::string & key) const
{
    std::string v ("");
    if ( confS.find(block, key, v) )
    {
      return v;
    }
    else
    {
      std::string errorMessage = "Config: setting " + block + "::" + key + " not found !\n";
      errorMessage += "\n \n Config: " + help(block, key) + "\n";
      throw NICE::Exception( errorMessage );
    }

}

std::string Config::gS(const std::string & block, const std::string & key, const std::string & defv) const
{
    std::string v ("");
    if ( confS.find(block, key, v) ) {
		return v;
    } else {
#if defined DEBUGCONFIG
		DEBUGPRINT("Config: Setting %s::%s not found using default value %s\n", block.c_str(), key.c_str(), defv.c_str() );
#endif
		return defv;
    }

}

double Config::gD(const std::string & key) const
{
    return gD(key, "main");
}

double Config::gD(const std::string & block, const std::string & key) const
{
    double v = 0.0;
    if ( confD.find(block, key, v) ) {
		return v;
    } else {
		int vi;
		if ( confI.find(block, key, vi) ) {
			DEBUGPRINT("Config: Setting %s::%s should be double (please change in the config)\n", block.c_str(), key.c_str() );
			return static_cast<int>(vi);
		}
		fprintf (stderr, "Config: setting %s::%s not found !\n", block.c_str(), key.c_str() );
		fprintf (stderr, "Config: %s\n", help(block, key).c_str() );
		exit(-1);
		return -1.0; // never reached
    }
}

double Config::gD(const std::string & block, const std::string & key, const double defv) const
{
    double v = 0.0;
    if ( confD.find(block, key,  v) ) {
		return v;
    } else {
		int vi;
		if ( confI.find(block, key, vi) ) {
			DEBUGPRINT("Config: Setting %s::%s should be double (please change in the config)\n", block.c_str(), key.c_str() );
			return static_cast<int>(vi);
		}
#if defined DEBUGCONFIG
		DEBUGPRINT("Config: Setting %s::%s not found using default value %f\n", block.c_str(), key.c_str(), defv );
#endif
		return defv;
    }

}

int Config::gI(const std::string & key) const
{
    return gI(key, "main");
}

int Config::gI(const std::string & block, const std::string & key) const
{
    int v = 0;
    if ( confI.find(block, key, v) ) {
		return v;
    } else {
		fprintf (stderr, "Config: setting %s::%s not found !\n", block.c_str(), key.c_str() );
		fprintf (stderr, "Config: %s\n", help(block, key).c_str() );
		exit(-1);
		return 1; // never reached
    }

}

int Config::gI(const std::string & block, const std::string & key, int defv) const
{
    int v = 0;
    if ( confI.find(block, key, v) ) {
		return v;
    } else {
#if defined DEBUGCONFIG
		DEBUGPRINT("Config: Setting %s::%s not found using default value %d\n", block.c_str(), key.c_str(), defv );
#endif
		return defv;
    }
}

bool Config::gB(const std::string & key) const
{
    return gB(key, "main");
}

bool Config::gB(const std::string & block, const std::string & key) const
{
    bool v = true;
    if ( confB.find(block, key, v) ) {
		return v;
    } else {
		fprintf (stderr, "Config: setting %s::%s not found !\n", block.c_str(), key.c_str() );
		fprintf (stderr, "Config: %s\n", help(block, key).c_str() );
		exit(-1);
		return true; // never reached
    }

}

bool Config::gB(const std::string & block, const std::string & key, bool defv) const
{
    bool v = true;
    if ( confB.find(block, key, v) ) {
		return v;
    } else {
#if defined DEBUGCONFIG
		DEBUGPRINT("Config: Setting %s::%s not found using default value %d\n", block.c_str(), key.c_str(), defv );
#endif
		return defv;
    }
}

void Config::getAllS ( const std::string & block, std::map< string, std::string > & list ) const
{
    confS.getAll ( block, list );
}

void Config::getAllD ( const std::string & block, std::map< string, double > & list ) const
{
    confD.getAll ( block, list );
}

void Config::getAllI ( const std::string & block, std::map< string, int > & list ) const
{
    confI.getAll ( block, list );
}

void Config::getAllB ( const std::string & block, std::map< string, bool > & list ) const
{
    confB.getAll ( block, list );
}

void Config::sD(const std::string & block, const std::string & key, const double defv)
{
    confD.store ( block, key, defv );
}

void Config::sI(const std::string & block, const std::string & key, const int defv)
{
	confI.store ( block, key, defv );
}

void Config::sB(const std::string & block, const std::string & key, const bool defv)
{
	confB.store ( block, key, defv );
}

void Config::sS(const std::string & block, const std::string & key, const std::string & defv)
{
	confS.store ( block, key, defv );
}

void Config::store (ostream & os, int format) const 
{
  if (!ioUntilEndOfFile)
  {
    //let's give us a hint that we do not have to restore until end of file but until "Config::store--done"
    os << "Config::store--PreciseTermination" << std::endl;
  }
    os << "# -----------------------------------------" << endl;
    os << "# |             Config                    |" << endl;
    os << "# -----------------------------------------" << endl;

    os << endl << "# ------------- double values" << endl;
    confD.store( os, format );
    os << endl << "# ------------- boolean values" << endl;
    confB.store( os, format );
    os << endl << "# ------------- integer values" << endl;
    confI.store( os, format );
    os << endl << "# ------------- string values" << endl;
    confS.store( os, format );
    os << "# -----------------------------------------" << endl;
  if (!ioUntilEndOfFile)
  {
    os << "Config::store--done" << std::endl;
  }

}

void Config::getAllBlocks ( std::set< std::string > & list ) const
{
    list.clear();
    confB.getAllBlocks ( list );
    confD.getAllBlocks ( list );
    confS.getAllBlocks ( list );
    confI.getAllBlocks ( list );
}

string Config::getAbsoluteFilenameRelativeToThisConfig(const string &p_Filename) const
{
    if( m_sConfigFilename.empty() )
        return p_Filename;

    NICE::FileName t_DatasetFilename( p_Filename );

    if( !t_DatasetFilename.isRelative() )
    {
        return p_Filename;
    }

    NICE::FileName t_ConfigFilename( this->m_sConfigFilename );
    return  t_ConfigFilename.extractPath().str() + p_Filename;
}

}

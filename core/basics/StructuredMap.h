/** 
* @file Config.h
* @brief configuration mgt
* @author Erik Rodner
* @date 2006-03-12
*/
#ifndef STRUCTUREDINCLUDE
#define STRUCTUREDINCLUDE

#include <iostream>
#include <map>

#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <set>

#include <math.h>

#include "core/basics/Persistent.h"
  


namespace NICE {

template<class ValueType>
/** This class provides a structured map. */
class StructuredMap : public NICE::Persistent 
{
    protected:
      typedef typename std::map<std::string, ValueType> MapValueType;
      typedef typename std::map<std::string, ValueType>::const_iterator MapValueTypeCIterator;

      MapValueType conf;

    public:
    
      bool keyExists ( const std::string & block, const std::string & key ) const
      {
		  std::string newkey = block + "::" + key;
		  MapValueTypeCIterator map_i = conf.find(newkey);
		  return ( map_i != conf.end() );
      }

      bool find ( const std::string & block, const std::string & key, ValueType & value ) const
      {
		  std::string newkey = block + "::" + key;
		  MapValueTypeCIterator map_i = conf.find(newkey);
		  if ( map_i == conf.end() ) return false;
		  value = map_i->second;
		  return true;
      }

      void store ( const std::string & block, const std::string & key, const ValueType & value )
      {
		  std::string newkey = block + "::" + key;
		  conf[newkey] = value;
      }

      void getAll ( const std::string & block, std::map<std::string, ValueType> & list ) const
      {
		  // FIXME: optimize this !
		  for ( MapValueTypeCIterator map_i = conf.begin(); map_i != conf.end() ; map_i++ )
		  {
			  std::string key = map_i->first;
			  ValueType val = map_i->second;
			  if ( key.find (block + "::") == 0 ) 
			  {
			  size_t dpos = key.find_first_of(':', 0);
			  size_t dend = key.find_first_not_of(':', dpos);
			  list[key.substr(dend)] = val;
			  }
		  }
      }

      void getAllBlocks ( std::set<std::string> & blocks ) const
      {
		  for ( MapValueTypeCIterator map_i = conf.begin(); map_i != conf.end() ; map_i++ )
		  {
			  std::string key = map_i->first;
			  size_t dpos = key.find_first_of(':', 0);
			  std::string block = key.substr(0,dpos);
			  if ( blocks.find(block) == blocks.end() )
			  blocks.insert(block);
		  }
      }

      size_t size () const
      {
		  return conf.size();
      }

	  void restore (std::istream & is, int format = 0)
	  {
		  fthrow ( Exception, "StructuredMap: restore function of structured map not implemented\n" );
	  }

      void clear()
      {
		  conf.clear();
      }

      void store ( std::ostream & os, int format = 0 ) const
      {
		  std::string lastblock = "";
		  for ( MapValueTypeCIterator i = conf.begin();
			i != conf.end();
			i++ ) 
		  {
			  std::string k = i->first;
			  size_t dpos = k.find_first_of(':', 0);
			  size_t dend = k.find_first_not_of(':', dpos);
			  std::string block = k.substr(0,dpos);
			  std::string key = k.substr(dend);
			  ValueType value = i->second;

			  if ( block.compare(lastblock) != 0 ) {
				  os << std::endl << "[" << block << "]" << std::endl;
			  }
			  os << key << " = " << value << std::endl;

			  lastblock = block;
		  }
      }

	  void copyFrom ( const StructuredMap & map )
	  {
		  conf.clear();
		  conf = map.conf;		  
	  }
};


} // namespace

#endif

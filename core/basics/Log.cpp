/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#include "Log.h"

namespace NICE {
  
Log Log::_debugLog(std::cerr);
Log Log::_errorLog(std::cerr);
Log Log::_timingLog(std::cerr);
Log Log::_detailLog(std::cerr);
Log Log::_resultLog(std::cout);

std::stringstream Log::dummy;
  
Log::~Log() {
}

} // namespace

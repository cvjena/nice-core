/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libfbasics - library of some basic tools
 * See file License for license information.
 */
#include <core/basics/tools.h>

namespace NICE {

void writeLatexTabular(std::ostream& out,
                       std::vector<std::vector<std::string> >& data,
                       bool heading,
                       bool hlines,
                       bool vlines) {
  const uint lines = data.size();
  
  if (lines == 0) {
    return;
  }
  
  const uint columns = data[0].size();
  
  // latex tabular
  out << "\\begin{tabular}{";
  for (unsigned int j = 0; j < columns; j++) {
    if (vlines) {
      out << "|";
    }
    out << "l";
  }
  if (vlines) {
    out << "|";
  }
  out << "}" << std::endl;
  if (hlines) {
    out << "\\hline" << std::endl;
  }
  
  // data
  for (unsigned int i = 0; i < lines; i++) {
    if (i == 1 && heading) {
      out << "\\hline" << std::endl;
    }
    if (i > 0 && hlines) {
      out << "\\hline" << std::endl;
    }
    for (unsigned int j = 0; j < columns; j++) {
      if (j > 0) {
        out << "&";
      }
      out << data[i][j];
    }
    out << "\\\\" << std::endl;
  }
  
  // finish
  if (hlines) {
    out << "\\hline" << std::endl;
  }
  out << "\\end{tabular}" << std::endl;
}

} // namespace

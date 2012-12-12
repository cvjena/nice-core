#ifndef FILENAME_H
#define FILENAME_H

#include <string>

namespace NICE {
  
/**
 * Represents a file name.
 * Supports special string and file operations.
 * 
 * @author Ferid Bajramovic (ferid [dot] bajramovic [at] informatik [dot] uni-jena [dot] de)
 */
class FileName {
public:
  /**
   * Constructor: empty filename.
   */
  FileName();

  /**
   * Constructor.
   * @param _fileName initial file name
   */
	FileName(const std::string& _fileName);

  /**
   * Constructor.
   * @param _fileName initial file name
   */
  FileName(const char* _fileName);
  
  /**
   * Copy-Constructor.
   */
  FileName(const FileName& _fileName);
  
  /**
   * Assignment.
   */
  FileName& operator=(const FileName& _fileName);

  /**
   * Assignment.
   */
  FileName& operator=(const std::string& _fileName);

  /**
   * Assignment.
   */
  FileName& operator=(const char* _fileName);
  
	virtual ~FileName();
  
  /**
   * Convert to \c string.
   * @return the file name (as \c string)
   */
  const std::string& str() const;

  /**
   * Convert (cast) to <tt>char *</tt>.
   * @return the file name (as <tt>char *</tt>)
   */
  operator const char*() const;

  /**
   * Convert (cast) to \c string.
   * @return the file name (as \c string)
   */
  operator const std::string&() const;
  
  /**
   * Set the FileName to \c s.
   * @param s new filename
   */
  inline void set(const std::string& s) { fileName = s; }

  /**
   * Extract the path (including the last slash '/').
   * Example: <tt> FileName("/a/b/c/file.txt").extractPath()</tt>
   *          returns "/a/b/c/"
   * @return the path
   */
  FileName extractPath() const;

  /**
   * Extract the file name (name and extension, no path)
   * Example: <tt>FileName("/a/b/c/file.txt").extractFileName()</tt>
   *          returns "file.txt"
   * @return file name without path
   */
  FileName extractFileName() const;

  /**
   * Extract the extension (everything from the last dot '.', inclusive)
   * Example: <tt>FileName("/a/b/c/file.txt").extractExtension()</tt>
   *          returns ".txt"
   * @return the file extension
   */
  FileName extractExtension() const;
  
  /**
   * Remove the extension if one exists (everything from the last dot '.', inclusive)
   */
  void removeExtension();
  
  /**
   * Add a slash '/' at the end if there is non
   * (except when the FileName is empty "")
   */
  void addSlash();

  /**
   * Remove a slash '/' at the end if there is one
   */
  void removeSlash();
  
  /**
   * Add \c extension as file name extension,
   * except if the file name extension is already \c extension.
   * @param extension The new file name extension
   *        (should contain a leading dot ".")
   */
   void setExtension(const std::string& extension);
  
  /**
   * Create a directory named as this FileName.
   */
  void createDirectory() const;
  
  /**
   * Does this filename exist (i.e. a file with this name)?
   * @return true if the file exists
   */
  bool fileExists() const;

  /**
   * Is this filename a directory?
   * @return true if it's directory
   */
  bool isDirectory() const;
  
  /**
   * Delete the file (does not work on directories).
   */
  void deleteFile() const;
   
private:
  //! stores the file name
  std::string fileName;
};

} // namespace
#endif // FILENAME_H

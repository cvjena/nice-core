#ifndef _IMAGE_IMAGEFILELISTWRITER_H
#define _IMAGE_IMAGEFILELISTWRITER_H

#include "core/image/ImageOutputStream.h"
#include <string>
#include <fstream>
#include <vector>

namespace NICE {

/**
 * Writes a sequence of image files and a filelist.
 *
 * The filenames of the image files are formed as follows:
 * Let path = toppath/subdir.
 * Then the filenames are toppath/subdir/subdir_ + counter + extension.
 * The filename of the filelist text file is
 * toppath/subdir/subdir + '.txt'.
 * The directory toppath/subdir will be created if it doesn't exist.
 *
 * The filelist written by this class can be read by ImageFileListReader.
 * The filename of that filelist can be retrieved via getSequenceFileName().
 *
 * @note Any existing files will be overwritten!
 */
class ImageFileListWriter: public ImageOutputStream {
public:
	/**
	 * Constructor.
	 * @param path      Output path (see class description).
	 * @param extension target output extension
	 * @param _keepImagesInMemory Write all files in \c close().
	 *                            No disk access until then.
	 */
	ImageFileListWriter(const std::string& path, const std::string& extension = ".ppm", const bool _keepImagesInMemory =
			false);

	/**
	 * Destructor. Will close the writer.
	 */
	virtual ~ImageFileListWriter();

	//! write a ColorImage
	virtual void writeColorImage(const ColorImage& image);

	/**
	 * Write a Image.
	 * Note: If in buffered mode (\c _keepImagesInMemory), GrayImages will be
	 * buffered as ColorImages.
	 */
	virtual void writeGrayImage(const Image& image);

	/**
	 * If in buffered mode (\c _keepImagesInMemory), write all images to
	 disk.
	 * Otherwise, do nothing.
	 * NEW SINCE NICE
	 */
	virtual void flushMemoryBuffer();

	virtual void close();
	virtual void insertMissingFrames(int frames);

	/**
	 * Get the name of the output file (as can be passed to ImageFileListReader)
	 * @return filename of the output file list
	 */
	inline const std::string& getSequenceFileName() const {
		return fileListFileName;
	}

	/**
	 * Current frame index. The index of the NEXT image to be written.
	 */
	inline int currentFrameIndex() const {
		return currentFrame;
	}

	/**
	 * The filename of the last image which has been written.
	 */
	inline const std::string& lastImageFileName() const {
		return m_lastImageFileName;
	}

private:
	//! The output name prefix.
	std::string namePrefix;

	//! The output name extension and thus file format.
	std::string nameExtension;

	//! The current frame number.
	int currentFrame;

	//! The file name of the output file list.
	std::string fileListFileName;

	//! Stream to the output file list.
	std::ofstream fileList;

	/**
	 * Initialize.
	 * @param path Output path
	 */
	void init(const std::string& path);

	/**
	 * Construct the file name for the current frame.
	 * @return new file name
	 */
	std::string makeCurrentFileName();

	/**
	 * Add a file name to the file list.
	 * @param fileName File name to be added.
	 */
	void addToFileList(const std::string& fileName);

	//! Keep images in memory until destruction?
	bool keepImagesInMemory;

	//! Buffered images.
	std::vector<ColorImage*> images;

	//! Buffered file names.
	std::vector<std::string*> fileNames;

	std::string m_lastImageFileName;
};

} // namespace

#endif // _IMAGE_IMAGEFILELISTWRITER_H

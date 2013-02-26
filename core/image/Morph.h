/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#ifndef LIMUN_MORPH_H
#define LIMUN_MORPH_H


#include <core/image/ippwrapper.h>

#include <core/vector/VectorT.h>
#include <core/vector/MatrixT.h>

#include <core/image/ImageT.h>
#include <core/image/ColorImageT.h>
#include <core/image/Buffer.h>

#include <core/image/Histogram.h>
#include <core/image/Convert.h>

namespace NICE {

    /**
    * @name morphological operations with a given structure Element
    * \{
    */

    /**
    * Filters Image \c src into the gray Image \c dst using a ranking operation.
    * with a given structre element \c structureElement and rank \c rank.
    * @param src              source gray image
    * @param structureElement only pixels that correspond to nonzero mask values are taken into account
    *                         during operation
    * @param rank             determines which rank is used for the new pixel value
    * @param dst              Optional buffer to be used as target.<br>
    *                         Create a new Image if \c dst == NULL.<br>
    *                         If \c dst != NULL then size must be equal to \c src 's size!
    * @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal
    *                       or if \c rank is smaller 1 or bigger than the number of nonzero mask entries.
    */
    Image* rank(const Image& src, const CharMatrix& structureElement,
                    const size_t& rank, Image* dst=NULL);

    /**
    * Filters Image \c src into the Image \c dst using a median filter for a given \c structureElement .
    * @param src              source gray image
    * @param structureElement only pixels that correspond to nonzero mask values are taken into account
    *                         during operation
    * @param dst              Optional buffer to be used as target.<br>
    *                         Create a new Image if \c dst == NULL.<br>
    *                         If \c dst != NULL then size must be equal to \c src 's size!
    * @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal
    *                       or if \c rank is smaller 1 or bigger than the number of nonzero mask entries.
    */
    Image* median(const Image& src, const CharMatrix& structureElement, Image* dst=NULL);

    /**
    * Filters Image \c src into the Image \c dst using a erosion with a given \c structureElement .<br>
    * The erosion of an image equals the computation of the minimum of the nonzero Elements of \c structureElement .
    * @param src              source gray image
    * @param structureElement only pixels that correspond to nonzero mask values are taken into account
    *                         during operation
    * @param dst              Optional buffer to be used as target.<br>
    *                         Create a new Image if \c dst == NULL.<br>
    *                         If \c dst != NULL then size must be equal to \c src 's size!
    * @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal
    *                       or if \c rank is smaller 1 or bigger than the number of nonzero mask values.
    */
    Image* erode(const Image& src, const CharMatrix& structureElement, Image* dst=NULL);

    /**
    * Filters Image \c src into the Image \c dst using a dilation with a given \c structureElement .<br>
    * The dilation of an image equals the computation of the maximum of the nonzero Elements of \c structureElement .
    * @param src              source gray image
    * @param structureElement only pixels that correspond to nonzero mask values are taken into account
    *                         during operation
    * @param dst              Optional buffer to be used as target.<br>
    *                         Create a new Image if \c dst == NULL.<br>
    *                         If \c dst != NULL then size must be equal to \c src 's size!
    * @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal
    *                       or if \c rank is smaller 1 or bigger than the number of nonzero mask values
    */
    Image* dilate(const Image& src, const CharMatrix& structureElement, Image* dst=NULL);

    /**
    * Filters Image \c src into Image \c dst using a closing operation with a given \c structureElement .<br>
    * In the first step an erosion of \c src is performed, afterwards a dilation.
    * @param src              source gray image
    * @param structureElement only pixels that correspond to nonzero mask values are taken into account
    *                         during operation
    * @param dst              Optional buffer to be used as target.<br>
    *                         Create a new Image if \c dst == NULL.<br>
    *                         If \c dst != NULL then size must be equal to \c src 's size!
    * @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal
    *                       or if \c rank is smaller 1 or bigger than the number of nonzero mask values
    */
    Image* opening(const Image& src, const CharMatrix& structureElement, Image* dst=NULL);

    /**
    * Filters Image \c src into Image \c dst using a closing operation with a given \c structureElement .<br>
    * In the first step a dilation \c src is performed, afterwards a erosion.
    * @param src              source gray image
    * @param structureElement only pixels that correspond to nonzero mask values are taken into account
    *                         during operation
    * @param dst              Optional buffer to be used as target.<br>
    *                         Create a new Image if \c dst == NULL.<br>
    *                         If \c dst != NULL then size must be equal to \c src 's size!
    * @return Pointer to Image
    * @throw  ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal
    *                       or if \c rank is smaller 1 or bigger than the number of nonzero mask values
    */
    Image* closing(const Image& src, const CharMatrix& structureElement, Image* dst=NULL);

    /**
    * \}
    * @name morphological operations with a quadratic structure element
    * \{
    */

    /**
    * Filters Image \c src into the Image \c dst using a ranking operation with a given \c rank
    * @param src  source gray image
    * @param size Area of size (2*\c size +1)x(2*\c size +1) where to perform the ranking operation.
    * @param rank determines which rank is used for the new pixel value
    * @param dst  Optional buffer to be used as target.<br>
    *             Create a new Image if \c dst == NULL.<br>
    *             If \c dst != NULL then size must be equal to \c src 's size!
    * @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal
    *                       or if \c rank is not in [1,2,...,(2*size+1)x(2*size+1)]
    */
    Image* rank(const Image& src, const uint& size, const uint& rank, Image* dst=NULL);

    /**
    * Erode Image \c src into the Image \c dst .<br>
    * The erosion of an image equals the computation of the minimum of an area.
    * @param src  source gray image
    * @param dst  Optional buffer to be used as target.<br>
    *             Create a new Image if \c dst == NULL.<br>
    *             If \c dst != NULL then size must be equal to \c src 's size!
    * @param size Area of size (2*\c size +1)x(2*\c size +1) where to perform the erosion.
    * @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
    Image* erode(const Image& src, Image* dst=NULL, const size_t& size=1);

    /**
    * Filters Image \c src into the Image \c dst using a median filter.
    * @param src  source gray image
    * @param dst  Optional buffer to be used as target.<br>
    *             Create a new Image if \c dst == NULL.<br>
    *             If \c dst != NULL then size must be equal to \c src 's size!
    * @param size Area of size (2*\c size +1)x(2*\c size +1) where to compute the median.
    * @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and dst are not equal.
    */
    Image* median(const Image& src, Image* dst=NULL, const size_t& size=1);

	/**
	* Dilate Image \c src into the Image \c dst .<br>
    * The dilation of an image equals the computation of the maximum of an area.
	* @param src  source gray image
    * @param dst  Optional buffer to be used as target.<br>
    *             Create a new Image if \c dst == NULL.<br>
    *             If \c dst != NULL then size must be equal to \c src 's size!
    * @param size (2*\c size +1) x (2*\c size +1) area where to perform the dilations
    *             default is a 3x3 area
	* @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
	*/
	Image* dilate(const Image& src, Image* dst=NULL, const size_t& size=1);

	/**
	* Filters Image \c src into Image \c dst using a opening operation.<br>
    * In the first step an erosion of \c src is performed, afterwards a dilation.
	* @param src  source gray image
	* @param dst  Optional buffer to be used as target.<br>
    *             Create a new Image if \c dst == NULL.<br>
    *             If \c dst != NULL then size must be equal to \c src 's size!
    * @param size (2*\c size +1) x (2*\c size +1) area where to perform the opening operation (default 3x3)
    * @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
    */
	Image* opening(const Image& src, Image* dst=NULL, const size_t& size=1);

	/**
    * Filters Image \c src into Image \c dst using a closing operation.<br>
    * In the first step a dilation of \c src is performed, afterwards a erosion.
	* @param src  source gray image
	* @param dst  Optional buffer to be used as target.<br>
    *             Create a new Image if \c dst == NULL.<br>
    *             If \c dst != NULL then size must be equal to \c src 's size!
    * @param size (2*\c size +1) x (2*\c size +1) where to perform the closing operation (default 3x3)
	* @return Pointer to Image
    * @throw ImageException will be thrown if \c dst != NULL and the size of \c src and \c dst is not equal.
	*/
	Image* closing(const Image& src, Image* dst=NULL, const size_t& size=1);

	/**
	* \}
	* @name in-place morphological operations
	* \{
	*/

	/**
	* Filters Image \c src using a 3x3 ranking operation.
	* @param src  source gray image
	* @param rank Rank for the operation
	* @throw ImageException will be thrown if rank is not within [1,9]
	*/
	void rankingIP(Image& src, const uint& rank);

	/**
	* Filters Image \c src using a 3x3 dilation.
	* @param src source gray image
	*/
	void dilateIP(Image& src);

	/**
	* Filters Image \c src using a 3x3 median.
	* @param src source gray image
	*/
	void medianIP(Image& src);

	/**
	* Filters Image \c src using a 3x3 erosion.
	* @param src source gray image
	*/
	void erodeIP(Image& src);

	/**
	* Filters Image \c src using a 3x3 opening operation.
	* @param src source gray image
	*/
	void openingIP(Image& src);

	/**
	* Filters Image \c src using a 3x3 closing operation.
	* @param src source gray image
	*/
	void closingIP(Image& src);

    /**
    * \}
    * @name morphological matching functions
    * \{
    */

    /**
    * Performs a Hit-And-Miss operation on \c src by a given \c structureElement .<br>
    * The first step is a erosion of \c src with the nonzero elements of \c structureElement. <br>
    * In the second step the complement of \c src is eroded by the complement of \c structureElement.
    * @param src              source gray image
    * @param structureElement structure element to be used for the hitAndMiss operation.<br>
    *                         Only pixels that correspond to nonzero mask values are taken 
    *                         into account during operation.<br>
    * @param dst              Optional buffer to be used as target.<br>
    *                         Create a new Image if \c dst == NULL.<br>
    *                         If \c dst != NULL then size must be equal to \c src 's size!
    * @return Pointer to Image
    */
    Image* hitAndMiss(const Image& src, const CharMatrix& structureElement, Image* dst=NULL);

    /**
    * \}
    * @name special median Implementation
    * \{
    */

    /**
    * Filters Image \c src by rows into the Image \c dst using medianfilter.
    * @param src     source gray image
    * @param anchorx horizontal offset to the kernelposition if negativ use center position
    * @param anchory vertical offset to the kernelposition if negativ use center position
    * @param maskx   horizontal size of the median mask
    * @param masky   vertical size of the median mask
    * @param dst     Optional buffer to be used as target.<br>
    *                Create a new Image if dst == NULL.<br>
    *                If dst != NULL then size must be equal to src's size!
    * @return Image
    */
    template<class P>
    ImageT<P>* median(const ImageT<P>& src, int anchorx=-1, int anchory=-1,
                          uint maskx=3, uint masky=3, ImageT<P>* dst=NULL);

    /**
    * Filters ColorImage \c src by rows into the ColorImage \c dst using a 5x5 medianfilter.
    * @param src  source gray image
    * @param mask switch between 3x3 masksize (false) and 5x5 masksize (true)
    * @param dst  Optional buffer to be used as target.<br>
    *             Create a new Image if dst == NULL.<br>
    *             If dst != NULL then size must be equal to src's size!
    * @return Image
    */
    template<class P>
    ColorImageT<P>* median(const ColorImageT<P>& src,bool mask=false, ColorImageT<P>* dst=NULL);

    /**
    * \}
    */
} // namespace

//#ifdef __GNUC__
	#include <core/image/Morph.tcc>
//#endif

#endif //LIMUN_RANKING_H

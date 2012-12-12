/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#ifndef LIMUN_BUFFER_H
#define LIMUN_BUFFER_H


#include "core/image/ippwrapper.h"
#include "core/image/GrayColorImageCommonImplementation.h"
#include "core/image/RectT.h"
#include "core/vector/VectorT.h"

namespace NICE {
	
	/**
	* Create result buffer.
	* @param image input
	* @param buffer image buffer for result
	* @return image buffer
	*/
	template<class IMG, class BUFFER>
	BUFFER* createResultBuffer(const IMG& image, BUFFER* buffer);
	
	/**
	* Create result buffer.
	* @param width width of the input image
	* @param height height of the input image
	* @param buffer image buffer for result
	* @return image buffer
	*/
	template<class BUFFER>
	BUFFER* createResultBuffer(const int width, const int height, BUFFER* buffer);
	
} // namespace


#ifdef __GNUC__
	#include <core/image/Buffer.tcc>
#endif

#endif //LIMUN_BUFFER_H

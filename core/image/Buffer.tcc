
#include <iostream>

namespace NICE {

template<class BUFFER>
BUFFER* createResultBuffer(const int width, const int height, BUFFER* buffer) 
{
	BUFFER* result;
	if(buffer == NULL) 
	{
		result = new BUFFER(width, height);
	} 
	else if(buffer->width()==0 && buffer->height()==0) 
	{
		result = buffer;
		result->resize(width,height);
	}
	else 
	{
		result = buffer;
		if (result->width() != width || result->height() != height) 
		{
			fthrow(ImageException, "DeprecatedConverter: size of image is not equal to (width, height).");
		}
	}
	return result;
}

template<class IMG, class BUFFER>
BUFFER* createResultBuffer(const IMG& image, BUFFER* buffer)
{
	BUFFER* result;
	if (buffer == NULL) 
	{
		result = new BUFFER(image.width(), image.height());
	} 
	else if(buffer->width()==0 && buffer->height()==0) 
	{
		result = buffer;
		result->resize(image.width(),image.height());
	}
	else 
	{
		result = buffer;
		if (result->width() != image.width() 
			|| result->height() != image.height()) 
		{
			fthrow(ImageException, "DeprecatedConverter: size of image and buffer are not equal.");
		}
	}
	return result;
}

}

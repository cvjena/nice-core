#ifndef __LIMUN_TEKKOTSULINK_H__
#define __LIMUN_TEKKOTSULINK_H__

/**
 * @file TekkotsuLink.h
 * Interface between Linum images and Tekkotsu images.
 * Only available in AIBO mode.
 */


#ifdef LIMUN_AIBO_MODE

	#include <core/image/ImageT.h>
	#include <core/image/ColorImageT.h>
	
	#include <Shared/WorldState.h>
	#include <Shared/ProjectInterface.h>
	#include <Shared/Config.h>
	#include <Behaviors/BehaviorBase.h>
	
	#include <Events/EventRouter.h>
			
	#include <Events/FilterBankEvent.h>
	#include <Vision/RawCameraGenerator.h>
	#include <Vision/InterleavedYUVGenerator.h>

namespace NICE {
	
/**
* Create a new interleaved YUV ColorImage from a Tekkotsu
* FilterBankEvent \c fbkevt. The new ColorImage directly uses the pixel memory
* of the FilterBankEvent, the image data itself is not copied.
* @param fbkevt source FilterBankEvent created from an InterleavedYUVGenerator.
*        The GeneratorID has to be EventBase::visInterleaveEGID.
* @param layer specifies the size of the created ColorImage, possible values are
* - 5 - double resolution - 416x320 - requires some significant processing, so use it sparingly.
* - 4 - full resolution - 208x160 - direct from system
* - 3 - half resolution - 104x80 - direct from system
* - 2 - quarter resolution - 52x40 - direct from system
* - 1 - eigth resolution - 26x20 - references every other pixel of quarter resolution image
* - 0 - sixteenth resolution - 13x10 - references the every fourth pixel of quarter resolution image
* @return Pointer to a new ColorImage
* @throws ImageException will be thrown if the fbkevt or layer is invalid.
*/
inline ColorImage* createYUVImageFromTekkotsu(const FilterBankEvent& fbkevt,
                                              const uint& layer) {
  if (fbkevt.getGeneratorID() != EventBase::visInterleaveEGID) {
    fthrow(ImageException,
           "Invalid event GeneratorID (expected visInterleaveEGID).");
  }
        
  if (layer > 5) {
    fthrow(ImageException, "Invalid Layer.");
  }

  FilterBankGenerator* gen = fbkevt.getSource();

  return new ColorImage(gen->getImage(layer, 0),
                        gen->getWidth(layer),
                        gen->getHeight(layer),
                        gen->getStride(layer),
                        GrayColorImageCommonImplementation::shallowCopy);
}

/**
* Return an interleaved YUV ColorImage from a Tekkotsu
* FilterBankEvent \c fbkevt. The new ColorImage directly uses the pixel memory
* of the FilterBankEvent, the image data itself is not copied.
* @param fbkevt source FilterBankEvent created from an InterleavedYUVGenerator.
*        The GeneratorID has to be EventBase::visInterleaveEGID.
* @param layer specifies the size of the created ColorImage, possible values are
* - 5 - double resolution - 416x320 - requires some significant processing, so use it sparingly.
* - 4 - full resolution - 208x160 - direct from system
* - 3 - half resolution - 104x80 - direct from system
* - 2 - quarter resolution - 52x40 - direct from system
* - 1 - eigth resolution - 26x20 - references every other pixel of quarter resolution image
* - 0 - sixteenth resolution - 13x10 - references the every fourth pixel of quarter resolution image
* @return The new ColorImage
* @throws ImageException will be thrown if the fbkevt or layer is invalid.
*/
inline ColorImage yuvImageFromTekkotsu(const FilterBankEvent& fbkevt,
                                       const uint& layer) {
  if (fbkevt.getGeneratorID() != EventBase::visInterleaveEGID) {
    fthrow(ImageException,
           "Invalid event GeneratorID (expected visInterleaveEGID).");
  }
        
  if (layer > 5) {
    fthrow(ImageException, "Invalid Layer.");
  }

  FilterBankGenerator* gen = fbkevt.getSource();

  return ColorImage(gen->getImage(layer, 0),
                    gen->getWidth(layer),
                    gen->getHeight(layer),
                    gen->getStride(layer),
                    GrayColorImageCommonImplementation::shallowCopy);
}

/**
* Create a new Image from a Tekkotsu FilterBankEvent \c fbkevt.
* The new Image directly uses the pixel memory
* of the FilterBankEvent, the image data itself is not copied.
* @param fbkevt source FilterBankEvent created from a RawCameraGenerator.
*        The GeneratorID has to be EventBase::visRawCameraEGID.
* @param layer specifies the size of the created ColorImage, possible values are
* - 5 - double resolution - 416x320 - requires some significant processing, so use it sparingly.
* - 4 - full resolution - 208x160 - direct from system
* - 3 - half resolution - 104x80 - direct from system
* - 2 - quarter resolution - 52x40 - direct from system
* - 1 - eigth resolution - 26x20 - references every other pixel of quarter resolution image
* - 0 - sixteenth resolution - 13x10 - references the every fourth pixel of quarter resolution image
* @param channel Channel to retrieve from the RawCameraGenerator, possible values are:
*   - RawCameraGenerator::CHAN_Y      - Y (intensity) channel.
*   - RawCameraGenerator::CHAN_U      - Cb (approx. blue,green,yellow) channel.
*   - RawCameraGenerator::CHAN_V      - Cr (approx. pink,red,yellow) channel.
*   - RawCameraGenerator::CHAN_Y_DY   - vertical derivative of Y channel.
*   - RawCameraGenerator::CHAN_Y_DX   - horizontal derivative of Y channel.
*   - RawCameraGenerator::CHAN_Y_DXDY - vert. & horiz. derivatives of Y channel.
* @return Pointer to Image
* @throws ImageException will be thrown if the fbkevt, layer or channel is invalid.
*/
inline Image* createGrayImageFromTekkotsu(
                    const FilterBankEvent& fbkevt,
                    const uint& layer,
                    const RawCameraGenerator::channel_id_t channel) {
  if (fbkevt.getGeneratorID() != EventBase::visRawCameraEGID) {
    fthrow(ImageException,
           "Invalid event GeneratorID (expected visRawCameraEGID).");
  }
        
  if (layer > 5) {
    fthrow(ImageException, "Invalid Layer.");
  }
		
  if (channel < RawCameraGenerator::CHAN_Y 
      || channel > RawCameraGenerator::CHAN_Y_DXDY) {
    fthrow(ImageException, "Invalid Channel.");
  }

  FilterBankGenerator* gen = fbkevt.getSource();

  return new Image(gen->getImage(layer, channel), 
                       gen->getWidth(layer),
                       gen->getHeight(layer),
                       GrayColorImageCommonImplementation::shallowCopy);
}

/**
* Return a Image from a Tekkotsu FilterBankEvent \c fbkevt.
* The new Image directly uses the pixel memory
* of the FilterBankEvent, the image data itself is not copied.
* @param fbkevt source FilterBankEvent created from a RawCameraGenerator.
*        The GeneratorID has to be EventBase::visRawCameraEGID.
* @param layer specifies the size of the created ColorImage, possible values are
* - 5 - double resolution - 416x320 - requires some significant processing, so use it sparingly.
* - 4 - full resolution - 208x160 - direct from system
* - 3 - half resolution - 104x80 - direct from system
* - 2 - quarter resolution - 52x40 - direct from system
* - 1 - eigth resolution - 26x20 - references every other pixel of quarter resolution image
* - 0 - sixteenth resolution - 13x10 - references the every fourth pixel of quarter resolution image
* @param channel Channel to retrieve from the RawCameraGenerator, possible values are:
*   - RawCameraGenerator::CHAN_Y      - Y (intensity) channel.
*   - RawCameraGenerator::CHAN_U      - Cb (approx. blue,green,yellow) channel.
*   - RawCameraGenerator::CHAN_V      - Cr (approx. pink,red,yellow) channel.
*   - RawCameraGenerator::CHAN_Y_DY   - vertical derivative of Y channel.
*   - RawCameraGenerator::CHAN_Y_DX   - horizontal derivative of Y channel.
*   - RawCameraGenerator::CHAN_Y_DXDY - vert. & horiz. derivatives of Y channel.
* @return Image
* @throws ImageException will be thrown if the fbkevt, layer or channel is invalid.
*/
inline Image grayImageFromTekkotsu(
                   const FilterBankEvent& fbkevt,
                   const uint& layer,
                   const RawCameraGenerator::channel_id_t channel) {
  if (fbkevt.getGeneratorID() != EventBase::visRawCameraEGID) {
    fthrow(ImageException,
           "Invalid event GeneratorID (expected visRawCameraEGID).");
  }
        
  if (layer > 5) {
    fthrow(ImageException, "Invalid Layer.");
  }
        
  if (channel < RawCameraGenerator::CHAN_Y 
      || channel > RawCameraGenerator::CHAN_Y_DXDY) {
    fthrow(ImageException, "Invalid Channel.");
  }

  FilterBankGenerator* gen = fbkevt.getSource();

  return Image(gen->getImage(layer, channel), 
                   gen->getWidth(layer),
                   gen->getHeight(layer),
                   GrayColorImageCommonImplementation::shallowCopy);
}

} // namespace NICE

#endif // LIMUN_AIBO_MODE

#endif // __LIMUN_TEKKOTSULINK_H__

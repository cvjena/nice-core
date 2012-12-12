#ifndef _IMAGEDISPLAY_OVERLAYCOLORS_H
#define _IMAGEDISPLAY_OVERLAYCOLORS_H

namespace NICE {
// overlay color table (ICE)
static const unsigned int overlayColorTableNumEntries = 8; 
static const unsigned char overlayColorTable[overlayColorTableNumEntries][3] =
      {{127,   0,   0},  // dark red
       {255,   0,   0},  // red
       {  0, 255,   0},  // green
       {  0,   0, 255},  // blue
       {255, 255,   0},  // yellow
       {  0, 255, 255},  // cyan
       {255,   0, 255},  // magenta
       {255, 127, 127}}; // pink

}

#endif

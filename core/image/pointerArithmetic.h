/*
 * NICE-Core - efficient algebra and computer vision methods
 *  - libimage - An image library
 * See file License for license information.
 */
#ifndef HELP_IPP_H
#define HELP_IPP_H


#include "core/image/ippwrapper.h"
#include "core/image/CoordT.h"

namespace NICE {

/**
 * Shift an IPP pointer in an image.
 * Get a new pointer that points to the pixel at location (\c x, \c y)
 * @param pointer Original pointer to the image data
 * @param x The X-coordinate of the pixel to point to
 * @param y The Y-coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return A pointer pointing to the pixel (\c x, \c y)
 */
template <class T>
inline const T* pointerToPixel1(const T* pointer, int x, int y, int stepsize) {
  return (T*) (((Ipp8u*) pointer) + y * stepsize + x * sizeof(T));
}

/**
 * Shift an IPP pointer in an image.
 * @copydoc pointerToPixel1()
 */
template <class T>
inline T* pointerToPixel1(T* pointer, int x, int y, int stepsize) {
  return (T*) (((Ipp8u*) pointer) + y * stepsize + x * sizeof(T));
}

/**
 * Shift an IPP pointer in a three channel image.
 * @copydoc pointerToPixel1()
 */
template <class T>
inline const T* pointerToPixel3(const T* pointer, int x, int y, int stepsize) {
  return (T*) (((Ipp8u*) pointer) + y * stepsize + x * sizeof(T) * 3);
}

/**
 * Shift an IPP pointer in a three channel image.
 * @copydoc pointerToPixel1()
 */
template <class T>
inline T* pointerToPixel3(T* pointer, int x, int y, int stepsize) {
  return (T*) (((Ipp8u*) pointer) + y * stepsize + x * sizeof(T) * 3);
}

/**
 * Shift an IPP pointer in an image.
 * Get a new pointer that points to the pixel at location (\c 0, \c y)
 * @param pointer Original pointer to the image data
 * @param y The Y-coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return A pointer pointing to the pixel (\c 0, \c y)
 */
template <class T>
inline const T* pointerToPixelY(const T* pointer, int y, int stepsize) {
  return (T*) (((Ipp8u*) pointer) + y * stepsize);
}

/**
 * Shift an IPP pointer in an image.
 * @copydoc pointerToPixel()
 */
template <class T>
inline T* pointerToPixelY(T* pointer, int y, int stepsize) {
  return (T*) (((Ipp8u*) pointer) + y * stepsize);
}

/**
 * Shift an IPP pointer in an image.
 * Get a new pointer that points to the pixel at location \c coord
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return A pointer pointing to the pixel \c coord
 */
template <class T>
inline const T* pointerToPixel1(const T* pointer, const Coord &coord, int stepsize) {
  return (T*) (((Ipp8u*) pointer) + coord.y * stepsize + coord.x * sizeof(T));
}

/**
 * Shift an IPP pointer in an image.
 * Get a new pointer that points to the pixel at location \c coord
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return A pointer pointing to the pixel \c coord
 */
template <class T>
inline T* pointerToPixel1(T* pointer, const Coord &coord, int stepsize) {
  return (T*) (((Ipp8u*) pointer) + coord.y * stepsize + coord.x * sizeof(T));
}

/**
 * Shift an IPP pointer in a three channel image.
 * Get a new pointer that points to the pixel at location \c coord
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return A pointer pointing to the pixel \c coord
 */
template <class T>
inline const T* pointerToPixel3(const T* pointer, const Coord &coord, int stepsize) {
  return (T*) (((Ipp8u*) pointer) + coord.y * stepsize + coord.x * sizeof(T) * 3);
}

/**
 * Shift an IPP pointer in a three channel image.
 * Get a new pointer that points to the pixel at location \c coord
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return A pointer pointing to the pixel \c coord
 */
template <class T>
inline T* pointerToPixel3(T* pointer, const Coord &coord, int stepsize) {
  return (T*) (((Ipp8u*) pointer) + coord.y * stepsize + coord.x * sizeof(T) * 3);
}


/**
 * Shift an IPP pointer in an image.
 * Get a new pointer that points to the pixel at location (\c x, \c y)
 * @param pointer Original pointer to the image data
 * @param x The X-coordinate of the pixel to point to
 * @param y The Y-coordinate of the pixel to point to
 * @param rowStepsize IPP (row) stepsize associated with \c pointer
 * @param columnStepsize stepsize between colmuns associated with \c pointer
 * @return A pointer pointing to the pixel (\c x, \c y)
 */
template <class T>
inline const T* pointerToPixelEx(const T* pointer, int x, int y, int rowStepsize, int columnStepsize) {
  return (T*) (((Ipp8u*) pointer) + y * rowStepsize + x * columnStepsize);
}

/**
 * Shift an IPP pointer in an image.
 * @copydoc pointerToPixel1()
 */
template <class T>
inline T* pointerToPixelEx(T* pointer, int x, int y, int rowStepsize, int columnStepsize) {
  return (T*) (((Ipp8u*) pointer) + y * rowStepsize + x * columnStepsize);
}









/**
 * Shift an IPP pointer in an image.
 * Get a new pointer that points to the pixel at location (\c x, \c y)
 * @param pointer Original pointer to the image data
 * @param x The X-coordinate of the pixel to point to
 * @param y The Y-coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return A pointer pointing to the pixel (\c x, \c y)
 */
inline const Ipp8u* helpIppiShiftPointer_8u_C1(const Ipp8u* pointer, const int x, const int y, 
                                         int stepsize) {
  return pointer + y * stepsize + x;
}

/**
 * Shift an IPP pointer in an image.
 * @copydoc helpIppiShiftPointer_8u_C1()
 */
inline Ipp8u* helpIppiShiftPointer_8u_C1(Ipp8u* pointer, const int x, const int y, 
                                         int stepsize) {
  return pointer + y * stepsize + x;
}

/**
 * Shift an IPP pointer in an image.
 * @copydoc helpIppiShiftPointer_8u_C1()
 */
inline const Ipp8u* helpIppiShiftPointer_8u_C3(const Ipp8u* pointer, const int x, const int y, 
                                         int stepsize) {
  return pointer + y * stepsize + x * 3;
}

/**
 * Shift an IPP pointer in an image.
 * @copydoc helpIppiShiftPointer_8u_C1()
 */
inline Ipp8u* helpIppiShiftPointer_8u_C3(Ipp8u* pointer, const int x, const int y, 
                                         int stepsize) {
  return pointer + y * stepsize + x * 3;
}

/**
 * Shift an IPP pointer in an image.
 * @copydoc helpIppiShiftPointer_8u_C1()
 */
inline const Ipp16s* helpIppiShiftPointer_16s_C1(const Ipp16s* pointer, const int x, const int y, 
                                           int stepsize) {
  return (Ipp16s*) (((Ipp8u*) pointer) + y * stepsize + x * sizeof(Ipp16s));
}

/**
 * Shift an IPP pointer in an image.
 * @copydoc helpIppiShiftPointer_8u_C1()
 */
inline Ipp16s* helpIppiShiftPointer_16s_C1(Ipp16s* pointer, const int x, const int y, 
                                           int stepsize) {
  return (Ipp16s*) (((Ipp8u*) pointer) + y * stepsize + x * sizeof(Ipp16s));
}

/**
 * Shift an IPP pointer in an image.
 * @copydoc helpIppiShiftPointer_8u_C1()
 */
inline const Ipp32f* helpIppiShiftPointer_32f_C1(const Ipp32f* pointer, const int x, const int y, 
                                           int stepsize) {
  return (Ipp32f*) (((Ipp8u*) pointer) + y * stepsize + x * sizeof(Ipp32f));
}

/**
 * Shift an IPP pointer in an image.
 * @copydoc helpIppiShiftPointer_8u_C1()
 */
inline Ipp32f* helpIppiShiftPointer_32f_C1(Ipp32f* pointer, const int x, const int y, 
                                           int stepsize) {
  return (Ipp32f*) (((Ipp8u*) pointer) + y * stepsize + x * sizeof(Ipp32f));
}

/**
 * Shift an IPP pointer in an image.
 * @copydoc helpIppiShiftPointer_8u_C1()
 */
inline const Ipp64f* helpIppiShiftPointer_64f_C1(const Ipp64f* pointer, const int x, const int y, 
                                           int stepsize) {
  return (Ipp64f*) (((Ipp8u*) pointer) + y * stepsize + x * sizeof(Ipp64f));
}

/**
 * Shift an IPP pointer in an image.
 * @copydoc helpIppiShiftPointer_8u_C1()
 */
inline Ipp64f* helpIppiShiftPointer_64f_C1(Ipp64f* pointer, const int x, const int y, 
                                           int stepsize) {
  return (Ipp64f*) (((Ipp8u*) pointer) + y * stepsize + x * sizeof(Ipp64f));
}

/**
 * Shift an IPP pointer in an image.
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return pointer pointing to the pixel \c coord
 */
inline const Ipp8u* helpIppiShiftPointer_8u_C1(const Ipp8u* pointer, const Coord &coord, 
                                         int stepsize) {
  return pointer + coord.y * stepsize + coord.x;
}

/**
 * Shift an IPP pointer in an image.
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return pointer pointing to the pixel \c coord
 */
inline Ipp8u* helpIppiShiftPointer_8u_C1(Ipp8u* pointer, const Coord &coord, 
                                         int stepsize) {
  return pointer + coord.y * stepsize + coord.x;
}

/**
 * Shift an IPP pointer in an image.
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return pointer pointing to the pixel \c coord
 */
inline const Ipp8u* helpIppiShiftPointer_8u_C3(const Ipp8u* pointer, const Coord &coord, 
                                         int stepsize) {
  return pointer + coord.y * stepsize + coord.x * 3;
}

/**
 * Shift an IPP pointer in an image.
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return pointer pointing to the pixel \c coord
 */
inline Ipp8u* helpIppiShiftPointer_8u_C3(Ipp8u* pointer, const Coord &coord, 
                                         int stepsize) {
  return pointer + coord.y * stepsize + coord.x * 3;
}

/**
 * Shift an IPP pointer in an image.
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return pointer pointing to the pixel \c coord
 */
inline const Ipp16s* helpIppiShiftPointer_16s_C1(const Ipp16s* pointer, const Coord &coord, 
                                           int stepsize) {
  return (Ipp16s*) (((Ipp8u*) pointer) + coord.y * stepsize + coord.x * sizeof(Ipp16s));
}

/**
 * Shift an IPP pointer in an image.
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return pointer pointing to the pixel \c coord
 */
inline Ipp16s* helpIppiShiftPointer_16s_C1(Ipp16s* pointer, const Coord &coord, 
                                           int stepsize) {
  return (Ipp16s*) (((Ipp8u*) pointer) + coord.y * stepsize + coord.x * sizeof(Ipp16s));
}

/**
 * Shift an IPP pointer in an image.
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return pointer pointing to the pixel \c coord
 */
inline const Ipp32f* helpIppiShiftPointer_32f_C1(const Ipp32f* pointer, const Coord &coord, 
                                           int stepsize) {
  return (Ipp32f*) (((Ipp8u*) pointer) + coord.y * stepsize + coord.x * sizeof(Ipp32f));
}

/**
 * Shift an IPP pointer in an image.
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return pointer pointing to the pixel \c coord
 */
inline Ipp32f* helpIppiShiftPointer_32f_C1(Ipp32f* pointer, const Coord &coord, 
                                           int stepsize) {
  return (Ipp32f*) (((Ipp8u*) pointer) + coord.y * stepsize + coord.x * sizeof(Ipp32f));
}

/**
 * Shift an IPP pointer in an image.
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return pointer pointing to the pixel \c coord
 */
inline const Ipp64f* helpIppiShiftPointer_64f_C1(const Ipp64f* pointer, const Coord &coord, 
                                           int stepsize) {
  return (Ipp64f*) (((Ipp8u*) pointer) + coord.y * stepsize + coord.x * sizeof(Ipp64f));
}

/**
 * Shift an IPP pointer in an image.
 * @param pointer  Original pointer to the image data
 * @param coord    coordinate of the pixel to point to
 * @param stepsize IPP stepsize associated with \c pointer
 * @return pointer pointing to the pixel \c coord
 */
inline Ipp64f* helpIppiShiftPointer_64f_C1(Ipp64f* pointer, const Coord &coord, 
                                           int stepsize) {
  return (Ipp64f*) (((Ipp8u*) pointer) + coord.y * stepsize + coord.x * sizeof(Ipp64f));
}
} // namespace
#endif

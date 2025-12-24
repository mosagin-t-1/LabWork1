/*
 * Mosagin Timofey
 * st142155@student.spbu.ru
 * My lab work 1
 */

#ifndef FILTERS_H
#define FILTERS_H

#include "bmpimage.h"

BMPImage rotate_cw(const BMPImage &in);
BMPImage rotate_ccw(const BMPImage &in);
BMPImage gaussian_blur(const BMPImage &in);

#endif

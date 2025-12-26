/*
 * Mosagin Timofey
 * st142155@student.spbu.ru
 * My lab work 1
 */

#ifndef BMPHEADER_H
#define BMPHEADER_H

#include <cstdint>
#include <istream>
#include <ostream>

#include "pixel.h"

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

class BMPHeader {
    BMPFileHeader fh{};
    BMPInfoHeader ih{};
    static constexpr int BYTES_PER_PIXEL = 3;
    static constexpr int ROW_ALIGNMENT = 4; 

public:
    BMPHeader() = default;

    bool read(std::istream &in);
    bool write(std::ostream &out) const;
    bool isValid() const;
    int width() const;
    int heightAbs() const;
    bool isBottomUp() const;
    int bitCount() const;
    uint32_t dataOffset() const;
    void setDefaults(int w, int h);
    void updateImageSizeAndFileSize(int w, int h);
    int rowSizeBytes(int w) const;
};

#endif

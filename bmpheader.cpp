/*
 * Mosagin Timofey
 * st142155@student.spbu.ru
 * My lab work 1
 */

#include "bmpheader.h"
#include <iostream>

bool BMPHeader::read(std::istream &in) {
    in.read(reinterpret_cast<char*>(&fh), sizeof(fh));
    in.read(reinterpret_cast<char*>(&ih), sizeof(ih));
    return !in.fail();
}

bool BMPHeader::write(std::ostream &out) const {
    out.write(reinterpret_cast<const char*>(&fh), sizeof(fh));
    out.write(reinterpret_cast<const char*>(&ih), sizeof(ih));
    return !out.fail();
}

bool BMPHeader::isValid() const {
    return fh.bfType == 0x4D42 && ih.biBitCount == 24 && ih.biCompression == 0;
}

int BMPHeader::width() const {
    return ih.biWidth;
}

int BMPHeader::heightAbs() const {
    return ih.biHeight < 0 ? -ih.biHeight : ih.biHeight;
}

bool BMPHeader::isBottomUp() const {
    return ih.biHeight > 0;
}

int BMPHeader::bitCount() const {
    return ih.biBitCount;
}

uint32_t BMPHeader::dataOffset() const {
    return fh.bfOffBits;
}

void BMPHeader::setDefaults(int w, int h) {
    fh.bfType = 0x4D42;
    fh.bfReserved1 = 0;
    fh.bfReserved2 = 0;
    fh.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    ih.biSize = sizeof(BMPInfoHeader);
    ih.biWidth = w;
    ih.biHeight = h;
    ih.biPlanes = 1;
    ih.biBitCount = 24;
    ih.biCompression = 0;
    ih.biXPelsPerMeter = 0;
    ih.biYPelsPerMeter = 0;
    ih.biClrUsed = 0;
    ih.biClrImportant = 0;

    updateImageSizeAndFileSize(w, h);
}

void BMPHeader::updateImageSizeAndFileSize(int w, int h) {
    const int rowSize = rowSizeBytes(w);
    ih.biSizeImage = rowSize * std::abs(h);
    fh.bfSize = fh.bfOffBits + ih.biSizeImage;
}

int BMPHeader::rowSizeBytes(int w) const {
    return ((w * 3 + 3) / 4) * 4;
}


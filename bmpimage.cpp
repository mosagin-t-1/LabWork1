#include "bmpimage.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include "pixel.h"

int BMPImage::width() const { return w; }
int BMPImage::height() const { return h; }
std::vector<Pixel>& BMPImage::data() { return pixels; }
const std::vector<Pixel>& BMPImage::data() const { return pixels; }

void BMPImage::setSize(int ww, int hh){
    w = ww;
    h = hh;
    pixels.assign(static_cast<size_t>(w) * static_cast<size_t>(h), Pixel{0,0,0});
    header.setDefaults(w, h);
    header.updateImageSizeAndFileSize(w, h);
}

bool BMPImage::load(const std::string &path){
    std::ifstream in(path, std::ios::binary);
    if(!in){
        std::cerr<<"BMPImage::load: cannot open file: "<<path<<"\n";
        return false;
    }
    if(!header.read(in)){
        std::cerr<<"BMPImage::load: failed to read header\n";
        return false;
    }
    if(!header.isValid()){
        std::cerr<<"BMPImage::load: invalid or unsupported BMP header\n";
        return false;
    }
    w = header.width();
    h = header.heightAbs();
    // move to pixel data offset
    in.seekg(static_cast<std::streamoff>(header.dataOffset()), std::ios::beg);
    // compute row size (includes padding)
    int rowSize = header.rowSizeBytes(w);
    std::vector<uint8_t> row(static_cast<size_t>(rowSize));
    pixels.assign(static_cast<size_t>(w) * static_cast<size_t>(h), Pixel{0,0,0});
    bool bottomUp = header.isBottomUp();
    for(int y = 0; y < h; ++y){
        in.read(reinterpret_cast<char*>(row.data()), rowSize);
        if(!in) {
            std::cerr<<"BMPImage::load: unexpected EOF while reading pixel data\n";
            return false;
        }
        int targetRow = bottomUp ? (h - 1 - y) : y;
        for(int x = 0; x < w; ++x){
            int src = x * 3;
            Pixel p;
            p.b = row[static_cast<size_t>(src) + 0];
            p.g = row[static_cast<size_t>(src) + 1];
            p.r = row[static_cast<size_t>(src) + 2];
            pixels[ static_cast<size_t>(targetRow) * static_cast<size_t>(w) + static_cast<size_t>(x) ] = p;
        }
    }
    return true;
}

bool BMPImage::save(const std::string &path) const {
    if(w <= 0 || h <= 0){
        std::cerr<<"BMPImage::save: invalid image size\n";
        return false;
    }
    std::ofstream out(path, std::ios::binary);
    if(!out){
        std::cerr<<"BMPImage::save: cannot open file for writing: "<<path<<"\n";
        return false;
    }
    // prepare header for output
    BMPHeader outHeader;
    outHeader.setDefaults(w, h); // set 24-bit bottom-up defaults
    outHeader.updateImageSizeAndFileSize(w, h);
    if(!outHeader.write(out)){
        std::cerr<<"BMPImage::save: failed to write header\n";
        return false;
    }
    int rowSize = outHeader.rowSizeBytes(w);
    std::vector<uint8_t> row(static_cast<size_t>(rowSize));
    for(int y = h - 1; y >= 0; --y){
        std::fill(row.begin(), row.end(), 0);
        for(int x = 0; x < w; ++x){
            const Pixel &p = pixels[ static_cast<size_t>(y) * static_cast<size_t>(w) + static_cast<size_t>(x) ];
            int idx = x * 3;
            row[static_cast<size_t>(idx) + 0] = p.b;
            row[static_cast<size_t>(idx) + 1] = p.g;
            row[static_cast<size_t>(idx) + 2] = p.r;
        }
        out.write(reinterpret_cast<const char*>(row.data()), rowSize);
        if(!out){
            std::cerr<<"BMPImage::save: failed while writing row\n";
            return false;
        }
    }
    return true;
}


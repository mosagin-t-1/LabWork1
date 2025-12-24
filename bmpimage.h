/*
 * Mosagin Timofey
 * st142155@student.spbu.ru
 * My lab work 1
 */

#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#include "bmpheader.h"
#include "pixel.h"

#include <vector>
#include <string>

class IImage {
public:
    virtual bool load(const std::string &path) = 0;
    virtual bool save(const std::string &path) const = 0;
    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual std::vector<Pixel>& data() = 0;
    virtual const std::vector<Pixel>& data() const = 0;
    virtual ~IImage() = default;
};

class BMPImage : public IImage {
    int w = 0;
    int h = 0;
    std::vector<Pixel> pixels;
    BMPHeader header;

public:
    BMPImage() = default;

    bool load(const std::string &path) override;
    bool save(const std::string &path) const override;
    int width() const override;
    int height() const override;
    std::vector<Pixel>& data() override;
    const std::vector<Pixel>& data() const override;
    void setSize(int ww, int hh);
};

#endif

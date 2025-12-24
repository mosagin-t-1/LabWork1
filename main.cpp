/*
 * Mosagin Timofey
 * st142155@student.spbu.ru
 * My lab work 1
 */

#include <iostream>
#include "bmpimage.h"
#include "filters.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: lab1 <input.bmp>\n";
        return 1;
    }

    BMPImage img;
    if (!img.load(argv[1])) {
        std::cerr << "Failed to load BMP\n";
        return 2;
    }

    std::cout << "Loaded BMP: " << img.width() << "x" << img.height() << "\n";

    auto cw = rotate_cw(img);
    cw.save("rot_cw.bmp");

    auto ccw = rotate_ccw(img);
    ccw.save("rot_ccw.bmp");

    auto g = gaussian_blur(cw);
    g.save("gauss.bmp");

    std::cout << "Done.\n";
    return 0;
}


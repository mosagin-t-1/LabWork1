#include "filters.h"
#include <algorithm>
#include "pixel.h"

BMPImage rotate_cw(const BMPImage &in) {
    int w = in.width(), h = in.height();
    BMPImage out;
    out.setSize(h, w);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            out.data()[x * h + (h - 1 - y)] = in.data()[y * w + x];
    return out;
}

BMPImage rotate_ccw(const BMPImage &in) {
    int w = in.width(), h = in.height();
    BMPImage out;
    out.setSize(h, w);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            out.data()[(w - 1 - x) * h + y] = in.data()[y * w + x];
    return out;
}

BMPImage gaussian_blur(const BMPImage &in) {
    int w = in.width(), h = in.height();
    BMPImage out;
    out.setSize(w, h);
    const int K[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
    int Ksum = 16;
    for(int y=0; y<h; y++) {
        for(int x=0; x<w; x++) {
            int rb=0, rg=0, rr=0;
            for(int ky=-1; ky<=1; ky++) {
                for(int kx=-1; kx<=1; kx++) {
                    int sx = std::clamp(x + kx, 0, w - 1);
                    int sy = std::clamp(y + ky, 0, h - 1);
                    const Pixel &p = in.data()[sy * w + sx];
                    int kval = K[ky + 1][kx + 1];
                    rb += p.b * kval;
                    rg += p.g * kval;
                    rr += p.r * kval;
                }
            }
            Pixel np;
            np.b = static_cast<uint8_t>(rb / Ksum);
            np.g = static_cast<uint8_t>(rg / Ksum);
            np.r = static_cast<uint8_t>(rr / Ksum);
            out.data()[y * w + x] = np;
        }
    }
    return out;
}


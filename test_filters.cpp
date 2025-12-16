#include "filters.h"
#include "bmpimage.h"
#include <gtest/gtest.h>
#include <vector>

BMPImage makePattern() {
    BMPImage img;
    img.setSize(3,2);
    for(int y=0;y<2;y++){
        for(int x=0;x<3;x++){
            Pixel p;
            p.r = static_cast<uint8_t>(x + y*10);
            p.g = p.r;
            p.b = p.r;
            img.data()[y*3 + x] = p;
        }
    }
    return img;
}

TEST(FiltersTest, RotateCWPositions) {
    BMPImage img = makePattern();
    BMPImage cw = rotate_cw(img);
    ASSERT_EQ(cw.width(), img.height());
    ASSERT_EQ(cw.height(), img.width());
    for(int y=0;y<img.height();++y){
        for(int x=0;x<img.width();++x){
            Pixel orig = img.data()[y*img.width() + x];
            Pixel after = cw.data()[ (x)*cw.width() + (cw.width()-1 - y) ]; 
            EXPECT_EQ(orig.r, after.r);
        }
    }
}

TEST(FiltersTest, RotateCCWPositions) {
    BMPImage img = makePattern();
    BMPImage ccw = rotate_ccw(img);
    ASSERT_EQ(ccw.width(), img.height());
    ASSERT_EQ(ccw.height(), img.width());
    for(int y=0;y<img.height();++y){
        for(int x=0;x<img.width();++x){
            Pixel orig = img.data()[y*img.width() + x];
            Pixel after = ccw.data()[(img.width()-1 - x)*ccw.width() + y];
            EXPECT_EQ(orig.r, after.r);
        }
    }
}

TEST(FiltersTest, Gaussian_Blur_AllZeroStaysZero) {
    BMPImage img;
    img.setSize(5,5);
    // all zero by default
    BMPImage g = gaussian_blur(img);
    for(auto &p : g.data()){
        EXPECT_EQ(p.r, 0);
        EXPECT_EQ(p.g, 0);
        EXPECT_EQ(p.b, 0);
    }
}

TEST(FiltersTest, Gaussian_Blur_SimpleCenter) {
    BMPImage img;
    img.setSize(3,3);
    for(auto &p : img.data()) { p.r = p.g = p.b = 0; }
    img.data()[1*3 + 1].r = 16; img.data()[1*3 + 1].g = 16; img.data()[1*3 + 1].b = 16;
    BMPImage g = gaussian_blur(img);
    Pixel center = g.data()[1*3 + 1];
    EXPECT_EQ(center.r, 4);
    EXPECT_EQ(center.g, 4);
    EXPECT_EQ(center.b, 4);
}


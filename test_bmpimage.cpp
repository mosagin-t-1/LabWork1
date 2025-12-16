#include "bmpimage.h"
#include <gtest/gtest.h>
#include <filesystem>

using namespace std;

BMPImage makeTestImage(int w, int h) {
    BMPImage img;
    img.setSize(w,h);
    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            Pixel p;
            p.r = static_cast<uint8_t>((x + y*10) % 256);
            p.g = static_cast<uint8_t>((x*2 + y*3) % 256);
            p.b = static_cast<uint8_t>((x*3 + y*5) % 256);
            img.data()[y*w + x] = p;
        }
    }
    return img;
}

TEST(BMPImageTest, SaveLoadRoundTrip_Small) {
    auto img = makeTestImage(3,2);
    std::string fname = "tmp_roundtrip.bmp";
    ASSERT_TRUE(img.save(fname));
    BMPImage loaded;
    ASSERT_TRUE(loaded.load(fname));
    ASSERT_EQ(img.width(), loaded.width());
    ASSERT_EQ(img.height(), loaded.height());
    ASSERT_EQ(img.data().size(), loaded.data().size());
    for(size_t i=0;i<img.data().size();++i){
        EXPECT_EQ(img.data()[i].r, loaded.data()[i].r);
        EXPECT_EQ(img.data()[i].g, loaded.data()[i].g);
        EXPECT_EQ(img.data()[i].b, loaded.data()[i].b);
    }
    std::filesystem::remove(fname);
}

TEST(BMPImageTest, Padding_RowSizeOddWidth) {
    auto img = makeTestImage(1,5);
    std::string fname = "tmp_pad.bmp";
    ASSERT_TRUE(img.save(fname));
    BMPImage loaded;
    ASSERT_TRUE(loaded.load(fname));
    ASSERT_EQ(img.width(), loaded.width());
    ASSERT_EQ(img.height(), loaded.height());
    for(size_t i=0;i<img.data().size();++i){
        EXPECT_EQ(img.data()[i].r, loaded.data()[i].r);
        EXPECT_EQ(img.data()[i].g, loaded.data()[i].g);
        EXPECT_EQ(img.data()[i].b, loaded.data()[i].b);
    }
    std::filesystem::remove(fname);
}


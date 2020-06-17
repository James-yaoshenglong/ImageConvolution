#ifndef CV_H
#define CV_H
#include <string>
using namespace std;
//使用int_32之类来保证在不同的机器上所占字节数一样
class BitMapFileHeader{ //文件头
    private:
        u_int32_t bfSize;  //文件大小
        u_int16_t fReserved1;  //保留字
        u_int16_t fReserved2;  //保留字
        u_int32_t fOffBits;  //位图数据偏移字节数	
};

class BitMapInfoHeader{ //位图信息头
    private:
        u_int32_t biSize;   //结构体长度
        int32_t biWidth;   //位图宽度
        int32_t biHeight;   //位图高度
        u_int16_t biPlanes;   //位图平面数
        u_int16_t biBitCount;  //颜色位数
        u_int32_t biCompression;   //压缩方式
        u_int32_t biSizeImage;   //实际位图数据占用的字节数
        int32_t biXPelsPerMeter;   //X方向分辨率
        int32_t biYPelsPerMeter;   //Y方向分辨率
        u_int32_t biClrUsed;   //使用的颜色数
        u_int32_t biClrImportant;   //重要颜色数
        friend class BMPImage;
};

class PixelBlock{ //像素点
    private:
        unsigned char B;
        unsigned char G;
        unsigned char R;
        friend class BMPImage;
};

class BMPImage{
    private:
        int width;
        int height;
        int channels;
        PixelBlock** imageData;
        BitMapFileHeader bmpFileHeader;
        BitMapInfoHeader bmpInfoHeader;
        unsigned short fileType;  //Picture type Sign
    public:
        BMPImage(const char*);
        ~BMPImage();
        bool save(const char*);
};
#endif

#include <iostream>
#include <fstream>
#include "cv.h"
using namespace std;

BMPImage::BMPImage(const char* path):bmpFileHeader(),bmpInfoHeader(){
    ifstream pFile;

    /**0. Init Values**/
    //BMP Image file info
    channels = 3;
    width = 0;
    height = 0;
    //Data Content Parameters
    int offset = 0;
    unsigned char offset_char;

    /**1. File Open**/
    pFile.open(path,std::ios::binary);
    if(!pFile){
        cout<<"Unable to open the file!"<<endl;
        return;
    }

    /**2. Read Image File Content**/
    pFile.read((char*)&fileType,sizeof(fileType));
    if (fileType == 0x4D42){ //judge whether it is a bit map image
        //2.1 Read Header
        pFile.read((char*)&bmpFileHeader,sizeof(BitMapFileHeader));

        //2.2 Get Picture Info
        pFile.read((char*)&bmpInfoHeader,sizeof(BitMapInfoHeader));
        if(bmpInfoHeader.biBitCount == 24){
            width = bmpInfoHeader.biWidth;
            height = bmpInfoHeader.biHeight;
            imageData = new PixelBlock* [height];
            for(int i=0;i<height;i++){
                imageData[i] = new PixelBlock [width];
            }
            offset = ((channels*width)%4 != 0)*(4-(channels*width)%4); //offset in bmpFile,和4之间的偏移量

            /**Most Important**/
            //2.3 Reading ImageData
            for (int i=height-1; i>=0; i--){
                for (int j=0; j<width; j++){
                    pFile.read((char*)&imageData[i][j], sizeof(PixelBlock));
                }
                if (offset != 0){
                    for (int j=0; j<offset; j++){
                        pFile.read((char*)&offset_char, sizeof(unsigned char));
                    }
                }
            }
        }
    }
    pFile.close();
}

BMPImage::~BMPImage(){
    for(int i=0;i<height;i++){
        delete [] imageData[i];
    }
    delete [] imageData;
}

bool BMPImage::save(const char* path){
    ofstream pFile;
    int rowLen;
    int offset;
    unsigned char offset_char;

    pFile.open(path,std::ios::binary);
    if (!pFile){
        return false;
    }
    if(channels == 3){
        rowLen = channels*width;
        offset = (rowLen)%4;
        if (offset != 4){
            rowLen += 4-offset;
        }
        pFile.write((char*)&fileType,sizeof(fileType));
        //Write Header
        pFile.write((char*)&bmpFileHeader,sizeof(bmpFileHeader));
        //Write Info
        pFile.write((char*)&bmpInfoHeader,sizeof(bmpInfoHeader));
        //Write Image Data
        for(int i=height-1;i>=0;i--){
            for(int j=0;j<width;j++){
                pFile.write((char*)&imageData[i][j],sizeof(PixelBlock));
            }
            if (offset!=0){
                for (int j=0; j<offset; j++){
                    offset_char = 0;
                    pFile.write((char*)&offset_char, sizeof(unsigned char));
                }
            }
        }
    }
    pFile.close();
    return true;
}
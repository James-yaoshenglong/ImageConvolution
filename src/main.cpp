#include <iostream>
#include <cstring>
#include "cv.h"
#include "main.h"
using namespace std;


int main(int argc, char* argv[]){
    if(argc == 1){
        cout << "Welcome to BMP Editor!"<<endl;
        giveHelp();
        return 0;
    }
    else if(argc == 2){
        cout<<"More arguments needed!"<<endl;
        giveHelp();
        return 1;
    }
    else if(argc == 3){
        BMPImage image(argv[2]);
        //指针要用stringcmp函数比较相等而不能用==
        if(strcmp(argv[1],"-o") == 0 || strcmp(argv[1],"--outline") == 0){//边缘检测
            image.convolution(oKernel);
        }
        else if (strcmp(argv[1],"-G") == 0 || strcmp(argv[1],"--Gaussian") == 0){//高斯模糊
            image.convolution(GKernel);
        }
        else if (strcmp(argv[1],"-s") == 0 || strcmp(argv[1],"--sculpture") == 0){
            image.convolution(skernel);
        }
        else{
            cout<< "Command has not been found!"<<endl;
            giveHelp();
            return 1;
        }
        image.save("./result/result.bmp");
    }
    else{
        cout<<"More arguments than needed!"<<endl;
        giveHelp();
        return 1;
    }
    return 0;
}
//后续功能添加：实现命令行操作，添加更多的卷积核，添加图像翻转等操作
//还有result文件夹需要手动创建的问题？？？，可以利用makefile来搞这个命令
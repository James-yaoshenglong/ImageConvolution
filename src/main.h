#ifndef MAIN_H
#define MAIN_H

#include <iostream>
using namespace std;

void giveHelp(){
    cout<<"Usage: ./editor [options] [filename(should be bmp file!)]"<<endl;
    cout<<"options:"<<endl;
    cout<<"\t-o or --outline\t\tOutline for the image."<<endl;
    cout<<"\t-G or ----Gaussian\tGaussian vague for the image."<<endl;
    cout<<"\t-s or ----sculpture\tSculpture for the image."<<endl;
    cout<<"\t--help\t\t\tDisplay this help information."<<endl;
}

double oKernel[3][3] = {{-0.125,-0.125-0.125},{-0.125,1,-0.125},{-0.125,-0.125,-0.125}};
double GKernel[3][3] = {{0.089 , 0.112 , 0.089},{0.112 , 0.100, 0.112},{0.089 , 0.112 , 0.089}};
double skernel[3][3] = {{-0.5,0,0},{0,0,0},{0,0,0.5}};

#endif
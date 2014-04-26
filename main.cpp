#include "mainwindow.h"
#include "clrman.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    //    QApplication colorManipulation(argc,argv);
    //    MainWindow mainwindow;
    //    mainwindow.show();
    //    return colorManipulation.exec();
    cv::Mat src = cv::imread("/Users/timfeirg/Google Drive/OpenCV/DIP3E_Original_Images_CH06/Fig0648(a)(lenna-noise-R-gauss-mean0-var800).tif",0);
    cv::Mat rgb_src = cv::imread("/Users/timfeirg/Google Drive/OpenCV/DIP3E_Original_Images_CH06/Fig0608(RGB-full-color-cube).tif");
    cv::Mat dst;
    dst.create(src.size(),CV_8UC3);

//        clrman::cvt2websafe(rgb_src,dst);
    double upperbound = 150.0;
    double lowerbould = 0.0;
    int channel = CLRMAN_RED;
    clrman::pseudoColor<uchar, cv::Vec3b>(src, dst, upperbound, lowerbould, channel);
    cv::imshow("src", src);
    cv::imshow("dst",dst);
    cv::waitKey();
    return 1;
}



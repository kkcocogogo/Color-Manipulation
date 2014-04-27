#include "mainwindow.h"
#include "clrman.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//        QApplication colorManipulation(argc,argv);
//        MainWindow mainwindow;
//        mainwindow.show();
//        return colorManipulation.exec();



    cv::Mat src = cv::imread("/Users/timfeirg/Google Drive/OpenCV/DIP3E_Original_Images_CH06/Fig0627(a)(WashingtonDC Band3-RED).TIF",0);
    cv::Mat rgb_src = cv::imread("/Users/timfeirg/Google Drive/OpenCV/DIP3E_Original_Images_CH06/Fig0608(RGB-full-color-cube).tif");
    cv::Mat rgb_635 = cv::imread("/Users/timfeirg/Google Drive/OpenCV/DIP3E_Original_Images_CH06/Fig0635(middle_row_left_chalk ).tif");
    cv::Mat dst;

    cv::Mat grad = cv::imread("/Users/timfeirg/Documents/Color-Manipulation/gradBW.tif",0);
    dst.create(src.size(),CV_8UC3);

//        clrman::cvt2websafe(rgb_src,dst);
    double upperbound = 90.0;
    double lowerbould = 60.0;
    int channel = CLRMAN_RED;
    clrman::histoEqual(rgb_635,dst);
//    clrman::pseudoColor(grad,dst);
//    clrman::pseudoColor<uchar, cv::Vec3b>(src, dst, upperbound, lowerbould, channel);
//    cv::imshow("src", grad);
    cv::imshow("rgb 635", rgb_635);
//    cv::imshow("src",src);
    cv::imshow("dst",dst);
    cv::waitKey();
    return 1;
}



#include "mainwindow.h"
#include "clrman.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    {
        using namespace cv;
        Mat gradBW = cv::imread("/Users/timfeirg/Documents/Color-Manipulation/gradBW.png",0);
        Mat rgbcube = cv::imread("/Users/timfeirg/Documents/Color-Manipulation/WebSafeTarget.png");
        Mat rgbimage = cv::imread("/Users/timfeirg/Documents/Color-Manipulation/rgbImage.png");
        Mat washinton = imread("/Users/timfeirg/Documents/Color-Manipulation/washinton.png");
        Mat dst;
        // pseudo color problem
        clrman::pseudoColor(gradBW,dst);
        imshow("gradient",gradBW);
        imshow("pseudo color map",dst);
        waitKey();
        clrman::pseudoColor(washinton,dst);
        imshow("real case BW image",dst);
        imshow("washinton to be convert to pseudo color",washinton);
        waitKey();
        // web safe color
        clrman::cvt2websafe(rgbcube,dst);
        imshow("HSI cube",rgbcube);
        imshow("web safe color",dst);
        waitKey();
        // histogram equalization
        clrman::histoEqual(rgbimage,dst);
        imshow("after histo equalization",dst);
        imshow("read case rgb image",rgbimage);
        waitKey();
    }

    return 1;
    /****************************************
     * this is the code of my unfinished
     * project, I'm keeping it as a debugging
     * area, have fun with everything above
    ****************************************/
    //        QApplication colorManipulation(argc,argv);
    //        MainWindow mainwindow;
    //        mainwindow.show();
    //        return colorManipulation.exec();
}



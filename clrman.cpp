#include "clrman.h"

/*****************************************************
 * clrman::cvt2websafe function
 * this function works with gray or rgb images with
 * depth of 8/16
*****************************************************/
void clrman::cvt2websafe(cv::Mat &src, cv::Mat &dst) {
    int channels = src.channels();
    assert(channels == 1 || channels == 3);
    // force convert to depth of 8, initialize the size of dst
    if (src.depth() > sizeof(uchar) || dst.size() != src.size()) {
        if(channels == 3) {
            src.convertTo(src, CV_8UC3);
            dst = cv::Mat(src.size(), CV_8UC3);
        }
        else {
            src.convertTo(src, CV_8UC1);
            dst = cv::Mat(src.size(), CV_8UC1);
        }
    }

    // this will bring efficiency, check out:
    // http://docs.opencv.org/doc/tutorials/core/how_to_scan_images/how_to_scan_images.html
    int rows = src.rows * channels;
    int cols = src.cols;
    if(src.isContinuous()) {
        cols *= rows;
        rows = 1;
    }

    int i,j;
    uchar* p_src;
    uchar* p_dst;
    for(i = 0; i < rows; ++i) {
        p_src = src.ptr<uchar>(i);
        p_dst = dst.ptr<uchar>(i);
        for(j = 0; j < cols; ++j) {
            p_dst[j] = ((p_src[j] + 26) / 51) * 51;
        }
    }
}

/*****************************************************
 * this is the standard pseudo color conversion
 * please refer to this website:
 * http://blog.damiles.com/2010/01/pseudocolor-implementation-with-opencv/
 * this is where I get the constants for the following program
 * the output of this function is fixed to cv::Vec3d
*****************************************************/
void clrman::pseudoColor(cv::Mat &gray_src, cv::Mat &rgb_dst) {

    // create a normalized copy of source image, this new source'll be used throughout the function
    cv::Mat double_src;
    gray_src.convertTo(double_src, CV_64F);
    // normalize double_src so that sine calculations will work
    cv::normalize(double_src, double_src, M_PI, 0, cv::NORM_MINMAX);
    // create dst as 64F
    rgb_dst = cv::Mat_<cv::Vec3d>(gray_src.size());
    // create iterators
    cv::MatIterator_<double> it_src = double_src.begin<double>();
    cv::MatIterator_<cv::Vec3d> it_dst = rgb_dst.begin<cv::Vec3d>();
    cv::MatIterator_<double> it_end = double_src.end<double>();

    for(; it_src != it_end; it_src ++, it_dst ++) {
        double pixGrayLevel_src = *it_src;
    // you can play with different theta and p value
        (*it_dst)[0] = fabs(sin( pixGrayLevel_src * 2));
        (*it_dst)[1] = fabs(sin( pixGrayLevel_src * 2 + (-0.1) * M_PI));
        (*it_dst)[2] = fabs(sin( pixGrayLevel_src * 2 + (-0.3) * M_PI));
    }
}

/*****************************************************
 * this function implements histogram equalization on all
 * three channels separately
 * as a bonus it also takes gray scale image as well
 * notice that performing HE on each RGB channel is
 * WRONG, this is purely for demo purpose
*****************************************************/
void clrman::histoEqualSep(cv::Mat &src, cv::Mat &dst) {
    int channels = src.channels();
    // crash the program if images with weird formats comes in
    assert(channels == 1 || channels == 3);

    // for gray scale images
    if(channels == 1) cv::equalizeHist(src, dst);
    // for rgb images
    else if(channels == 3){
        cv::Mat channelContainer[3];
        cv::split(src,channelContainer);
        // equalize all 3 channels
        cv::equalizeHist(channelContainer[0],channelContainer[0]);
        cv::equalizeHist(channelContainer[1],channelContainer[1]);
        cv::equalizeHist(channelContainer[2],channelContainer[2]);
        // merge into one rgb mat
        cv::merge(channelContainer,3,dst);
    }
}

/*****************************************************
 * this function implements histogram equalization on
 * YUV space, that way we just have to deal with channel
 * Y, and leave the color information alone so that
 * the color don't get distorted
*****************************************************/
void clrman::histoEqual(cv::Mat &src, cv::Mat &dst) {
    int channels = src.channels();
    assert(channels == 3 || channels == 1);
    if(channels == 1) cv::equalizeHist(src, dst);
    else {
        // convert source image to YUV space
        cv::cvtColor(src,dst,CV_BGR2YCrCb);
        // split into YUV channels
        cv::Mat channelContainers[3];
        cv::split(dst,channelContainers);
        // perform histogram equalization only to Y channel
        cv::equalizeHist(channelContainers[0],channelContainers[0]);
        // merge into one piece
        cv::merge(channelContainers,3,dst);
        // convert back to rgb so that it gets displayed properly
        cv::cvtColor(dst,dst,CV_YUV2BGR);
    }
}

/*****************************************************
 * I tried (and failed) to design a function that convert
 * images with arbitary depth to pseudo color with user-
 * specified thretholds.
 * right now THIS FUNCTION IS CONSIDERED USELESS
 * clrman::pseudoColor function
 * the function work with RGB images with arbitrary depth
 * there's no reason to use double for threthold values,
 * but here the shortest data type appropriate depends on
 * the color depth of the source image.
 *
 * to specify channel, use something like CLRMAN_BLUE
*****************************************************/

template<typename GRAY_TYPE, typename RGB_TYPE>
void clrman::pseudoColor(cv::Mat &gray_src, cv::Mat &rgb_dst, double upperBound, double lowerBound , int channel) {
    // calculate lootup table for each channel
    // but what size should it take?
    // forget about CLUT
    assert(
                gray_src.channels() == 1 &&
                rgb_dst.channels() == 3 &&
                gray_src.rows == rgb_dst.rows &&
                gray_src.cols == rgb_dst.cols);

    cv::MatIterator_<GRAY_TYPE> it_src = gray_src.begin<GRAY_TYPE>();
    cv::MatIterator_<RGB_TYPE> it_dst = rgb_dst.begin<RGB_TYPE>();
    cv::MatIterator_<GRAY_TYPE> it_end = gray_src.end<GRAY_TYPE>();

    for(; it_src != it_end; it_src ++, it_dst ++) {
        double pixGrayLevel_src = *it_src;
        // if the gray level of that pixel falls outside the area we specified, copy the value to all 3 channels
        // the first condition is mostly likely to happen
        if (
                pixGrayLevel_src > upperBound ||
                pixGrayLevel_src < lowerBound
                ) {
            (*it_dst)[0] = pixGrayLevel_src;
            (*it_dst)[1] = pixGrayLevel_src;
            (*it_dst)[2] = pixGrayLevel_src;
        }
        // if the program ever runs to here, that means we have a pixel that falls in between our interested area, move it to r/g/b channel as specified
        else {
            // set the pixel in dst to zero, and then set r/g/b channel to current pixel gray level
            (*it_dst)[0] = 0;
            (*it_dst)[1] = 0;
            (*it_dst)[2] = 0;
            (*it_dst)[channel] = pixGrayLevel_src;
        }
    }
}
template void clrman::pseudoColor<uchar, cv::Vec3b>(cv::Mat &gray_src, cv::Mat &rgb_dst, double upperBound, double lowerBound , int channel);

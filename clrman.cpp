#include "clrman.h"

// this file includes all clrman(color manipulation) functions

void clrman::cvt2websafe(cv::Mat& src, cv::Mat& dst) {
    assert(src.type()==16);
    // preallocate size to speed things up, not quite sure of its merits
    if (dst.size() != src.size()) {
        dst = cv::Mat_<cv::Vec3b>(src.size());
    }
    cv::MatIterator_<cv::Vec3b>
            it_src = src.begin<cv::Vec3b>(),
            it_dst = dst.begin<cv::Vec3b>(),
            it_end = src.end<cv::Vec3b>();

    // round all value to the nearest multiple of 51 to maintain accuracy
    // better ways to do this is using a lookup table, but I'm somehow stuck at generating such array
    // DONT use Mat::at in this case, MatIterator are for scanning images ad-hoc
    for( ; it_src != it_end; it_src ++, it_dst ++) {
        (*it_dst)[0] = (((*it_src)[0] + 26) / 51) * 51;
        (*it_dst)[1] = (((*it_src)[1] + 26) / 51) * 51;
        (*it_dst)[2] = (((*it_src)[2] + 26) / 51) * 51;
    }
}

// trying to design a function template that work with RGB images with arbitrary depth
// if there's any way that I can use different data type other than double to hold the threthold!
// to specify channel, use something like CLRMAN_BLUE
template<typename GRAY_TYPE, typename RGB_TYPE>
void clrman::pseudoColor(cv::Mat &gray_src, cv::Mat &rgb_dst, double upperBound, double lowerBound , int channel) {
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

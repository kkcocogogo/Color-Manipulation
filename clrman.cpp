#include "clrman.h"

/*****************************************************
 * clrman::cvt2websafe function
*****************************************************/

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

/*****************************************************
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
    // obtain a copy of the brightest value within source image
    //    const double
    //            src_max = *(std::max_element(it_src, it_end)),
    //            src_min = *(std::min_element(it_src, it_end));

    for(; it_src != it_end; it_src ++, it_dst ++) {
        double pixGrayLevel_src = *it_src;

        (*it_dst)[0] = fabs(sin( pixGrayLevel_src * 2));
        (*it_dst)[1] = fabs(sin( pixGrayLevel_src * 2 + (-0.1) * M_PI));
        (*it_dst)[2] = fabs(sin( pixGrayLevel_src * 2 + (-0.3) * M_PI));

//        {
//            using namespace std;
//            using namespace cv;
//            imshow("current",rgb_dst);
//            waitKey(1);
//            cout<<*it_dst<<endl;
//            cv::waitKey();
//        }

    }
    // normalize dst so that it can be perceived by eye
//    cv::normalize(rgb_dst, rgb_dst, 1, 0, cv::NORM_MINMAX);
}

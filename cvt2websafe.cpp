#include <opencv2/core/core.hpp>

void cvt2websafe(cv::Mat& src, cv::Mat& dst) {
assert(src.type()==16);
    // preallocate size to speed things up, not quite sure of its merits
    if (dst.size() != src.size()) {
        dst = cv::Mat_<cv::Vec3b>(src.size());
    }
    cv::MatIterator_<cv::Vec3b>
            it_src = src.begin<cv::Vec3b>(),
            it_end = src.end<cv::Vec3b>(),
            it_dst = dst.begin<cv::Vec3b>();

    // round all value to the nearest multiple of 51 to maintain accuracy
    // better ways to do this is using a lookup table, but I'm somehow stuck at generating such array

    for( ; it_src != it_end; it_src ++, it_dst ++) {
        (*it_dst)[0] = (((*it_src)[0] + 26) / 51) * 51;
        (*it_dst)[1] = (((*it_src)[1] + 26) / 51) * 51;
        (*it_dst)[2] = (((*it_src)[2] + 26) / 51) * 51;
    }
}


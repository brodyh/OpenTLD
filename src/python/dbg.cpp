#include <iostream>
#include <vector>
#include <string>
#include <opencv/cv.h>

std::string type2str(int type) {
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
  case CV_8U:  r = "8U"; break;
  case CV_8S:  r = "8S"; break;
  case CV_16U: r = "16U"; break;
  case CV_16S: r = "16S"; break;
  case CV_32S: r = "32S"; break;
  case CV_32F: r = "32F"; break;
  case CV_64F: r = "64F"; break;
  default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}


int main(int argc, char **argv) {
  cv::Mat img(100, 100, CV_8UC1, cv::Scalar(1));
  cv::Mat out, outSquared;
  cv::integral(img, out, outSquared);
  out = out(cv::Rect(1, 1, img.cols, img.rows));
  std::cout << "out Size " << out.size()
	    << " Type " << type2str(out.type()) << std::endl;
  std::cout << "outSquared Size " << outSquared.size()
	    << " Type " << type2str(outSquared.type()) << std::endl;
}

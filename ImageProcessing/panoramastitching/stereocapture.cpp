#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include <assert.h>

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

/* ************************************************************** */
/* ************************************************************** */

int main (int argc, char ** argv)
{
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <number>\n", argv[0]);
    exit(1);
  }

  int counter=atoi(argv[1]);
  char leftfname[80];
  char rightfname[80];
  sprintf (leftfname, "left%d.jpg",   counter);
  sprintf (rightfname, "right%d.jpg", counter);
  
  // open video capture devices
  VideoCapture cap0(0);
  VideoCapture cap1(1);
  
  cap0.open(0);
  cap1.open(1);

  Mat leftimg, rightimg;
  cap0 >> rightimg;
  cap1 >> leftimg;

  imwrite(leftfname, leftimg);
  imwrite(rightfname, rightimg);
  
  return 0;
}

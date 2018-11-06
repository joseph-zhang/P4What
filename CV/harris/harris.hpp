#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/* Auxiliary type :: Definition of ResponsePoint interface */
struct ResponsePoint {
  ResponsePoint(){}
  ResponsePoint(Point p, float res):
    response(res), point(p){}

  float response;
  Point point;
};

/* the rule to assign the sequence of ResponsePoint vector */
struct by_response {
  bool operator()(ResponsePoint const &left, ResponsePoint const &right) {
        return left.response > right.response;
    }
};

/* Auxiliary type :: Definition of Deriv interface */
struct Deriv {
  Deriv(){}
  Deriv(Mat I_x, Mat I_y, Mat I_xy) :
    Ix(I_x), Iy(I_y), Ixy(I_xy){}
	Mat Ix;
	Mat Iy;
	Mat Ixy;
};

/* Definition of Harris interface */
class Harris {
public:
  Harris(Mat img, float alpha, int kernelSize);
  vector<ResponsePoint> NMS(int topNum, int suppressionRadius);

private:
  Mat Rgb2Gray(Mat& img);
	Deriv computeDerivs(Mat& img);
	Deriv gaussianOp(Deriv& derives, int kernelSize);
	Mat computeResponses(Deriv& derives, float alpha);
	Mat gaussFilter(Mat& img, int kernelSize);
	Mat responseM;
};

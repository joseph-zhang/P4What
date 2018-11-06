#include <opencv2/opencv.hpp>
#include "harris.hpp"
#include <vector>
using namespace std;
using namespace cv;

/* Harris interface definition */
Harris::Harris(Mat img, float alpha, int kernelSize) {
  Mat grayImg = Rgb2Gray(img);
  Deriv derivatives = computeDerivs(grayImg);
  Deriv bluredDerivatives = gaussianOp(derivatives, kernelSize);
  responseM = computeResponses(bluredDerivatives, alpha);
}

/* Function to transfer RGB image to gray image */
Mat Harris::Rgb2Gray(Mat& img) {
  Mat grayImg(img.rows, img.cols, CV_32F);

  for (int i = 0; i < img.rows; i++) {
    for (int j = 0; j < img.cols; j++) {
      grayImg.at<float>(i,j) =
        0.114 * img.at<cv::Vec3b>(i,j)[0] +
        0.587 * img.at<cv::Vec3b>(i,j)[1] +
        0.299 * img.at<cv::Vec3b>(i,j)[2];
        }
    }

  return grayImg;
}

/*
 * Fucntion to process the given derives
 * -------------------------------------------
 * derives : the input Deriv data;
 * kernelSize : the size of gaussian kernel.
 * -------------------------------------------
 */
Deriv Harris::gaussianOp(Deriv& derives, int kernelSize) {
  if(kernelSize == 0)
    return derives;

  Deriv resDeriv;

  resDeriv.Ix  = gaussFilter(derives.Ix,  kernelSize);
  resDeriv.Iy  = gaussFilter(derives.Iy,  kernelSize);
  resDeriv.Ixy = gaussFilter(derives.Ixy, kernelSize);

  return resDeriv;
}

/* Function to compute derivatives of a given image */
Deriv Harris::computeDerivs(Mat& img) {
  Mat sobelH = (Mat_<float>(3,3) << -1,-2,-1,0,0,0,1,2,1);
  Mat sobelV = (Mat_<float>(3,3) << -1,0,1,-2,0,2,-1,0,1);
  Mat Ix, Iy;

  filter2D(img, Ix, CV_32F, sobelH);
  filter2D(img, Iy, CV_32F, sobelV);

  Mat Ixy(Ix.rows, Ix.cols, CV_32F);

  for(int i = 0; i < Ix.rows; i++) {
    for(int j = 0; j < Ix.cols; j++) {
      Ixy.at<float>(i,j) = Ix.at<float>(i,j) * Iy.at<float>(i,j);
    }
  }
  imshow("Ix",Ix);
  waitKey(0);
  imshow("Iy", Iy);
  waitKey(0);
  return Deriv(Ix, Iy, Ixy);
}

/*
 * Function to compute response matrix.
 * the formula is \det(A) - \alpha \mathrm{trace}(A)^2 = \lambda_0\lambda_1 - \alpha(\lambda_0 + \lambda_1)^2
 */
Mat Harris::computeResponses(Deriv& derives, float alpha) {
  Mat resM(derives.Iy.rows, derives.Ix.cols, CV_32F);

  for(int i = 0; i < derives.Iy.rows; i++) {
    for(int j = 0; j < derives.Iy.cols; j++) {
      float   a11, a12, a21, a22;

      a11 = derives.Ix.at<float>(i,j) * derives.Ix.at<float>(i,j);
      a22 = derives.Iy.at<float>(i,j) * derives.Iy.at<float>(i,j);
      a21 = derives.Ix.at<float>(i,j) * derives.Iy.at<float>(i,j);
      a12 = derives.Ix.at<float>(i,j) * derives.Iy.at<float>(i,j);

      float det = a11*a22 - a12*a21;
      float trace = a11 + a22;

      resM.at<float>(i,j) = abs(det - alpha * trace*trace);
    }
  }
  imshow("Response", resM);
  waitKey(0);
  return resM;
}

/* Function to do gaussian blur */
Mat Harris::gaussFilter(Mat& img, int kernelSize) {
  Mat tmp(img.rows, img.cols, CV_32F);
  Mat gaussKernel = cv::getGaussianKernel(kernelSize,1);
  filter2D(img, tmp, CV_32F, gaussKernel);
  return tmp;
}

/*
 * Function to do non-maximal suppression
 * -------------------------------------------------------------------------
 * topNum : the number of key point of show on the given image;
 * suppressionRadius : the parameter to control the algorithm sensitivity.
 * -------------------------------------------------------------------------
 */
vector<ResponsePoint> Harris::NMS(int topNum, int suppressionRadius) {
  Mat maskM(responseM.rows, responseM.cols, CV_32F, Scalar::all(0));

  vector<ResponsePoint> sortedPoints;
  for (int i = 0; i < responseM.rows; i++) {
    for (int j = 0; j < responseM.cols; j++) {
      Point p(i,j);

      sortedPoints.push_back(ResponsePoint(p, responseM.at<float>(i,j)));
    }
  }

  sort(sortedPoints.begin(), sortedPoints.end(), by_response());
  vector<ResponsePoint> topPoints;

  int counter = 0;
  while(topPoints.size() < topNum) {
    if(counter == sortedPoints.size()) break;

    int supRows = maskM.rows;
    int supCols = maskM.cols;

    if(maskM.at<int>(sortedPoints[counter].point.x, sortedPoints[counter].point.y) == 0) {
      for (int i = -suppressionRadius; i <= suppressionRadius; i++) {
        for (int j = -suppressionRadius; j <= suppressionRadius; j++) {
          int sx = sortedPoints[counter].point.x + i;
          int sy = sortedPoints[counter].point.y + j;

          if(sx > supRows) sx = supRows;
          if(sx < 0) sx = 0;
          if(sy > supCols) sy = supCols;
          if(sy < 0) sy = 0;

          maskM.at<int>(sx, sy) = 1;
        }
      }
      topPoints.push_back(sortedPoints[counter]);
    }
    counter++;
  }
  return topPoints;
}

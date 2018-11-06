#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

/* Util class interface */
class Util {
public:
  static void displayImage(Mat& img);
  static void displayMat(Mat& img);
  static Mat  drawPointOnImg(Mat& img, vector<ResponsePoint> points, int radius);
  static void saveResPoints(vector<ResponsePoint> points, string filename);
};

/* Function to display a Mat as image */
void Util::displayImage(Mat& img) {
  namedWindow("testImg", 1);
  imshow("testImg", img);
  waitKey(0);
}

/* Function to print a Mat */
void Util::displayMat(Mat& img) {
  cout << "-= Display Matrix =-";
  int rowCount = 0;
  for (int i = 0; i < img.rows; i++) {
    cout << endl;
    int colCount = 0;
    for (int j = 0; j < img.cols; j++) {
      cout << img.at<float>(i,j) << ", ";
      colCount++;
    }
    rowCount++;
    cout << " -> " << colCount << "cols";
  }
  cout << "-> " << rowCount << "rows" << endl;
}

/*
 * Function to draw points on a given image.
 * ---------------------------------------------
 * img : input image;
 * points : a vector of response points;
 * radius : parameter to control the circle.
 * ----------------------------------------------
 */
Mat Util::drawPointOnImg(Mat& img, vector<ResponsePoint> points, int radius) {
  Mat retImg;
  img.copyTo(retImg);
  for(vector<ResponsePoint>::iterator it = points.begin(); it != points.end(); ++it) {
    Point center = (*it).point;
    for(int i = -radius; i < radius; i++) {
      retImg.at<Vec3b>(Point(center.y+i, center.x+radius)) = Vec3b(0, 0, 255);
			retImg.at<Vec3b>(Point(center.y+i, center.x-radius)) = Vec3b(0, 0, 255);
			retImg.at<Vec3b>(Point(center.y-radius, center.x+i)) = Vec3b(0, 0, 255);
			retImg.at<Vec3b>(Point(center.y+radius, center.x+i)) = Vec3b(0, 0, 255);
		}
		retImg.at<Vec3b>(Point(center.y,center.x)) = Vec3b(0, 255, 0);
	}
	return retImg;
}

/*
 * Function to save the position (x,y) of keypoints
 * --------------------------------
 * points : top points to save;
 * filename : the path of target file.
 * --------------------------------
 */
void Util::saveResPoints(vector<ResponsePoint> points, string filename) {
  ofstream out(filename);
  for(auto it = points.begin(); it != points.end(); it++) {
    Point p = (*it).point;
    if(out.is_open()) out << p.x << " " << p.y << "\n";
  }
  out.close();
}

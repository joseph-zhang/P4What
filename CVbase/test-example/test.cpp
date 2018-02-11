#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    std::cout << "Read an image and display " << std::endl;
    cv::Mat image = imread("lena.jpg");
    imshow("lena",image);
    waitKey(0);
    return 0;
}

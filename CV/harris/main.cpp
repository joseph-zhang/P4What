#include <opencv2/opencv.hpp>
#include <string>
#include "harris.hpp"
#include "util.hpp"
#include "args.hxx"

using namespace cv;
using namespace std;
using namespace args;

int main(int argc, char** argv) {
  /* Argparse Definitions */
  args::ArgumentParser    parser("");
  args::HelpFlag          help(parser, "help", "Display this help menu", {'h', "help"});
  args::ValueFlag<string> img_path(parser, "img_path", "the test image path", {"img_path"});
  args::ValueFlag<float>  alpha(parser, "alpha", "alpha value for response", {"alpha"});
  args::ValueFlag<int>    kernelSize(parser, "kernelSize", "the size of gaussian kernel", {"kernelSize"});
  args::ValueFlag<int>    num_point(parser, "num_point", "the points of keypoint", {"num_point"} );
  args::ValueFlag<int>    suppressionRadius(parser, "suppresionRadius", "value of suppression radius", {"sr"});

  /* Default values of parameters */
  string img_dir("./test.jpg");
  float alpha_val = 0.25;
  int kernelSize_val = 3;
  int num_point_val = 50;
  int suppressionRadius_val = 10;

  /* Parse the CLI parameters */
  try{
    parser.ParseCLI(argc, argv);
  }
  catch(args::Help){
    cout << parser;
    return 0;
  }
  if(img_path) {img_dir = args::get(img_path);}
  if(alpha) {alpha_val = args::get(alpha);}
  if(kernelSize) {kernelSize_val = args::get(kernelSize);}
  if(num_point) {num_point_val = args::get(num_point);}
  if(suppressionRadius) {suppressionRadius_val = args::get(suppressionRadius);}

  /* Do harris keyPoint detection */
  Mat img;
  img = imread(img_dir);
  Harris harris(img, alpha_val, kernelSize_val);
  vector<ResponsePoint> resPts = harris.NMS(num_point_val, suppressionRadius_val);
  cout << resPts.size() << " Points" << endl;
  Mat _img = Util::drawPointOnImg(img, resPts, 3);
  imshow("HarrisCornerDetector", _img);
  waitKey(0);
}

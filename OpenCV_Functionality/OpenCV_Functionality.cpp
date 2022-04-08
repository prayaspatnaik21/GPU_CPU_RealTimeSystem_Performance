#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(void) {
	
	// Read image in GrayScale mode
	Mat image = imread("../resources/Images/Sam_0.jpg",1);
	Size outDim = image.size();

	cout << outDim << endl;

	Mat result;

	Point center = Point( image.cols/2, image.rows/2 );
	double angle = 90.0;
	double scale = 1;

	Mat rot_mat = getRotationMatrix2D( center, angle, scale );
	warpAffine( image,result, rot_mat, image.size() );

	imwrite("RotatedImage.jpg",result);
	waitKey(0);
	return 0;
}

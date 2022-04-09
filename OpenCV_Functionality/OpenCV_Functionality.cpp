#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
using namespace std::chrono;

int main(void) {

	// Read image in GrayScale mode
	Mat image = imread("../resources/Images/Sam_0.jpg",1);
	
	Size outDim = image.size();

	cout << outDim << endl;

	Mat result;

	Point center = Point( image.cols/2, image.rows/2 );
	double angle = 90.0;
	double scale = 1;

	auto start = high_resolution_clock::now();
	Mat rot_mat = getRotationMatrix2D( center, angle, scale );
	warpAffine( image,result, rot_mat, image.size() );
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << duration.count() << endl;
	cv::imshow(" image1", result);
	cv::waitKey(0);
	
	return 0;
}

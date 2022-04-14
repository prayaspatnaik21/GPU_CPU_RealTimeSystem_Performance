#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
using namespace std::chrono;

int main(void) {

	// Read image in GrayScale mode

	int i{0};
	string fixedPath = "../resources/Images/Sam_";
	string VariableFileName;

	while(i < 5)
	{
		Mat result;

		VariableFileName = std::to_string(i)+ ".jpg";
		string ResultPath = fixedPath + VariableFileName;
		Mat image = imread(ResultPath,1);

		imshow("Image",image);
		waitKey(0);

		cout << "Image Resolution" << " " << image.cols << "X" << image.rows << endl;

		Point center = Point( image.cols/2, image.rows/2 );
		double angle = 90.0;
		double scale = 1;
		
		Mat rot_mat = getRotationMatrix2D( center, angle, scale );

		int iterations{50};

		for(auto j = 0 ; j < iterations ; j++)
		{
			auto start = high_resolution_clock::now();
			warpAffine( image,result, rot_mat, image.size() );

			auto stop = high_resolution_clock::now();

			auto duration = duration_cast<microseconds>(stop - start);

			cout << duration.count() << endl;
		}
		
		image.release();
		result.release();
		i++;
	}
	return 0;
}

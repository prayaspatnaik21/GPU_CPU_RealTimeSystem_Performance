#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
using namespace std::chrono;

void GreyConversionOperationFunction();
void GaussianBlurOperationFunction();
void RotateImageOperationFunction(double rotationAngle);
void NormalOperationFunction();

int main(void) 
{
	// std::cout << "Choose the type of Operation\n"
    //         "Grey Conversion Operation 1\n"
    //         "Guassian Filter Operation 2\n"
    //         "Rotate Image Operation 3"<<std::endl;

    // int Operation{0};
    // std::cin >> Operation;

    bool GreyConversionOperation  = false, GaussianBlurOperation = false , RotateImageOperation = true ,NormalOperation = false;

    // switch(Operation)
    // {
    //     case 1:
    //         GreyConversionOperation = true;
    //         break;
    //     case 2:
    //         GaussianBlurOperation = true;
    //         break;
    //     case 3:
    //         RotateImageOperation = true; 
    //         break;
    //     default:
    //         NormalOperation = true;
	// 		break; 
    // }

	if(GreyConversionOperation)
	{
		GreyConversionOperationFunction();
	}
	else if (GaussianBlurOperation)
	{
		GaussianBlurOperationFunction();
	}
	else if(RotateImageOperation)
	{
		// cout << "Enter the angle by which you want to rotate the Image" << endl;
		// double rotationAngle{0};
		// cin >> rotationAngle;
		RotateImageOperationFunction(90.0f);
	}
	else
	{
		NormalOperationFunction();
	}
}

void GreyConversionOperationFunction()
{
	int i{0};

	string fixedPath = "../resources/Images/Sam_";
	string VariableFileName;

	while(i < 5)
	{
		Mat result;

		VariableFileName = std::to_string(i)+ ".jpg";
		string ResultPath = fixedPath + VariableFileName;
		Mat image = imread(ResultPath,1);

		cout << "Image Resolution" << " " << image.cols << "X" << image.rows << endl;

		int iterations{50};

		for(auto j = 0 ; j < iterations ; j++)
		{
			auto start = high_resolution_clock::now();
			image = imread(ResultPath,1);
			cv::cvtColor(image, result, cv::COLOR_BGR2GRAY);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << duration.count() << endl;
		}
	
		image.release();
		result.release();
		i++;
	}
}

void GaussianBlurOperationFunction()
{
	int i{0};

	string fixedPath = "../resources/Images/Sam_";
	string VariableFileName;

	while(i < 5)
	{
		Mat result;

		VariableFileName = std::to_string(i)+ ".jpg";
		string ResultPath = fixedPath + VariableFileName;
		Mat image = imread(ResultPath,1);

		cout << "Image Resolution" << " " << image.cols << "X" << image.rows << endl;

		int iterations{50};

		for(auto j = 0 ; j < iterations ; j++)
		{
			auto start = high_resolution_clock::now();
			Mat image = imread(ResultPath,1);
			GaussianBlur(image, result, Size(5, 5), 0);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << duration.count() << endl;
		}
	
		image.release();
		result.release();
		i++;
	}
}

void RotateImageOperationFunction(double rotationAngle)
{
	int i{0};

	string fixedPath = "../resources/Images/Sam_";
	string VariableFileName;

	while(i < 5)
	{
		Mat result;

		VariableFileName = std::to_string(i)+ ".jpg";
		string ResultPath = fixedPath + VariableFileName;
		Mat image = imread(ResultPath,1);

		cout << "Image Resolution" << " " << image.cols << "X" << image.rows << endl;

		Point center = Point( image.cols/2, image.rows/2 );
		double scale = 1;
	
		Mat rot_mat = getRotationMatrix2D( center, rotationAngle, scale );

		int iterations{50};

		for(auto j = 0 ; j < iterations ; j++)
		{
			auto start = high_resolution_clock::now();
			Mat image = imread(ResultPath,1);
			warpAffine( image,result, rot_mat, image.size() );
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << duration.count() << endl;
		}
	
		image.release();
		result.release();
		i++;
	}
}

void NormalOperationFunction()
{
	int i{0};

	string fixedPath = "../resources/Images/Sam_";
	string VariableFileName;

	while(i < 5)
	{
		VariableFileName = std::to_string(i)+ ".jpg";
		string ResultPath = fixedPath + VariableFileName;
		Mat image = imread(ResultPath,1);

		imshow("Image",image);
		waitKey(0);

		cout << "Image Resolution" << " " << image.cols << "X" << image.rows << endl;
	
		image.release();
		i++;
	}
}
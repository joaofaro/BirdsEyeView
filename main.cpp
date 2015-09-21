// Generic
#include <iostream>

// OpenCV modules (TODO: change this to include just the ones needed)
#include <opencv2/opencv.hpp>

// Classes
#include "birdseyeperspective.hpp"

using namespace std;

int main() {

	cout << "Hello World!" << endl;

	// Create object
	BirdsEyePerspective birsEye;

	// Read test image
	cv::Mat image;
    image = cv::imread("./HomographyTest.jpg", CV_LOAD_IMAGE_COLOR);

    // Set keypoints
   	birsEye.selectKeypoints(image);

	return 0;
}
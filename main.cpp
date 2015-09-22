// Generic
#include <iostream>

// OpenCV modules (TODO: change this to include just the ones needed)
#include <opencv2/opencv.hpp>

// Classes
#include "birdseyeperspective.hpp"

using namespace std;

int main() {

	// Create object
	BirdsEyePerspective birdsEye;

	// Read test image
	cv::Mat image;
    image = cv::imread("./HomographyTest.jpg", CV_LOAD_IMAGE_COLOR);

    // Set keypoints
   	birdsEye.selectKeypoints(image);

   	// Calculate vanishing points
   	birdsEye.obtainVanishingPoints();

	return 0;
}
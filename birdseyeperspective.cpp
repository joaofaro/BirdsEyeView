#include <iostream>
#include "birdseyeperspective.hpp"

using namespace cv;
using namespace std;

BirdsEyePerspective::BirdsEyePerspective(){
	// Empty temp vector
	vector<Point> tempVector;

	// X keypoints
	_keyPoints.push_back(tempVector);
	// Y keypoints
	_keyPoints.push_back(tempVector);
	// Z keypoints
	_keyPoints.push_back(tempVector);

	// Points needed per vanishing point
	_nKeyPoints = 4;

	// Number of vanishing points
	_nVanishingPoints = 3;

	// Current idx (defined to make the interface control easier)
	_idxVanishingPoints = 0;
}

void BirdsEyePerspective::selectKeypoints(Mat image){
	// Create window
	namedWindow("Point selection",1);   

	// Set the callback function
    setMouseCallback("Point selection", callBackFunc, (void*)&_keyPoints[_idxVanishingPoints]);
    
    // Draw points while the user select them
    while(_idxVanishingPoints < _nVanishingPoints){
	    while( _keyPoints[_idxVanishingPoints].size() < _nKeyPoints ){
	    	drawKeypoints(image);
	    }
	    // Increment idx and update callback function, pointing to the _keyPoints with the new _idxVanishingPoints
	    ++_idxVanishingPoints;
	    setMouseCallback("Point selection", callBackFunc, (void*)&_keyPoints[_idxVanishingPoints]);
	}
}

void BirdsEyePerspective::callBackFunc(int event, int x, int y, int flags, void* userdata){
    if( event == EVENT_LBUTTONDOWN ){
    	vector<Point>* vp = (vector<Point>*)userdata;
        Point temp;
        temp.x = x;
        temp.y = y;
        vp->push_back(temp);
    }
}

void BirdsEyePerspective::drawKeypoints(Mat image){
	for (int i = 0; i <= _idxVanishingPoints; ++i){
		for (int j = 1; j < _keyPoints[i].size(); j+=2){
			line(image, _keyPoints[i][j-1], _keyPoints[i][j], Scalar(0, 255/(i+1), 255), 2 );
		}
	}
	imshow("Point selection", image);
	waitKey(1);
}

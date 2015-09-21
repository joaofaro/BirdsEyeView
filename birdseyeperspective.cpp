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

	// Name of the window used in keypoints selection
	_pointSelectionWindow = "Point selection";
}

void BirdsEyePerspective::selectKeypoints(Mat image){
	// Create window
	namedWindow(_pointSelectionWindow,1);   

	// Set the callback function
    setMouseCallback(_pointSelectionWindow, callBackFunc, (void*)&_keyPoints[_idxVanishingPoints]);
    
    // Draw points while the user select them
    while(_idxVanishingPoints < _nVanishingPoints){
	    while( _keyPoints[_idxVanishingPoints].size() < _nKeyPoints ){
	    	drawKeypoints(image);
	    }
	    // Increment idx and update callback function, pointing to the _keyPoints vector with the new _idxVanishingPoints
	    ++_idxVanishingPoints;
	    setMouseCallback(_pointSelectionWindow, callBackFunc, (void*)&_keyPoints[_idxVanishingPoints]);
	}
}

void BirdsEyePerspective::callBackFunc(int event, int x, int y, int flags, void* userdata){
    if( event == EVENT_LBUTTONDOWN ){
    	vector<Point>* vp = (vector<Point>*) userdata;
        Point temp;
        temp.x = x;
        temp.y = y;
        vp->push_back(temp);
    }
}

void BirdsEyePerspective::drawKeypoints(Mat image){
	// Draw lines between each pair of points
	for (uint i = 0; i <= _idxVanishingPoints; ++i){
		for (uint j = 1; j < _keyPoints[i].size(); j+=2){
			line(image, _keyPoints[i][j-1], _keyPoints[i][j], Scalar(0, 255/(i+1), 255), 2 );
		}
	}
	// Show image with line segments
	imshow(_pointSelectionWindow, image);
	waitKey(1);
}

void BirdsEyePerspective::obtainVanishingPoints(){
	// Check if points are defined
	if (_keyPoints[_nVanishingPoints-1].size() < _nKeyPoints){
		cerr << "Keypoints should be defined first." << endl;
	}

	// Obtain line equations (y = mx+b) and calculate the corresponde intersection points
	for (uint group = 0; group < _keyPoints.size(); ++group){
		for (uint point = 1; point < _keyPoints[group].size(); point+=2){
			getLineEquation(_keyPoints[group][point-1], _keyPoints[group][point], slope, b);
		}
		//getIntersectionPoint();
	}
}




#include <iostream>
#include "birdseyeperspective.hpp"

using namespace cv;
using namespace std;

BirdsEyePerspective::BirdsEyePerspective(){
	// Empty temp vector
	vector<Point2d> tempVector;

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
	// Save local copy of image
	image.copyTo(_image);

	// Create window
	namedWindow(_pointSelectionWindow,1);   

	// Set the callback function
    setMouseCallback(_pointSelectionWindow, callBackFunc, (void*)&_keyPoints[_idxVanishingPoints]);
    
    // Draw points while the user select them
    while(_idxVanishingPoints < _nVanishingPoints){
	    while( _keyPoints[_idxVanishingPoints].size() < _nKeyPoints ){
	    	drawKeypoints(1);
	    }
	    // Increment idx and update callback function, pointing to the _keyPoints vector with the new _idxVanishingPoints
	    ++_idxVanishingPoints;
	    setMouseCallback(_pointSelectionWindow, callBackFunc, (void*)&_keyPoints[_idxVanishingPoints]);
	}
}

void BirdsEyePerspective::callBackFunc(int event, int x, int y, int flags, void* userdata){
    if( event == EVENT_LBUTTONDOWN ){
    	vector<Point2d>* vp = (vector<Point2d>*) userdata;
        Point2d temp;
        temp.x = x;
        temp.y = y;
        vp->push_back(temp);
    }
}

void BirdsEyePerspective::drawKeypoints(int waitKeyTime){
	// Draw lines between each pair of points
	for (uint i = 0; i <= _idxVanishingPoints; ++i){
		for (uint j = 1; j < _keyPoints[i].size(); j+=2){
			if (_vanishingPoints.size() > i){
				// Draw vanishing point if exists
				line(_image, _keyPoints[i][j-1], _vanishingPoints[i].location, Scalar(0, 255, 0), 1 );
			} else {	
				// Draw the line segment
				line(_image, _keyPoints[i][j-1], _keyPoints[i][j], Scalar(0, 255/(i+1), 255), 2 );
			}
		}
	}
	// Show image with line segments
	imshow(_pointSelectionWindow, _image);
	waitKey(waitKeyTime);
}

void BirdsEyePerspective::obtainVanishingPoints(){
	// Check if points are defined
	if (_keyPoints[_nVanishingPoints-1].size() < _nKeyPoints){
		cerr << "Keypoints should be defined first." << endl;
	}

	// Obtain line equations (y = mx+b) and calculate the corresponde intersection points
	for (uint group = 0; group < _keyPoints.size(); ++group){
		vanishingPointStruct tempVanishingPoint;
		for (uint point = 1; point < _keyPoints[group].size(); point+=2){
			// Get line equation for a pair of points
			getLineEquation(_keyPoints[group][point-1], _keyPoints[group][point], tempVanishingPoint.slope[point/2], tempVanishingPoint.b[point/2]);
		}
		// Calculate tempvanishingPoint location (updating the struct) and add it to the vector
		getIntersectionPoint(tempVanishingPoint.slope[0], tempVanishingPoint.b[0], tempVanishingPoint.slope[1], tempVanishingPoint.b[1], tempVanishingPoint.location);
		_vanishingPoints.push_back(tempVanishingPoint);		
	}
	// Draw vanishing points
	drawKeypoints(0);
}

void BirdsEyePerspective::getLineEquation(Point2d p1, Point2d p2, double &slope, double &b){
	if (p2.x == p1.x){
		p2.x += 0.1;
	}
	// Calc slope
	slope = (p2.y - p1.y) / (p2.x - p1.x);
	// Calc b using point 1
	b = p1.y - (slope*p1.x);
}

void BirdsEyePerspective::getIntersectionPoint(double m1, double b1, double m2, double b2, Point2d &location){
	// Find x
	location.x = (b2-b1) / (m1-m2);
	// Find y
	location.y = m1 * location.x + b1;
}

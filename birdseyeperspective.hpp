#ifndef PROJECTION_H
#define PROJECTION_H

#include <opencv2/opencv.hpp> // TODO do not include all modules, it is stupid

class BirdsEyePerspective {
	public:
		BirdsEyePerspective();

		virtual BirdsEyePerspective* clone(){ return new BirdsEyePerspective(*this);};

		virtual ~BirdsEyePerspective(){};

		virtual void selectKeypoints(cv::Mat image);

		//virtual std::vector<cv::Point> getVanishingPoints(){ return ; }; // TODO: Implement, returning only a vector with locations

		virtual cv::Mat getBirdsEyePerspective(){ return _outputImage; };

		virtual void obtainVanishingPoints();

	private:
		struct vanishingPointStruct {
			cv::Point2d location;
			double slope[2];
			double b[2];
		};

		std::vector<std::vector<cv::Point2d> > _keyPoints;
		std::vector<vanishingPointStruct> _vanishingPoints;
		cv::Mat _outputImage;
		uint _nKeyPoints;
		uint _nVanishingPoints;
		uint _idxVanishingPoints;
		std::string _pointSelectionWindow;
		std::string _resultWindow;
		cv::Mat _image;

		// Get line equation for a pair of points
		void getLineEquation(cv::Point2d p1, cv::Point2d p2, double &slope, double &b);

		// Get intersection point between two lines
		void getIntersectionPoint(double m1, double b1, double m2, double b2, cv::Point2d &location);

		// Mouse callback function
		static void callBackFunc(int event, int x, int y, int flags, void* userdata);

		// Draw keypoints in the image 
		void drawKeypoints(int waitKeyTime);
};

#endif
#ifndef PROJECTION_H
#define PROJECTION_H

#include <opencv2/opencv.hpp> // TODO do not include all modules, it is stupid

class BirdsEyePerspective {
	public:
		BirdsEyePerspective();

		virtual BirdsEyePerspective* clone(){ return new BirdsEyePerspective(*this);};

		virtual ~BirdsEyePerspective(){};

		virtual void selectKeypoints(cv::Mat image);

		virtual std::vector<cv::Point> getVanishingPoints(){ return _vanishingPoints; };

		virtual cv::Mat getBirdsEyePerspective(){ return _outputImage; };

	private:
		std::vector<std::vector<cv::Point> > _keyPoints;
		std::vector<cv::Point> _vanishingPoints;
		cv::Mat _outputImage;
		uint _nKeyPoints;
		uint _nVanishingPoints;
		uint _idxVanishingPoints;

		// Mouse callback function
		static void callBackFunc(int event, int x, int y, int flags, void* userdata);

		// Draw keypoints in the image 
		void drawKeypoints(cv::Mat image);
};

#endif
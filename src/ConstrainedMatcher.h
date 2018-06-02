/*
 * ConstrainedMatcher.h
 *
 *  Created on: 2 jan. 2016
 *      Author: christian
 */

#ifndef CONSTRAINEDMATCHER_H_
#define CONSTRAINEDMATCHER_H_

#include <vector>
#include <utility>
#include "Circle.h"
#include "opencv_includes.h"

class ConstrainedMatcher {
public:
	ConstrainedMatcher();
	virtual ~ConstrainedMatcher();

	// Set the feature detector
	inline void setFeatureDetector(cv::Ptr<cv::FeatureDetector>& detect) { detector= detect; }
	// Set the descriptor extractor
	inline void setDescriptorExtractor(cv::Ptr<cv::DescriptorExtractor>& desc) { extractor= desc; }
	// Set the matcher
	inline void setDescriptorMatcher(cv::Ptr<cv::DescriptorMatcher>& match) { matcher= match; }
	// Set confidence level
	inline void setConfidenceLevel(double conf) { confidence= conf; }
	// Set MinDistanceToEpipolar
	inline void setMinDistanceToEpipolar(double dist) { distance= dist; }
	// Set the list of corresponding constraints (circles)
	inline void setConstraints(std::vector< std::pair<Circle, Circle> >* constraints)
	{
		_constraints = constraints;
	}

	// Insert symmetrical matches in symMatches vector
	void symmetryTest(const std::vector<cv::DMatch>& matches1, const std::vector<cv::DMatch>& matches2, std::vector<cv::DMatch>& symMatches);
	// Identify good matches using RANSAC, return fundemental matrix
	cv::Mat ransacTest(const std::vector<cv::DMatch>& matches, const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2, std::vector<cv::DMatch>& outMatches);
	// Match feature points using symmetry test and RANSAC, returns fundemental matrix
	cv::Mat match(cv::Mat& image1, cv::Mat& image2, std::vector<cv::DMatch>& matches, std::vector<cv::KeyPoint>& keypoints1, std::vector<cv::KeyPoint>& keypoints2);


protected:
	// pointer to the feature point detector object
	cv::Ptr<cv::FeatureDetector> detector;
	// pointer to the feature descriptor extractor object
	cv::Ptr<cv::DescriptorExtractor> extractor;
	// pointer to the matcher object
	cv::Ptr<cv::DescriptorMatcher > matcher;
	float ratio; // max ratio between 1st and 2nd NN
	bool refineF; // if true will refine the F matrix
	double confidence; // confidence level (probability)
	double distance; // min distance to epipolar
	uint syn_total_points, real_total_points;

	std::vector< std::pair<Circle, Circle> >* _constraints;
};

#endif /* CONSTRAINEDMATCHER_H_ */

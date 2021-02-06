/*
 * Matrices.h
 *
 *  Created on: 8 de set de 2019
 *      Author: ensismoebius
 */

#ifndef SRC_MATRICES_CPP_
#define SRC_MATRICES_CPP_

#include <opencv2/opencv.hpp>

class Matrices
{
	public:

		inline static cv::Mat originalImage;
		inline static cv::Mat processedImage;
		inline static cv::Mat spectrumImage;
		inline static cv::Mat maskImage;
		inline static cv::Mat complex;

		inline static void init(const char *imagePath = 0)
		{

			// load original image
			cv::imread(imagePath, cv::COLOR_BGR2RGB).copyTo(originalImage);
			originalImage.convertTo(originalImage, CV_32F);

			// create processed image
			originalImage.copyTo(processedImage);

			// create spectrum image
			spectrumImage = cv::Mat(originalImage.rows, originalImage.cols, CV_32F);

			// create mask image
			maskImage = cv::Mat(originalImage.rows, originalImage.cols, CV_32F);

			// create complex image
			complex = cv::Mat(originalImage.rows, originalImage.cols, CV_32F);
		}
};

#endif /* SRC_MATRICES_CPP_ */

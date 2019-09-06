/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 5 de set de 2019
 *
 */
#ifndef SRC_LIB_NOISE_H_
#define SRC_LIB_NOISE_H_

#include <opencv2/opencv.hpp>

/**
 * Return a matrix with salt and pepper noise
 * @param image - Source
 * @param noiseProbability - Probability of noise
 * @return The matrix with noise
 */
cv::Mat addSaltAndPepperNoise(cv::Mat image, const double noiseProbability);

/**
 * Return a matrix with Gaussian noise
 * @param image - Source
 * @param sigma - The standard deviation (the more, more noise)
 * @return The matrix with noise
 */
cv::Mat addGaussianNoise(cv::Mat image, const unsigned char sigma);

#endif /* SRC_LIB_NOISE_H_ */

/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 5 de set de 2019
 *
 */
#include <opencv2/opencv.hpp>

/**
 * Return a matrix with salt and pepper noise
 * @param image - Source
 * @param noiseProbability - Probability of noise
 * @return The matrix with noise
 */
cv::Mat addSaltAndPepperNoise(cv::Mat image, const double noiseProbability, int imgFormat) {
	int imageChannels = image.channels();

	cv::Mat result = image.clone();
	result.convertTo(result, CV_8U);

	cv::RNG random(cv::RNG::NORMAL);

	long noisePoints = noiseProbability * image.rows * image.cols * imageChannels;

	for (long i = 0; i < noisePoints; i++) {

		int row = random.operator()(image.rows);
		int column = random.operator()(image.cols);
		int channel = random.operator()(imageChannels);

		unsigned char *pixelValuePtr = result.ptr(row) + (column * imageChannels) + channel;

		*pixelValuePtr = random.operator ()(2) > 0 ? 255 : 0;
	}

	result.convertTo(result, imgFormat);
	return result;
}

/**
 * Return a matrix with Gaussian noise
 * @param image - Source
 * @param sigma - The standard deviation (the more, more noise)
 * @return The matrix with noise
 */
cv::Mat addGaussianNoise(cv::Mat image, const unsigned char sigma, int imgFormat) {

	cv::Mat result = image.clone();
	result.convertTo(result, CV_8U);

	cv::RNG generator(cv::RNG::UNIFORM);

	int imageChannels = image.channels();

	for (int row = 0; row < result.rows; row++) {
		for (int column = 0; column < result.cols; column++) {
			for (int channel = 0; channel < imageChannels; channel++) {
				unsigned char *pixelValuePtr = result.ptr(row) + (column * imageChannels) + channel;

				long newPixelValue = *pixelValuePtr + generator.gaussian(sigma);

				*pixelValuePtr = newPixelValue > 255 ? 255 : newPixelValue < 0 ? 0 : newPixelValue;
			}
		}
	}

	result.convertTo(result, imgFormat);
	return result;
}

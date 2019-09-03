/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 1 de set de 2019
 *
 */

#include <array>
#include <cmath>
#include <vector>
#include <iostream>

#include <opencv2/opencv.hpp>

/**
 * Calculate the Inverse Discrete Fourier Transform
 * @param input A vector of sorted pairs, the 1st component is real, the 2nd component is complex
 * @param output The input vector
 */
void idft(std::vector<std::array<double, 2>> input, std::vector<double>& output) {
	/**
	 * The index of the current value being transformed
	 */
	int k = 0;

	/**
	 * The size of the signal
	 */
	int N = input.size();

	/**
	 * The current value being transformed
	 */
	std::array<double, 2> xn;

	/**
	 * Sum of the real parts
	 */
	double sumReal = 0;

	/**
	 * Sum of the complex parts
	 */
	double sumComplex = 0;

	// For each value of the signal calculate the sums
	while (k < N) {

		// Calculate the sums
		for (unsigned int n = 0; n < input.size(); ++n) {
			xn = input.at(n);

			sumReal += xn[0] * std::cos((2 * M_PI * k * n) / N);
			sumComplex += xn[1] * std::sin((2 * M_PI * k * n) / N);
		}

		// store the real and complex summed results
		output.push_back(sumReal + sumComplex);

		// reset the sums
		sumReal = 0;
		sumComplex = 0;

		// goto the next value
		k++;
	}
}
/**
 * Calculate the Discrete Fourier Transform
 * @param input The input vector
 * @param output A vector of sorted pairs, the 1st component is real, the 2nd component is complex
 */
void dft(std::vector<double> input, std::vector<std::array<double, 2>>& output) {

	/**
	 * The index of the current value being transformed
	 */
	int k = 0;

	/**
	 * The size of the signal
	 */
	int N = input.size();

	/**
	 * The current value being transformed
	 */
	double xn = 0;

	/**
	 * Sum of the real parts
	 */
	double sumReal = 0;

	/**
	 * Sum of the complex parts
	 */
	double sumComplex = 0;

	// For each value of the signal calculate the sums
	while (k < N) {

		// Calculate the sums
		for (unsigned int n = 0; n < input.size(); ++n) {
			xn = input.at(n);

			sumReal += xn * std::cos((2 * M_PI * k * n) / N);
			sumComplex += xn * std::sin((2 * M_PI * k * n) / N);
		}

		// store the results divide by the amount
		// values in the signal
		std::array<double, 2> r;
		output.push_back(r);
		output.at(k)[0] = sumReal / N;
		output.at(k)[1] = sumComplex / N;

		// reset the sums
		sumReal = 0;
		sumComplex = 0;

		// goto the next value
		k++;
	}
}

//void dft2(cv::Mat input, std::vector<std::vector<std::array<double, 2>>>& output) {
//
//	/**
//	 * Number of lines
//	 */
//	unsigned int M = 0;
//
//	/**
//	 * Number of items at each line
//	 */
//	unsigned int N = 0;
//
//	/**
//	 * The index of the current line being transformed
//	 */
//	unsigned int k = 0;
//
//	/**
//	 * The index of the current value in the line being transformed
//	 */
//	unsigned int j = 0;
//
//	/**
//	 * The index of the current line being transformed
//	 */
//	unsigned int u = 0;
//
//	/**
//	 * The index of the current value in the line being transformed
//	 */
//	unsigned int v = 0;
//
//	/**
//	 * The current value being transformed
//	 */
//	double xmn = 0;
//
//	/**
//	 * Sum of the real parts
//	 */
//	double sumReal = 0;
//
//	/**
//	 * Sum of the complex parts
//	 */
//	double sumComplex = 0;
//
//	while (u < M) {
//		while (v < N) {
//
//			//	for (int row = 0; row < image.rows; row++) {
//			//		for (int col = 0; col < image.cols; col++) {
//			//			//cv::Vec3b intensity = image.at<cv::Vec3b>(col, row);
//			//			image.at<cv::Vec3b>(row, col) = color;
//			//		}
//			//	}
//
//			for (unsigned int x = 0; x < M; ++x) {
//				for (unsigned int y = 0; y < N; ++y) {
//
//					cv::Vec3b intensity = input.at<cv::Vec3b>(y, x);
////
////
////
////
////					sumReal += xmn * std::cos(2 * M_PI *         (k * m)                   );
////					sumComplex += xmn * std::sin((2 * M_PI * k * n) / N);
//				}
//			}
//
//			// goto the next value
//			v++;
//		}
//		// goto the next line
//		u++;
//	}
//
//}

/**
 * Shows the results of a DFT
 * @param results The results to be read
 */
void showDftResults(const std::vector<std::array<double, 2>> results) {
	// output the result
	for (unsigned int n = 0; n < results.size(); ++n) {
		std::cout << "X" << n << ":\t" << results.at(n)[0] << " " << results.at(n)[1] << std::endl;
	}
}

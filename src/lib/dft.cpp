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

//#include <opencv2/opencv.hpp>

//void genDiscreteFourierTransformSpectrum(cv::Mat src, cv::Mat dst) {
//
//}

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

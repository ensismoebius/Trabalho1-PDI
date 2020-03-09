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
 * Calculates the magnitude for each sorted pairs resulted
 * from an Discrete Fourier Transformation
 * @param input A vector of sorted pairs, the 1st component is real, the 2nd component is complex
 * @param output The real vector result
 */
void calculateMagnitude(std::vector<std::array<double, 2>> input, std::vector<double> &output) {
	for (unsigned int n = 0; n < input.size(); ++n) {
		output.push_back(sqrt(pow(input.at(n)[0], 2) + pow(input.at(n)[1], 2)));
	}
}

/**
 * Calculates the fase for each sorted pairs resulted
 * from an Discrete Fourier Transformation
 * @param input A vector of sorted pairs, the 1st component is real, the 2nd component is complex
 * @param output The real vector result
 */
void calculateFase(std::vector<std::array<double, 2>> input, std::vector<double> &output) {
	for (unsigned int n = 0; n < input.size(); ++n) {
		output.push_back(atan(input.at(n)[1] / input.at(n)[0]));
	}
}

/**
 * Calculate the Inverse Discrete Fourier Transform
 * @param input A vector of sorted pairs, the 1st component is real, the 2nd component is complex
 * @param output The real vector result
 */
void idft(std::vector<std::array<double, 2>> input, std::vector<double> &output) {
	/**
	 * The index of the current value being untransformed
	 */
	int k = 0;

	/**
	 * The size of the signal
	 */
	int N = input.size();

	/**
	 * The current value being untransformed
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
void dft(std::vector<double> input, std::vector<std::array<double, 2>> &output) {

	/**
	 * The index of the current value being transformed
	 */
	unsigned int k = 0;

	/**
	 * The size of the signal
	 */
	unsigned int N = input.size();

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
		for (unsigned int n = 0; n < N; ++n) {
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
 * Calculate the 2D Discrete Fourier Transform
 * @param input The input
 * @param result The output
 */
void dft2(cv::Mat input, cv::Mat &result) {

	/**
	 * Sum of the real parts
	 */
	double sumReal = 0;

	/**
	 * Sum of the complex parts
	 */
	double sumComplex = 0;

	//////////level-1////////////////
	/**
	 * The index of the current line being transformed
	 */
	int unsigned u = 0;

	/**
	 * The amount of rows
	 */
	int unsigned M = input.rows;

	//////////level-2//////////////////
	/**
	 * The index of the current value being transformed
	 */
	int unsigned v = 0;

	/**
	 * The amount of items per cell
	 */
	int unsigned N = input.cols;

	while (u < M) {
		while (v < N) {

			// Calculate the sums
			for (unsigned int y = 0; y < M; ++y) {
				for (unsigned int x = 0; x < N; ++x) {

					double f = (double) input.at<uchar>(y, x);

					sumReal += f * std::cos(-2 * M_PI * (u * x / M + v * y / N));
					sumComplex += f * std::sin(-2 * M_PI * (u * x / M + v * y / N));
				}
			}

			result.at<cv::Vec2b>(v, u)[0] = sumReal / (M * N);
			result.at<cv::Vec2b>(v, u)[1] = sumComplex / (M * N);

			// reset the sums
			sumReal = 0;
			sumComplex = 0;

			// goto the next value
			v++;
		}

		// goto the next line
		u++;
	}

}

/**
 * Shows the values of a real vector
 * @param results The results to be read
 */
void showRealVector(const std::vector<double> results) {
// output the result
	for (unsigned int n = 0; n < results.size(); ++n) {
		std::cout << "X" << n << ":\t" << results.at(n) << std::endl;
	}
}

/**
 * Shows the results of a DFT
 * @param results The results to be read
 */
void showComplexVector(const std::vector<std::array<double, 2>> results) {
// output the result
	for (unsigned int n = 0; n < results.size(); ++n) {
		std::cout << "X" << n << ":\t" << results.at(n)[0] << " " << results.at(n)[1] << std::endl;
	}
}

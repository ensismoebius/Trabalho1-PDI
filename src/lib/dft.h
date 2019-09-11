/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 1 de set de 2019
 */

#ifndef SRC_LIB_DFT_H_
#define SRC_LIB_DFT_H_

#include <array>
#include <cmath>
#include <vector>
#include <iostream>

/**
 * Calculates the magnitude of each sorted pairs resulted
 * from an Discrete Fourier Transformation
 * @param input A vector of sorted pairs, the 1st component is real, the 2nd component is complex
 * @param output The real vector result
 */
void calculateMagnitude(std::vector<std::array<double, 2>> input, std::vector<double>& output);

/**
 * Calculates the fase for each sorted pairs resulted
 * from an Discrete Fourier Transformation
 * @param input A vector of sorted pairs, the 1st component is real, the 2nd component is complex
 * @param output The real vector result
 */
void calculateFase(std::vector<std::array<double, 2>> input, std::vector<double>& output);

/**
 * Calculate the Inverse Discrete Fourier Transform
 * @param input A vector of sorted pairs, the 1st component is real, the 2nd component is complex
 * @param output The input vector
 */
void idft(std::vector<std::array<double, 2>> input, std::vector<double>& output);

/**
 * Calculate the Discrete Fourier Transform
 * @param input The input vector
 * @param output A vector of sorted pairs, the 1st component is real, the 2nd component is complex
 */
void dft(std::vector<double> input, std::vector<std::array<double, 2>>& output);

/**
 * Calculate the 2D Discrete Fourier Transform
 * @param input The input
 * @param result The output
 */
void dft2(cv::Mat input, cv::Mat& result);

/**
 * Shows the values of a real vector
 * @param results The results to be read
 */
void showRealVector(const std::vector<double> results);

/**
 * Shows the results of a DFT
 * @param results The results to be read
 */
void showComplexVector(const std::vector<std::array<double, 2> > results);

#endif /* SRC_LIB_DFT_H_ */

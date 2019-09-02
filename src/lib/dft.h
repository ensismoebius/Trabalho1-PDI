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
 * Calculate the Discrete Fourier Transform
 * @param input The input vector
 * @param output A vector of sorted pairs, the 1st component is real, the 2nd component is complex
 */
void dft(std::vector<double> input, std::vector<std::array<double, 2>>& output);

/**
 * Shows the results of a DFT
 * @param results The results to be read
 */
void showDftResults(const std::vector<std::array<double, 2> > results);

#endif /* SRC_LIB_DFT_H_ */

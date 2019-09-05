/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * Based on the article from
 * @link https://vgg.fiit.stuba.sk/2012-05/frequency-domain-filtration/
 * @author Ing. Patrik Polatsek
 *
 * 5 de set de 2019
 *
 */

#ifndef SRC_LIB_DFT2_H_
#define SRC_LIB_DFT2_H_

#include <opencv2/opencv.hpp>

/**
 * Divide the matrix in four quadrants and swap the diagonals
 * @param matrix
 * @return the shifted matrix
 */
cv::Mat shiftMatrice(cv::Mat sourceMatrix);

/**
 * Apply the 2D Discrete Fourier Transform (DFT2)
 * and return a resulting complex matrix
 * @param sourceMatrix
 * @return complex matrix
 */
cv::Mat dft2(cv::Mat sourceMatrix);

/**
 * Generates the matrix witch can be used for
 * visualization of the Fourier Spectrum
 * @param complex - The complex matrix resulted from DFT2
 * @return
 */
cv::Mat genSpectrumImage(cv::Mat complex);

/**
 * Transforms the DFT2 complex matrix back to real one
 * @param complex
 * @return real matrix
 */
cv::Mat idft2(cv::Mat complex);

/**
 * Create a highpass or lowpass filter
 * @param reference - the matrix from witch will be copied the width and height
 * @param radius - The radius of the filter
 * @param highpass - true = highpass, false = lowpass
 * @return the filter matrix
 */
cv::Mat createHighLowPassFilter(cv::Mat reference, int radius, bool highpass = true, float gaussiamSigma = 1);

/**
 * Combines a filter with the complex matrix
 * from DFT2 and returns this combination
 * @param complex - the complex matrix
 * @param mask - the mask matrix
 * @return combination
 */
cv::Mat combineDFTComplexAndMask(cv::Mat complex, cv::Mat mask);

#endif /* SRC_LIB_DFT2_H_ */

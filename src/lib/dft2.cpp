/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * Based on the article from
 * @link https://vgg.fiit.stuba.sk/2012-05/frequency-domain-filtration/
 *
 * 5 de set de 2019
 *
 */

#include <opencv2/opencv.hpp>

/**
 * Divide the matrix in four quadrants and swap the diagonals
 * @param matrix
 * @return the shifted matrix
 */
cv::Mat shiftMatrice(cv::Mat sourceMatrix) {

	// crop if it has an odd number of rows or columns
	cv::Mat result = sourceMatrix(cv::Rect(0, 0, sourceMatrix.cols & -2, sourceMatrix.rows & -2)).clone();

	int cx = sourceMatrix.cols / 2;
	int cy = sourceMatrix.rows / 2;

	cv::Mat topLeft(result, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	cv::Mat topRight(result, cv::Rect(cx, 0, cx, cy));  // Top-Right
	cv::Mat bottomLeft(result, cv::Rect(0, cy, cx, cy));  // Bottom-Left
	cv::Mat bottomRight(result, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

	cv::Mat tmp;                            // swap quadrants (Top-Left with Bottom-Right)
	topLeft.copyTo(tmp);
	bottomRight.copyTo(topLeft);
	tmp.copyTo(bottomRight);
	topRight.copyTo(tmp);                     // swap quadrants (Top-Right with Bottom-Left)
	bottomLeft.copyTo(topRight);
	tmp.copyTo(bottomLeft);

	return result;
}

/**
 * Apply the 2D Discrete Fourier Transform (DFT2)
 * and return a resulting complex matrix
 * @param sourceMatrix
 * @return complex matrix
 */
cv::Mat dft2(cv::Mat sourceMatrix) {
	cv::Mat padded;
	int m = cv::getOptimalDFTSize(sourceMatrix.rows);
	int n = cv::getOptimalDFTSize(sourceMatrix.cols);

	// create output sourceMatrix of optimal size
	cv::copyMakeBorder(sourceMatrix, padded, 0, m - sourceMatrix.rows, 0, n - sourceMatrix.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	// copy the source sourceMatrix, on the border add zero values
	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };

	// create a complex matrix
	cv::Mat complex;
	cv::merge(planes, 2, complex);
	cv::dft(complex, complex, cv::DFT_COMPLEX_OUTPUT);  // fourier transform
	return complex;
}

/**
 * Generates the matrix witch can be used for
 * visualization of the Fourier Spectrum
 * @param complex - The complex matrix resulted from DFT2
 * @return
 */
cv::Mat genSpectrumImage(cv::Mat complex) {

	cv::Mat magI;
	cv::Mat planes[] = { cv::Mat::zeros(complex.size(), CV_32F), cv::Mat::zeros(complex.size(), CV_32F) };
	cv::split(complex, planes);                // planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))

	cv::magnitude(planes[0], planes[1], magI);    // sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)

	// switch to logarithmic scale: log(1 + magnitude)
	magI += cv::Scalar::all(1);
	cv::log(magI, magI);

	magI = shiftMatrice(magI);
	cv::normalize(magI, magI, 1, 0, cv::NORM_INF); // Transform the matrix with float values into a
	// viewable image form (float between values 0 and 1).
	return magI;
}

/**
 * Transforms the DFT2 complex matrix back to real one
 * @param complex
 * @return real matrix
 */
cv::Mat idft2(cv::Mat complex) {
	cv::Mat work;
	cv::idft(complex, work);

	cv::Mat planes[] = { cv::Mat::zeros(complex.size(), CV_32F), cv::Mat::zeros(complex.size(), CV_32F) };
	cv::split(work, planes);                // planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))

	cv::magnitude(planes[0], planes[1], work);    // === sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)
	cv::normalize(work, work, 0, 1, cv::NORM_MINMAX);
	return work;
}

/**
 * Create a highpass or lowpass filter
 * @param reference - the matrix from witch will be copied the width and height
 * @param radius - The radius of the filter
 * @param highpass - true = highpass, false = lowpass
 * @return the filter matrix
 */
cv::Mat createHighLowPassFilter(cv::Mat reference, int radius, bool highpass = true) {

	uchar backgroundColor;
	uchar cicleColor;

	if (highpass) {
		backgroundColor = 255;
		cicleColor = 0;
	} else {
		backgroundColor = 0;
		cicleColor = 255;
	}

	cv::Mat mask(reference.rows, reference.cols, CV_32F);
	mask.setTo(cv::Scalar(backgroundColor));

	unsigned int centerX = reference.cols / 2;
	unsigned int centerY = reference.rows / 2;

	cv::circle(mask, cv::Point(centerX, centerY), radius, cv::Scalar(cicleColor), cv::FILLED);

	return mask;
}

/**
 * Combines a filter with the complex matrix
 * from DFT2 and returns this combination
 * @param complex - the complex matrix
 * @param mask - the mask matrix
 * @return combination
 */
cv::Mat combineDFTComplexAndMask(cv::Mat complex, cv::Mat mask) {

	cv::Mat shiftedMask = shiftMatrice(mask);

	cv::Mat planes[] = { cv::Mat::zeros(complex.size(), CV_32F), cv::Mat::zeros(complex.size(), CV_32F) };

	cv::Mat kernel_spec;
	planes[0] = shiftedMask; // real
	planes[1] = shiftedMask; // imaginary
	cv::merge(planes, 2, kernel_spec);

	cv::mulSpectrums(complex, kernel_spec, complex, cv::DFT_ROWS); // only DFT_ROWS accepted

	return complex;
}

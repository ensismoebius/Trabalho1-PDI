/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 5 de set de 2019
 *
 */
#include <string>
#include <iostream>
#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include "MainWindow.cpp"

void shiftMatrice(cv::Mat magI) {

	// crop if it has an odd number of rows or columns
	magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));  // Top-Right
	cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));  // Bottom-Left
	cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

	cv::Mat tmp;                            // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);                     // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

cv::Mat computeDFT(cv::Mat image) {
	cv::Mat padded;
	int m = cv::getOptimalDFTSize(image.rows);
	int n = cv::getOptimalDFTSize(image.cols);
	// create output image of optimal size
	cv::copyMakeBorder(image, padded, 0, m - image.rows, 0, n - image.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	// copy the source image, on the border add zero values
	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	// create a complex matrix
	cv::Mat complex;
	cv::merge(planes, 2, complex);
	cv::dft(complex, complex, cv::DFT_COMPLEX_OUTPUT);  // fourier transform
	return complex;
}

cv::Mat generateSpectrumImage(cv::Mat complex) {

	cv::Mat magI;
	cv::Mat planes[] = { cv::Mat::zeros(complex.size(), CV_32F), cv::Mat::zeros(complex.size(), CV_32F) };
	cv::split(complex, planes);                // planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))

	cv::magnitude(planes[0], planes[1], magI);    // sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)

	// switch to logarithmic scale: log(1 + magnitude)
	magI += cv::Scalar::all(1);
	cv::log(magI, magI);

	shiftMatrice(magI);
	cv::normalize(magI, magI, 1, 0, cv::NORM_INF); // Transform the matrix with float values into a
	// viewable image form (float between values 0 and 1).
	return magI;
}

cv::Mat computeIDFT(cv::Mat complex) {
	cv::Mat work;
	cv::idft(complex, work);
	//  dft(complex, work, DFT_INVERSE + DFT_SCALE);

	cv::Mat planes[] = { cv::Mat::zeros(complex.size(), CV_32F), cv::Mat::zeros(complex.size(), CV_32F) };
	cv::split(work, planes);                // planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))

	cv::magnitude(planes[0], planes[1], work);    // === sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)
	cv::normalize(work, work, 0, 1, cv::NORM_MINMAX);
	return work;
}

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

cv::Mat combineDFTComplexAndMask(cv::Mat complex, cv::Mat mask) {

	shiftMatrice(mask);

	cv::Mat planes[] = { cv::Mat::zeros(complex.size(), CV_32F), cv::Mat::zeros(complex.size(), CV_32F) };

	cv::Mat kernel_spec;
	planes[0] = mask; // real
	planes[1] = mask; // imaginary
	cv::merge(planes, 2, kernel_spec);

	cv::mulSpectrums(complex, kernel_spec, complex, cv::DFT_ROWS); // only DFT_ROWS accepted

	return complex;
}

int main(int argc, char **argv) {
	char* file = argv[3];

	cv::Mat original = cv::imread(file, CV_LOAD_IMAGE_GRAYSCALE);

	cv::Mat complex = computeDFT(original);
	cv::Mat spectrum = generateSpectrumImage(complex);
	cv::Mat result = computeIDFT(complex);
	cv::Mat filter = createHighLowPassFilter(original, 20, false);

	complex = combineDFTComplexAndMask(complex, filter);
	cv::Mat spectrum2 = generateSpectrumImage(complex);
	cv::Mat result2 = computeIDFT(complex);

	original.convertTo(original, CV_32F);
	spectrum.convertTo(spectrum, CV_32F);
	result.convertTo(result, CV_32F);

	filter.convertTo(filter, CV_32F);
	spectrum2.convertTo(spectrum2, CV_32F);
	result2.convertTo(result2, CV_32F);

	cv::normalize(original, original, 1, 0, cv::NORM_INF);
	cv::normalize(spectrum, spectrum, 1, 0, cv::NORM_INF);
	cv::normalize(result, result, 1, 0, cv::NORM_INF);

	cv::normalize(filter, filter, 1, 0, cv::NORM_INF);
	cv::normalize(spectrum2, spectrum2, 1, 0, cv::NORM_INF);
	cv::normalize(result2, result2, 1, 0, cv::NORM_INF);

	cv::hconcat(original, spectrum, original);
	cv::hconcat(original, result, original);

	cv::hconcat(filter, spectrum2, filter);
	cv::hconcat(filter, result2, filter);

	cv::vconcat(original, filter, original);

	cv::imshow("mix", original);

	cv::waitKey(0);

	Gtk::Main kit(argc, argv);

	MainWindow mwindow(argv[1]);

	Gtk::Main::run(mwindow);

}

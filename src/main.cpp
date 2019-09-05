#include <iostream>
#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include "lib/dft.h"
#include "MainWindow.cpp"

void shiftMatrice(const cv::Mat& magI) {
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;
	cv::Mat q0(magI, cv::Rect(0, 0, cx, cy)); // Top-Left
	cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy)); // Top-Right
	cv::Mat q2(magI, cv::Rect(0, cy, cx, cy)); // Bottom-Left
	cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // Bottom-Right
	cv::Mat tmp;
	// swap (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	// swap (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);
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

cv::Mat genDFTSpectrum(const char* filename, bool shifted = true, bool highpass = false, bool lowpass = false) {

	cv::Mat original = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);

	if (original.empty()) return original;

	// expand input image to optimal size,
	cv::Mat padded;
	int m = cv::getOptimalDFTSize(original.rows);
	int n = cv::getOptimalDFTSize(original.cols);

	// on the border add zero values
	cv::copyMakeBorder(original, padded, 0, m - original.rows, 0, n - original.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	// create a new channel for housing the complex numbers
	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	cv::Mat complexI;
	cv::merge(planes, 2, complexI);

	// perform the dft
	cv::dft(complexI, complexI); // this way the result may fit in the source matrix

	// split channels for reading
	cv::split(complexI, planes);

	// planes[0] = real values of DFT(original)
	// planes[1] = Imaginary values of DFT(original)
	cv::magnitude(planes[0], planes[1], planes[0]);

	// planes[0] = magnitude values of DFT(original)
	cv::Mat magI = planes[0];
	magI += cv::Scalar::all(1);

	// switch to logarithmic scale
	cv::log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// shift the quadrants of Fourier image so that the origin is at the image center
	if (shifted) {
		shiftMatrice(magI);

		if (highpass) {
			cv::multiply(magI, createHighLowPassFilter(magI, 20, true), magI);
		}
		if (lowpass) {
			cv::multiply(magI, createHighLowPassFilter(magI, 20, false), magI);
		}
	}

	// Normalize image to o bit format
	cv::normalize(magI, magI, 0, 255, CV_MINMAX);

	// Convert image type to 8 bit
	magI.convertTo(magI, CV_8U);
	original.convertTo(original, CV_8U);

	// Resize for better visualization
	cv::resize(magI, magI, cv::Size(500, 500));
	cv::resize(original, original, cv::Size(500, 500));

	cv::hconcat(magI, original, magI);
	return magI;
}

int main(int argc, char **argv) {

//	std::vector<double> original = { 1, 2, 0, 1 };
//	std::vector<std::array<double, 2>> transformed;
//	std::vector<double> resconstructed;
//	std::vector<double> magnitudes;
//	std::vector<double> fases;
//
//	dft(original, transformed);
//	showDftResults(transformed);
//	calculateMagnitude(transformed, magnitudes);
//	calculateFase(transformed, fases);
//	idft(transformed, resconstructed);

//	cv::Mat originalMat(2, 2, CV_8UC1, cv::Scalar(0));
//	originalMat.at<uchar>(0, 0) = 10;
//	originalMat.at<uchar>(0, 1) = 0;
//	originalMat.at<uchar>(1, 0) = 0;
//	originalMat.at<uchar>(1, 1) = 10;

	const char* filename1;
	const char* filename2;
	const char* filename3;
	const char* filename4;
	const char* filename5;

	filename1 = argv[1];
	filename2 = argv[2];
	filename3 = argv[3];
	filename4 = argv[4];
	filename5 = argv[5];

	cv::Mat magI;
	cv::Mat magII;
	cv::Mat magIII;
	cv::Mat magIV;
	cv::Mat magV;

	magI = genDFTSpectrum(filename1, true, false, true);
	magII = genDFTSpectrum(filename2, true, false, true);
	magIII = genDFTSpectrum(filename3, true, false, true);
	magIV = genDFTSpectrum(filename4, true, false, true);
	magV = genDFTSpectrum(filename5, true, false, true);

//	cv::imwrite("shiftedSpectrumI.png", magI);
//	cv::imwrite("shiftedSpectrumII.png", magII);
//	cv::imwrite("shiftedSpectrumIII.png", magIII);
//	cv::imwrite("shiftedSpectrumIV.png", magIV);
//	cv::imwrite("shiftedSpectrumV.png", magV);

	cv::imshow("spectrum magnitude", magI);
	cv::waitKey();
	cv::imshow("spectrum magnitude", magII);
	cv::waitKey();
	cv::imshow("spectrum magnitude", magIII);
	cv::waitKey();
	cv::imshow("spectrum magnitude", magIV);
	cv::waitKey();
	cv::imshow("spectrum magnitude", magV);
	cv::waitKey();

	magI = genDFTSpectrum(filename1, false);
	magII = genDFTSpectrum(filename2, false);
	magIII = genDFTSpectrum(filename3, false);
	magIV = genDFTSpectrum(filename4, false);
	magV = genDFTSpectrum(filename5, false);

//	cv::imwrite("spectrumI.png", magI);
//	cv::imwrite("spectrumII.png", magII);
//	cv::imwrite("spectrumIII.png", magIII);
//	cv::imwrite("spectrumIV.png", magIV);
//	cv::imwrite("spectrumV.png", magV);

	cv::imshow("spectrum magnitude", magI);
	cv::waitKey();
	cv::imshow("spectrum magnitude", magII);
	cv::waitKey();
	cv::imshow("spectrum magnitude", magIII);
	cv::waitKey();
	cv::imshow("spectrum magnitude", magIV);
	cv::waitKey();
	cv::imshow("spectrum magnitude", magV);
	cv::waitKey();

//	cv::Mat originalMat = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
//	cv::Mat outputMat(originalMat.rows, originalMat.cols, CV_32F, cv::Scalar(0));
//	dft2(originalMat, outputMat);
//
//	cv::imshow("1channel", outputMat);
//	cv::waitKey(0);

//	Gtk::Main kit(argc, argv);
//
//	MainWindow mwindow(argv[1]);
//
//	Gtk::Main::run(mwindow);

	return 0;
}


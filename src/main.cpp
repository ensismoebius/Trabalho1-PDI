#include <iostream>
#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include "lib/dft.h"
#include "MainWindow.cpp"

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

	const char* filename = argc >= 2 ? argv[1] : "lena.jpg";

	cv::Mat I = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
	if (I.empty()) return -1;

	cv::Mat padded;                            //expand input image to optimal size
	int m = cv::getOptimalDFTSize(I.rows);
	int n = cv::getOptimalDFTSize(I.cols); // on the border add zero values
	cv::copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	cv::Mat complexI;
	cv::merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

	dft2(complexI, complexI);            // this way the result may fit in the source matrix

	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	cv::split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	cv::magnitude(planes[0], planes[1], planes[0]);                   // planes[0] = magnitude
	cv::Mat magI = planes[0];

	magI += cv::Scalar::all(1);                    // switch to logarithmic scale
	cv::log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));  // Top-Right
	cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));  // Bottom-Left
	cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

	cv::Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	cv::normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
	// viewable image form (float between values 0 and 1).

	//cv::imshow("Input Image", I);    // Show the result
	cv::imshow("spectrum magnitude", magI);
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


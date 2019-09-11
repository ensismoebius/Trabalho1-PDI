/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 5 de set de 2019
 *
 */
#include <iostream>
#include <strstream>
#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include "lib/dft.h"
#include "lib/dft2.h"
#include "lib/noise.h"
#include "MainWindow.cpp"

void exercicio2(char* file) {

	// Reads the image
	cv::Mat original = cv::imread(file, CV_LOAD_IMAGE_GRAYSCALE);

	// compute the DFT results
	cv::Mat complex = dft2(original);
	cv::Mat spectrum = genSpectrumImage(complex);

	// compute the IDFT results
	cv::Mat result = idft2(complex);

	// compute the masked IDFT results
	cv::Mat filter = createHighLowPassFilter(original, 20, true, 4);

	complex = combineDFTComplexAndMask(complex, filter);
	cv::Mat spectrum2 = genSpectrumImage(complex);
	cv::Mat result2 = idft2(complex);

	// create one big image with everything
	spectrum2.convertTo(spectrum2, CV_32F);
	original.convertTo(original, CV_32F);
	spectrum.convertTo(spectrum, CV_32F);
	result2.convertTo(result2, CV_32F);
	result.convertTo(result, CV_32F);
	filter.convertTo(filter, CV_32F);

	// equalize the matrix types
	cv::normalize(spectrum2, spectrum2, 1, 0, cv::NORM_INF);
	cv::normalize(original, original, 1, 0, cv::NORM_INF);
	cv::normalize(spectrum, spectrum, 1, 0, cv::NORM_INF);
	cv::normalize(result2, result2, 1, 0, cv::NORM_INF);
	cv::normalize(result, result, 1, 0, cv::NORM_INF);
	cv::normalize(filter, filter, 1, 0, cv::NORM_INF);

	// creates the first row of the image
	cv::hconcat(original, spectrum, original);
	cv::hconcat(original, result, original);

	// creates the second row of the image
	cv::hconcat(filter, spectrum2, filter);
	cv::hconcat(filter, result2, filter);

	// concatenates the first and second rows
	cv::vconcat(original, filter, original);

	// shows the result
	cv::imshow("mix", original);

	// Converts image into an "saveble" format
	original.convertTo(original, CV_8UC3, 255);

	// Changes file name
	std::stringstream filename;
	filename << file << "_processed.png";

	// Saves image
	cv::imwrite(filename.str(), original);

	cv::waitKey(0);
}

void exercicio4(char* file) {
	// Reads the image
	cv::Mat original = cv::imread(file, CV_LOAD_IMAGE_GRAYSCALE);

	// compute the DFT results for original image
	cv::Mat complex = dft2(original);
	cv::Mat spectrum = genSpectrumImage(complex);

	// adds salt pepper and gaussian noises
	cv::Mat originalNoise(original.rows, original.cols, original.type());
	originalNoise = addSaltAndPepperNoise(original, 0.05);
	originalNoise = addGaussianNoise(originalNoise, 5);
	cv::imshow("uga", originalNoise);

	// Converts image into an "saveble" format
	originalNoise.convertTo(originalNoise, CV_8U);

	// Changes file name
	std::stringstream filename;
	filename << file << "_noise.png";

	// Saves image
	cv::imwrite(filename.str(), originalNoise);

	cv::waitKey(0);

//	// compute the DFT results for image with noises
//	cv::Mat complex3 = dft2(originalNoise);
//	cv::Mat spectrumNoise = genSpectrumImage(complex3);
//
//	cv::Mat finalMask = createBandStopPassFilter(complex3, complex3.cols / 16, complex3.cols / 2, true, 1);
//
//	cv::Mat complex2 = combineDFTComplexAndMask(complex3, finalMask);
//	cv::Mat res = idft2(complex2);
//
//	cv::imshow("finalMask", finalMask);
//	cv::imshow("result", res);
//
//	///////////////////////////////////
//	// convert images to join them all
//	spectrum.convertTo(spectrum, CV_32F);
//	original.convertTo(original, CV_32F);
//	spectrumNoise.convertTo(spectrumNoise, CV_32F);
//	originalNoise.convertTo(originalNoise, CV_32F);
//
//	// equalize all matrix
//	cv::normalize(spectrum, spectrum, 1, 0, cv::NORM_INF);
//	cv::normalize(original, original, 1, 0, cv::NORM_INF);
//	cv::normalize(spectrumNoise, spectrumNoise, 1, 0, cv::NORM_INF);
//	cv::normalize(originalNoise, originalNoise, 1, 0, cv::NORM_INF);
//
//	// creates the first row of the image
//	cv::hconcat(originalNoise, spectrumNoise, originalNoise);
//
//	// creates the second row of the image
//	cv::hconcat(original, spectrum, original);
//
//	// join rows!!
//	cv::vconcat(original, originalNoise, original);
//
//	// shows the result
//	cv::imshow("mix", original);
	cv::waitKey(0);
}

void exercio01() {
	std::vector<double> input = { 1, 2, 0, 1 };
	std::vector<double> reconstructed;
	std::vector<std::array<double, 2>> output;

	showRealVector(input);
	std::cout << "---------" << std::endl;

	dft(input, output);
	showComplexVector(output);

	std::cout << "---------" << std::endl;
	idft(output, reconstructed);
	showRealVector(reconstructed);
}

int main(int argc, char **argv) {

//	exercio01();
//
//	for (int argi = 1; argi < argc; argi++) {
//		exercicio2(argv[argi]);
//	}

//	for (int argi = 1; argi < argc; argi++) {
//		exercicio4(argv[argi]);
//	}

	Gtk::Main kit(argc, argv);

	MainWindow mwindow(argv[1]);

	Gtk::Main::run(mwindow);

}

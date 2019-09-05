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
#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include "lib/dft2.h"
#include "MainWindow.cpp"

void genResultsImage(char* file) {

	// Reads the image
	cv::Mat original = cv::imread(file, CV_LOAD_IMAGE_GRAYSCALE);

	// compute the DFT results
	cv::Mat complex = dft2(original);
	cv::Mat spectrum = genSpectrumImage(complex);

	// compute the IDFT results
	cv::Mat result = idft2(complex);

	// compute the masked IDFT results
	cv::Mat filter = createHighLowPassFilter(original, 20, false, 4);

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
	cv::waitKey(0);
}

int main(int argc, char **argv) {

	for (int argi = 1; argi < argc; argi++) {
		genResultsImage(argv[argi]);
	}

	Gtk::Main kit(argc, argv);

	MainWindow mwindow(argv[1]);

	Gtk::Main::run(mwindow);

}

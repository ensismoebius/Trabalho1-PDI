#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include <iostream>
#include "lib/dft.h"
#include "MainWindow.cpp"

int main(int argc, char **argv) {

	std::vector<double> original = { 200, 100, 255, 255, 255, 0, 0, 0 };
	std::vector<std::array<double, 2>> transformed;
	std::vector<double> resconstructed;
	std::vector<double> magnitudes;
	std::vector<double> fases;

	dft(original, transformed);
	showDftResults(transformed);
	calculateMagnitude(transformed, magnitudes);
	calculateFase(transformed, fases);

	idft(transformed, resconstructed);

	Gtk::Main kit(argc, argv);

	MainWindow mwindow(argv[1]);

	Gtk::Main::run(mwindow);

	return 0;
}


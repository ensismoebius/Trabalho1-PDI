#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include <iostream>
#include "lib/dft.h"
#include "MainWindow.cpp"

int main(int argc, char **argv) {

	std::vector<double> teste = { 1, 4, 5, 6, 8, 10, 253, 54, 89, 50, 1, 0, 56, 65, 52, 1, 2, 3, 9, 8, 7 };
	std::vector<std::array<double, 2>> output;
	dft(teste, output);
	showDftResults(output);

	Gtk::Main kit(argc, argv);

	MainWindow mwindow(argv[1]);

	Gtk::Main::run(mwindow);

	return 0;
}


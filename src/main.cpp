#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include <iostream>
#include "lib/dft.h"
#include "MainWindow.cpp"

int main(int argc, char **argv) {

	std::vector<double> teste = { 2, 3, 4, 4, 2, 3, 4, 4 };
	std::vector<double> teste2;

	std::vector<std::array<double, 2>> output;
	dft(teste, output);
	showDftResults(output);
	idft(output, teste2);

	Gtk::Main kit(argc, argv);

	MainWindow mwindow(argv[1]);

	Gtk::Main::run(mwindow);

	return 0;
}


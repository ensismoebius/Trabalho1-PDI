//#include <gtkmm-3.0/gtkmm.h>
//#include <opencv2/opencv.hpp>
//
//#include "MainWindow.cpp"

#include <vector>
#include <array>
#include <cmath>
#include <iostream>

void dft(std::vector<double> input) {

	std::vector<std::array<double, 2>> output;

	int k = 0;
	int N = input.size();
	double xn = 0;
	double sumReal = 0;
	double sumComplex = 0;

	while (k < N) {
		for (unsigned int n = 0; n < input.size(); ++n) {

			xn = input.at(n);

			sumReal += xn * std::cos((2 * M_PI * k * n) / N);
			sumComplex += xn * std::sin((2 * M_PI * k * n) / N);
		}

		std::array<double, 2> r;
		output.push_back(r);
		output.at(k)[0] = sumReal / N;
		output.at(k)[1] = sumComplex / N;

		sumReal = 0;
		sumComplex = 0;

		k++;
	}

	// output the result
	for (unsigned int n = 0; n < input.size(); ++n) {
		std::cout << "X" << n << ":\t" << output.at(n)[0] << " " << output.at(n)[1] << std::endl;
	}

}

int main(int argc, char **argv) {
//	Gtk::Main kit(argc, argv);
//
//	MainWindow mwindow(argv[1]);
//
//	Gtk::Main::run(mwindow);
	std::cout << std::fixed;
	std::vector<double> teste = { 1, 2, 0, 1 };
	//std::vector<double> teste = { 2, 3, 4, 4 };
	dft(teste);

	return 0;

}


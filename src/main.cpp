#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include <iostream>
#include "MainWindow.cpp"

int main(int argc, char **argv) {

	Gtk::Main kit(argc, argv);

	MainWindow mwindow(argv[1]);

	Gtk::Main::run(mwindow);

	return 0;
}


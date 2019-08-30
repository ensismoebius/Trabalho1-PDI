#ifndef SRC_MAINWINDOW_CPP_
#define SRC_MAINWINDOW_CPP_

#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include "ImageCanvas.cpp"

class MainWindow: public Gtk::Window {
	protected:
		cv::Mat* image;
		Gtk::Frame videoFrame;
		ImageCanvas* imageArea;

		void createImageCanvas(char* imagePath = 0) {
			if (imagePath == 0) {
				image = new cv::Mat();
				imageArea = new ImageCanvas(*image, ImageCanvas::TYPE_VIDEO);
				imageArea->set_tooltip_text("Video");
				return;
			}

			image = new cv::Mat();
			*image = cv::imread(imagePath, 1);
			imageArea = new ImageCanvas(*image, ImageCanvas::TYPE_IMAGE);
			imageArea->set_tooltip_text("Image");
		}

	public:
		MainWindow(char* imagePath) {
			set_title("OpenCV with GTK and Video");
			set_border_width(10);

			this->createImageCanvas(imagePath);

			videoFrame.set_label("OpenCV and GTK with image");
			videoFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			videoFrame.set_shadow_type(Gtk::SHADOW_OUT);
			videoFrame.set_size_request(320, 240);
			videoFrame.add(*imageArea);

			add(videoFrame);

			show_all();
		}

		MainWindow() {
			set_title("OpenCV with GTK with Video");
			set_border_width(10);

			this->createImageCanvas();

			videoFrame.set_label("OpenCV and GTK");
			videoFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			videoFrame.set_shadow_type(Gtk::SHADOW_OUT);
			videoFrame.set_size_request(320, 240);
			videoFrame.add(*imageArea);

			add(videoFrame);

			show_all();
		}

		~MainWindow() {
			delete image;
			delete imageArea;
		}
};
#endif /* SRC_MAINWINDOW_CPP_ */

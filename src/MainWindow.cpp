#ifndef SRC_MAINWINDOW_CPP_
#define SRC_MAINWINDOW_CPP_

#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include "ImageCanvas.cpp"

class MainWindow: public Gtk::Window {
	protected:
		cv::Mat* image;
		Gtk::Frame originalFrame;
		ImageCanvas* imageArea;

		cv::Mat* processedImage;
		Gtk::Frame processedFrame;
		ImageCanvas* processedImageArea;

		Gtk::Box box;

		void createOriginalImageCanvas(char* imagePath = 0) {
			image = new cv::Mat();

			if (imagePath == 0) {
				imageArea = new ImageCanvas(*image, ImageCanvas::TYPE_VIDEO);
				imageArea->set_tooltip_text("Video");
				return;
			}

			*image = cv::imread(imagePath, 1);
			imageArea = new ImageCanvas(*image, ImageCanvas::TYPE_IMAGE);
			imageArea->set_tooltip_text("Image");
		}

		void createProcessedImageCanvas(char* imagePath = 0) {
			processedImage = new cv::Mat();

			if (imagePath == 0) {
				processedImageArea = new ImageCanvas(*image, ImageCanvas::TYPE_VIDEO);
				processedImageArea->set_tooltip_text("Processed video");
				return;
			}

			*processedImage = image->clone();
			processedImageArea = new ImageCanvas(*image, ImageCanvas::TYPE_IMAGE);
			processedImageArea->set_tooltip_text("Processed image");
		}

	public:
		MainWindow(char* imagePath) :
				box(Gtk::ORIENTATION_VERTICAL, 2) {
			set_title("OpenCV with GTK and Video");
			set_border_width(10);

			this->createOriginalImageCanvas(imagePath);
			originalFrame.set_label("OpenCV and GTK with image");
			originalFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			originalFrame.set_shadow_type(Gtk::SHADOW_OUT);
			originalFrame.set_size_request(160, 120);
			originalFrame.set_hexpand(true);
			originalFrame.set_vexpand(true);
			originalFrame.add(*imageArea);

			this->createProcessedImageCanvas(imagePath);
			processedFrame.set_label("OpenCV and GTK with processed image");
			processedFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			processedFrame.set_shadow_type(Gtk::SHADOW_OUT);
			processedFrame.set_size_request(160, 120);
			processedFrame.set_hexpand(true);
			processedFrame.set_vexpand(true);
			processedFrame.add(*processedImageArea);

			this->box.add(processedFrame);
			this->box.add(originalFrame);

			this->box.show();
			add(this->box);
			show_all();
		}

		MainWindow() :
				box(Gtk::ORIENTATION_VERTICAL, 2) {
			set_title("OpenCV with GTK with Video");
			set_border_width(10);

			this->createOriginalImageCanvas();

			originalFrame.set_label("OpenCV and GTK");
			originalFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			originalFrame.set_shadow_type(Gtk::SHADOW_OUT);
			originalFrame.set_size_request(320, 240);
			originalFrame.add(*imageArea);

			add(originalFrame);

			show_all();
		}

		~MainWindow() {
			delete image;
			delete imageArea;
		}
};
#endif /* SRC_MAINWINDOW_CPP_ */

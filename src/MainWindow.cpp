#ifndef SRC_MAINWINDOW_CPP_
#define SRC_MAINWINDOW_CPP_

#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include "ImageCanvas.cpp"

class MainWindow: public Gtk::Window {
	protected:

		Gtk::ScrolledWindow originalFrameScrool;
		Gtk::ScrolledWindow processedFrameScrool;

		Gtk::Frame originalFrame;
		ImageCanvas* imageArea;

		Gtk::Frame processedFrame;
		ImageCanvas* processedImageArea;

		Gtk::Box mainBox;

		Gtk::Button applyFilter;
		Gtk::Button openNewImage;

		void createOriginalImageCanvas(char* imagePath = 0) {

			if (imagePath == 0) {
				imageArea = new ImageCanvas(imagePath, ImageCanvas::TYPE_VIDEO);
				imageArea->set_tooltip_text("");
				return;
			}

			imageArea = new ImageCanvas(imagePath, ImageCanvas::TYPE_IMAGE);
			imageArea->set_tooltip_text(imagePath);
		}

		void createProcessedImageCanvas(char* imagePath = 0) {

			if (imagePath == 0) {
				processedImageArea = new ImageCanvas(imagePath, ImageCanvas::TYPE_VIDEO);
				processedImageArea->set_tooltip_text("Processed video");
				return;
			}

			processedImageArea = new ImageCanvas(imagePath, ImageCanvas::TYPE_IMAGE);
			processedImageArea->set_tooltip_text("Processed image");
		}

	public:
		MainWindow(char* imagePath) :
				mainBox(Gtk::ORIENTATION_VERTICAL, 2), applyFilter("_Apply filter", true), openNewImage("_Open image", true) {

			set_title("OpenCV with GTK and Video");
			set_border_width(10);

			this->createOriginalImageCanvas(imagePath);

			originalFrameScrool.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
			originalFrameScrool.set_hexpand(true);
			originalFrameScrool.set_vexpand(true);
			originalFrameScrool.add(*imageArea);

			originalFrame.set_label("OpenCV and GTK with image");
			originalFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			originalFrame.set_shadow_type(Gtk::SHADOW_OUT);
			originalFrame.set_size_request(160, 120);
			originalFrame.set_hexpand(true);
			originalFrame.set_vexpand(true);
			originalFrame.add(originalFrameScrool);

			this->createProcessedImageCanvas(imagePath);

			processedFrameScrool.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
			processedFrameScrool.set_hexpand(true);
			processedFrameScrool.set_vexpand(true);
			processedFrameScrool.add(*processedImageArea);

			processedFrame.set_label("OpenCV and GTK with processed image");
			processedFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			processedFrame.set_shadow_type(Gtk::SHADOW_OUT);
			processedFrame.set_size_request(160, 120);
			processedFrame.set_hexpand(true);
			processedFrame.set_vexpand(true);
			processedFrame.add(processedFrameScrool);

			this->mainBox.add(originalFrame);
			this->mainBox.add(processedFrame);
			this->mainBox.add(applyFilter);
			this->mainBox.add(openNewImage);

			this->applyFilter.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::filterMethod));
			this->openNewImage.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::chooseImage));

			this->mainBox.show();
			add(this->mainBox);

			show_all();
		}

		void filterMethod() {

//			static int c = 50;
//
//			cv::Vec3b color;
//			color.val[0] = 0;
//			color.val[1] = 255;
//			color.val[2] = 0;

//			for (int row = 0; row < image->rows; row++) {
//				for (int col = 0; col < image->cols; col++) {
//					//cv::Vec3b intensity = image.at<cv::Vec3b>(col, row);
//					image->at<cv::Vec3b>(row, col) = color;
//				}
//			}
//			for (int row = 0; row < image->rows; row++) {
//				for (int col = 0; col < c; col++) {
//					//cv::Vec3b intensity = image.at<cv::Vec3b>(col, row);
//					processedImage->at<cv::Vec3b>(row, col) = color;
//				}
//			}
//			c += 2;
			cv::cvtColor(imageArea->image, processedImageArea->image, cv::COLOR_BGR2GRAY);
			cv::GaussianBlur(processedImageArea->image, processedImageArea->image, cv::Size(0, 0), 1);
//			cv::medianBlur(*image, *processedImage, 7);

			processedImageArea->queue_draw();

			std::cout << "Image processed" << std::endl;
		}

		MainWindow() :
				mainBox(Gtk::ORIENTATION_VERTICAL, 2) {
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
			delete imageArea;
		}

		void chooseImage() {
			Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
			dialog.set_transient_for(*this);

			//Add response buttons the the dialog:
			dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
			dialog.add_button("_Open", Gtk::RESPONSE_OK);

			//Add filters, so that only certain file types can be selected:

			auto filterOften = Gtk::FileFilter::create();
			filterOften->set_name("Most used file types");
			filterOften->add_mime_type("image/bmp");
			filterOften->add_mime_type("image/dib");
			filterOften->add_mime_type("image/jpg");
			filterOften->add_mime_type("image/jpeg");
			filterOften->add_mime_type("image/jpe");
			filterOften->add_mime_type("image/png");
			dialog.add_filter(filterOften);

			auto filterBmp = Gtk::FileFilter::create();
			filterBmp->set_name("Windows bitmaps");
			filterBmp->add_mime_type("image/bmp");
			filterBmp->add_mime_type("image/dib");
			dialog.add_filter(filterBmp);

			auto filterJpg = Gtk::FileFilter::create();
			filterJpg->set_name("JPEG files");
			filterJpg->add_mime_type("image/jpg");
			filterJpg->add_mime_type("image/jpeg");
			filterJpg->add_mime_type("image/jpe");
			dialog.add_filter(filterJpg);

			auto filterJpg2 = Gtk::FileFilter::create();
			filterJpg2->set_name("JPEG 2000 files");
			filterJpg2->add_mime_type("image/jp2");
			dialog.add_filter(filterJpg2);

			auto filterPng = Gtk::FileFilter::create();
			filterPng->set_name("Portable Network Graphics");
			filterPng->add_mime_type("image/png");
			dialog.add_filter(filterPng);

			auto filterWebP = Gtk::FileFilter::create();
			filterWebP->set_name("WebP");
			filterWebP->add_mime_type("image/webP");
			dialog.add_filter(filterWebP);

			auto filterPortable = Gtk::FileFilter::create();
			filterPortable->set_name("Portable image format");
			filterPortable->add_mime_type("image/pbm");
			filterPortable->add_mime_type("image/pgm");
			filterPortable->add_mime_type("image/ppm");
			dialog.add_filter(filterPortable);

			auto filterSunR = Gtk::FileFilter::create();
			filterSunR->set_name("Sun rasters");
			filterSunR->add_mime_type("image/sr");
			filterSunR->add_mime_type("image/ras");
			dialog.add_filter(filterSunR);

			auto filterTiff = Gtk::FileFilter::create();
			filterTiff->set_name("TIFF files");
			filterTiff->add_mime_type("image/tiff");
			filterTiff->add_mime_type("image/tif");
			dialog.add_filter(filterTiff);

			auto filter_any = Gtk::FileFilter::create();
			filter_any->set_name("Any files");
			filter_any->add_pattern("*");
			dialog.add_filter(filter_any);

			//Show the dialog and wait for a user response:
			int result = dialog.run();

			//Handle the response:
			switch (result) {
				case (Gtk::RESPONSE_OK): {
					std::string filename = dialog.get_filename();
					std::cout << "Opening: " << filename << std::endl;

					imageArea->image = cv::imread(filename, CV_BGR2RGB);
					imageArea->set_tooltip_text(filename);
					imageArea->queue_draw();
					break;
				}
				case (Gtk::RESPONSE_CANCEL): {
					std::cout << "Cancel" << std::endl;
					break;
				}
				default: {
					std::cout << "Unexpected option" << std::endl;
					break;
				}
			}
		}

};
#endif /* SRC_MAINWINDOW_CPP_ */

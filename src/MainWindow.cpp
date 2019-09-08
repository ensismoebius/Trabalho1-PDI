#ifndef SRC_MAINWINDOW_CPP_
#define SRC_MAINWINDOW_CPP_

#include <stdexcept>
#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include "ImageCanvas.cpp"

class MainWindow: public Gtk::Window {
	protected:

		Gtk::ScrolledWindow originalFrameScrool;
		Gtk::ScrolledWindow processedFrameScrool;
		Gtk::ScrolledWindow maskFrameScrool;
		Gtk::ScrolledWindow spectrumFrameScrool;

		Gtk::Frame originalFrame;
		ImageCanvas* originalImageArea;

		Gtk::Frame processedFrame;
		ImageCanvas* processedImageArea;

		Gtk::Frame maskFrame;
		ImageCanvas* maskImageArea;

		Gtk::Frame spectrumFrame;
		ImageCanvas* spectrumImageArea;

		Gtk::Box mainBox;

		Gtk::Box horizontalBox1;
		Gtk::Box horizontalBox2;
		Gtk::Box horizontalBox3;

		Gtk::Box maskRadiosBox;
		Gtk::RadioButton nenhum, passaAlta, passaBanda, passaBaixa, paraBanda;

		Gtk::Box measuresScalesBox;
		Glib::RefPtr<Gtk::Adjustment> innerRadiusAjustments;
		Gtk::Scale innerRadius;
		Glib::RefPtr<Gtk::Adjustment> outerRadiusAjustments;
		Gtk::Scale outerRadius;
		Glib::RefPtr<Gtk::Adjustment> sigmaAjustments;
		Gtk::Scale sigma;

		Gtk::Button applyFilter;
		Gtk::Button openNewImage;

		void createOriginalImageCanvas(char* imagePath = 0) {

			if (imagePath == 0) {
				originalImageArea = new ImageCanvas(imagePath, ImageCanvas::TYPE_VIDEO);
				originalImageArea->set_tooltip_text("");
				return;
			}

			originalImageArea = new ImageCanvas(imagePath, ImageCanvas::TYPE_IMAGE);
			originalImageArea->set_tooltip_text(imagePath);
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

		void createMaskImageCanvas() {
			if (originalImageArea == 0) {
				throw std::runtime_error("Error at 'createMaskImageCanvas()' method:\n Original image area must be defined first!!");
			}
			maskImageArea = new ImageCanvas(originalImageArea->image);
			maskImageArea->set_tooltip_text("Mask");
		}

		void createSpectrumImageCanvas() {
			if (originalImageArea == 0) {
				throw std::runtime_error("Error at 'createMaskImageCanvas()' method:\n Original image area must be defined first!!");
			}
			spectrumImageArea = new ImageCanvas(originalImageArea->image);
			spectrumImageArea->set_tooltip_text("Spectrum");
		}

	public:
		MainWindow(char* imagePath) :
				mainBox(Gtk::ORIENTATION_VERTICAL, 2), //
				horizontalBox1(Gtk::ORIENTATION_HORIZONTAL, 2), //
				horizontalBox2(Gtk::ORIENTATION_HORIZONTAL, 2), //
				horizontalBox3(Gtk::ORIENTATION_HORIZONTAL, 2), //
				maskRadiosBox(Gtk::ORIENTATION_VERTICAL), //
				nenhum("_0-Nenhuma", true), //
				passaAlta("_1-Passa alta", true), //
				passaBanda("_2-Passa banda", true), //
				passaBaixa("_3-Passa baixa", true), //
				paraBanda("_4-Para banda", true), //
				measuresScalesBox(Gtk::ORIENTATION_VERTICAL), //
				innerRadiusAjustments(Gtk::Adjustment::create(0, 0, 100)), //
				innerRadius(innerRadiusAjustments, Gtk::ORIENTATION_HORIZONTAL), //
				outerRadiusAjustments(Gtk::Adjustment::create(0, 0, 100)), //
				outerRadius(outerRadiusAjustments, Gtk::ORIENTATION_HORIZONTAL), //
				sigmaAjustments(Gtk::Adjustment::create(0, 0, 100)), //
				sigma(sigmaAjustments, Gtk::ORIENTATION_HORIZONTAL), //
				applyFilter("_Apply filter", true), //
				openNewImage("_Open image", true) //
		{
			set_title("OpenCV with GTK and Video");
			set_border_width(10);

			this->createOriginalImageCanvas(imagePath);

			originalFrameScrool.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
			originalFrameScrool.set_hexpand(true);
			originalFrameScrool.set_vexpand(true);
			originalFrameScrool.add(*originalImageArea);

			originalFrame.set_label("Image");
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

			processedFrame.set_label("Processed image");
			processedFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			processedFrame.set_shadow_type(Gtk::SHADOW_OUT);
			processedFrame.set_size_request(160, 120);
			processedFrame.set_hexpand(true);
			processedFrame.set_vexpand(true);
			processedFrame.add(processedFrameScrool);

			this->createMaskImageCanvas();

			maskFrameScrool.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
			maskFrameScrool.set_hexpand(true);
			maskFrameScrool.set_vexpand(true);
			maskFrameScrool.add(*maskImageArea);

			maskFrame.set_label("Mask");
			maskFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			maskFrame.set_shadow_type(Gtk::SHADOW_OUT);
			maskFrame.set_size_request(160, 120);
			maskFrame.set_hexpand(true);
			maskFrame.set_vexpand(true);
			maskFrame.add(maskFrameScrool);

			this->createSpectrumImageCanvas();

			spectrumFrameScrool.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
			spectrumFrameScrool.set_hexpand(true);
			spectrumFrameScrool.set_vexpand(true);
			spectrumFrameScrool.add(*spectrumImageArea);

			spectrumFrame.set_label("Spectrum");
			spectrumFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			spectrumFrame.set_shadow_type(Gtk::SHADOW_OUT);
			spectrumFrame.set_size_request(160, 120);
			spectrumFrame.set_hexpand(true);
			spectrumFrame.set_vexpand(true);
			spectrumFrame.add(spectrumFrameScrool);

			this->horizontalBox1.add(originalFrame);
			this->horizontalBox1.add(processedFrame);
			this->mainBox.add(this->horizontalBox1);

			passaBaixa.join_group(nenhum);
			passaBanda.join_group(nenhum);
			paraBanda.join_group(nenhum);
			passaAlta.join_group(nenhum);

			maskRadiosBox.pack_start(nenhum, true, true, 0);
			maskRadiosBox.pack_start(passaAlta, true, true, 0);
			maskRadiosBox.pack_start(passaBanda, true, true, 0);
			maskRadiosBox.pack_start(passaBaixa, true, true, 0);
			maskRadiosBox.pack_start(paraBanda, true, true, 0);
			this->horizontalBox2.add(maskRadiosBox);

			measuresScalesBox.set_hexpand(true);
			measuresScalesBox.pack_start(innerRadius, true, true, 0);
			measuresScalesBox.pack_start(outerRadius, true, true, 0);
			measuresScalesBox.pack_start(sigma, true, true, 0);
			this->horizontalBox2.add(measuresScalesBox);

			this->horizontalBox2.set_hexpand(true);
			this->mainBox.add(this->horizontalBox2);

			this->horizontalBox3.add(maskFrame);
			this->horizontalBox3.add(spectrumFrame);
			this->mainBox.add(this->horizontalBox3);

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
			cv::cvtColor(originalImageArea->image, processedImageArea->image, cv::COLOR_BGR2GRAY);
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
			originalFrame.add(*originalImageArea);

			add(originalFrame);

			show_all();
		}

		~MainWindow() {
			delete originalImageArea;
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

					originalImageArea->image = cv::imread(filename, CV_BGR2RGB);
					originalImageArea->set_tooltip_text(filename);
					originalImageArea->queue_draw();
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

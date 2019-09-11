#ifndef SRC_MAINWINDOW_CPP_
#define SRC_MAINWINDOW_CPP_

#include <cmath>
#include <stdexcept>
#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

#include "lib/dft2.h"

#include "Matrices.cpp"
#include "ImageCanvas.cpp"

class MainWindow: public Gtk::Window {
	protected:

		Gtk::ScrolledWindow originalFrameScrool;
		Gtk::ScrolledWindow processedFrameScrool;
		Gtk::ScrolledWindow maskFrameScrool;
		Gtk::ScrolledWindow spectrumFrameScrool;

		Gtk::Frame originalFrame;
		Gtk::Frame processedFrame;
		Gtk::Frame maskFrame;
		Gtk::Frame spectrumFrame;

		ImageCanvas* originalImageArea;
		ImageCanvas* processedImageArea;
		ImageCanvas* spectrumImageArea;
		ImageCanvas* maskImageArea;

		Gtk::Box mainBox;
		Gtk::Grid gridBox;
		Gtk::Box horizontalBox;

		Gtk::Box maskRadiosBox;
		Gtk::RadioButton none, highPass, bandPass, lowPass, bandStop;

		Gtk::Label lblinnerRadius;
		Gtk::Label lblouterRadius;
		Gtk::Label lblsigma;

		Gtk::Box measuresScalesBox;
		Glib::RefPtr<Gtk::Adjustment> innerRadiusAjustments;
		Gtk::Scale innerRadius;
		Glib::RefPtr<Gtk::Adjustment> outerRadiusAjustments;
		Gtk::Scale outerRadius;
		Glib::RefPtr<Gtk::Adjustment> sigmaAjustments;
		Gtk::Scale sigma;

		Gtk::Button openNewImage;

		void createOriginalImageCanvas(const char* imagePath = 0) {
			originalImageArea = new ImageCanvas(Matrices::originalImage, ImageCanvas::TYPE_IMAGE);
			originalImageArea->set_tooltip_text(imagePath);
		}

		void createProcessedImageCanvas() {
			processedImageArea = new ImageCanvas(Matrices::processedImage, ImageCanvas::TYPE_IMAGE);
			processedImageArea->set_tooltip_text("Processed image");
		}

		void createMaskImageCanvas() {

			if (originalImageArea == 0) {
				throw std::runtime_error("Error at 'createMaskImageCanvas()' method:\n Original image area must be defined first!!");
			}

			maskImageArea = new ImageCanvas(Matrices::maskImage, ImageCanvas::TYPE_IMAGE);
			maskImageArea->set_tooltip_text("Mask");
		}

		void createSpectrumImageCanvas() {

			if (originalImageArea == 0) {
				throw std::runtime_error("Error at 'createMaskImageCanvas()' method:\n Original image area must be defined first!!");
			}

			spectrumImageArea = new ImageCanvas(Matrices::spectrumImage, ImageCanvas::TYPE_IMAGE);
			spectrumImageArea->set_tooltip_text("Spectrum");
		}

		void on_outerRadiusAjustments_changed() {
			processImage();
		}
		void on_innerRadiusAjustments_changed() {
			processImage();
		}
		void on_sigmaAjustments_changed() {
			processImage();
		}
		void on_none_changed() {
			processImage();
			updateSlidersAndLabelsSensitivity();
		}
		void on_highPass_changed() {
			processImage();
			updateSlidersAndLabelsSensitivity();
		}
		void on_bandPass_changed() {
			processImage();
			updateSlidersAndLabelsSensitivity();
		}
		void on_lowPass_changed() {
			processImage();
			updateSlidersAndLabelsSensitivity();
		}
		void on_bandStop_changed() {
			processImage();
			updateSlidersAndLabelsSensitivity();
		}

	public:
		MainWindow(char* imagePath) :
				mainBox(Gtk::ORIENTATION_VERTICAL, 2), //
				horizontalBox(Gtk::ORIENTATION_HORIZONTAL, 2), //
				maskRadiosBox(Gtk::ORIENTATION_VERTICAL), //
				none("_0-None", true), //
				highPass("_1-High pass", true), //
				bandPass("_2-Band pass", true), //
				lowPass("_3-Low pass", true), //
				bandStop("_4-Stop band", true), //
				lblinnerRadius("Inner Radius"), //
				lblouterRadius("Outer Radius"), //
				lblsigma("Blur sigma"), //
				measuresScalesBox(Gtk::ORIENTATION_VERTICAL), //
				innerRadiusAjustments(Gtk::Adjustment::create(0, 0, 100)), //
				innerRadius(innerRadiusAjustments, Gtk::ORIENTATION_HORIZONTAL), //
				outerRadiusAjustments(Gtk::Adjustment::create(0, 0, 100)), //
				outerRadius(outerRadiusAjustments, Gtk::ORIENTATION_HORIZONTAL), //
				sigmaAjustments(Gtk::Adjustment::create(0, 0, 100)), //
				sigma(sigmaAjustments, Gtk::ORIENTATION_HORIZONTAL), //
				openNewImage("_Open image", true) //
		{

			set_title("OpenCV with GTK and Video");
			set_border_width(10);

			Matrices::init(imagePath);

			this->createOriginalImageCanvas(imagePath);
			this->createProcessedImageCanvas();
			this->createSpectrumImageCanvas();
			this->createMaskImageCanvas();

			originalFrameScrool.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
			originalFrameScrool.set_hexpand(true);
			originalFrameScrool.set_vexpand(true);
			originalFrameScrool.add(*originalImageArea);

			originalFrame.set_label("Image");
			originalFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			originalFrame.set_shadow_type(Gtk::SHADOW_OUT);
			originalFrame.set_hexpand(true);
			originalFrame.set_vexpand(true);
			originalFrame.add(originalFrameScrool);

			processedFrameScrool.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
			processedFrameScrool.set_hexpand(true);
			processedFrameScrool.set_vexpand(true);
			processedFrameScrool.add(*processedImageArea);

			processedFrame.set_label("Processed image");
			processedFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			processedFrame.set_shadow_type(Gtk::SHADOW_OUT);
			processedFrame.set_hexpand(true);
			processedFrame.set_vexpand(true);
			processedFrame.add(processedFrameScrool);

			maskFrameScrool.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
			maskFrameScrool.set_hexpand(true);
			maskFrameScrool.set_vexpand(true);
			maskFrameScrool.add(*maskImageArea);

			maskFrame.set_label("Mask");
			maskFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			maskFrame.set_shadow_type(Gtk::SHADOW_OUT);
			maskFrame.set_hexpand(true);
			maskFrame.set_vexpand(true);
			maskFrame.add(maskFrameScrool);

			spectrumFrameScrool.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
			spectrumFrameScrool.set_hexpand(true);
			spectrumFrameScrool.set_vexpand(true);
			spectrumFrameScrool.add(*spectrumImageArea);

			spectrumFrame.set_label("Spectrum");
			spectrumFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
			spectrumFrame.set_shadow_type(Gtk::SHADOW_OUT);
			spectrumFrame.set_hexpand(true);
			spectrumFrame.set_vexpand(true);
			spectrumFrame.add(spectrumFrameScrool);

			this->gridBox.set_row_homogeneous(true);
			this->gridBox.set_column_homogeneous(true);
			this->gridBox.attach(maskFrame, 0, 1, 1, 1);
			this->gridBox.attach(spectrumFrame, 1, 1, 1, 1);
			this->gridBox.attach(originalFrame, 0, 0, 1, 1);
			this->gridBox.attach(processedFrame, 1, 0, 1, 1);
			this->mainBox.add(this->gridBox);

			lowPass.join_group(none);
			bandPass.join_group(none);
			bandStop.join_group(none);
			highPass.join_group(none);

			maskRadiosBox.pack_start(none, true, true, 0);
			maskRadiosBox.pack_start(highPass, true, true, 0);
			maskRadiosBox.pack_start(bandPass, true, true, 0);
			maskRadiosBox.pack_start(lowPass, true, true, 0);
			maskRadiosBox.pack_start(bandStop, true, true, 0);
			this->horizontalBox.add(maskRadiosBox);

			measuresScalesBox.set_hexpand(true);
			measuresScalesBox.pack_start(lblinnerRadius, true, true, 0);
			measuresScalesBox.pack_start(innerRadius, true, true, 0);
			measuresScalesBox.pack_start(lblouterRadius, true, true, 0);
			measuresScalesBox.pack_start(outerRadius, true, true, 0);
			measuresScalesBox.pack_start(lblsigma, true, true, 0);
			measuresScalesBox.pack_start(sigma, true, true, 0);
			this->horizontalBox.set_hexpand(true);
			this->horizontalBox.add(measuresScalesBox);

			this->mainBox.add(this->horizontalBox);

			this->mainBox.add(openNewImage);

			none.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_none_changed));
			openNewImage.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::chooseImage));
			lowPass.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_lowPass_changed));
			bandPass.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_bandPass_changed));
			bandStop.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_bandStop_changed));
			highPass.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_highPass_changed));
			sigma.signal_value_changed().connect(sigc::mem_fun(*this, &MainWindow::on_sigmaAjustments_changed));
			innerRadius.signal_value_changed().connect(sigc::mem_fun(*this, &MainWindow::on_innerRadiusAjustments_changed));
			outerRadius.signal_value_changed().connect(sigc::mem_fun(*this, &MainWindow::on_outerRadiusAjustments_changed));

			this->mainBox.show();
			add(this->mainBox);

			updateSlidersAndLabelsSensitivity();
			updateSlidersRange();
			processImage();

			show_all();
		}

		void updateSlidersAndLabelsSensitivity() {
			if (none.get_active()) {
				sigma.set_sensitive(false);
				lblsigma.set_sensitive(false);

				innerRadius.set_sensitive(false);
				lblinnerRadius.set_sensitive(false);

				outerRadius.set_sensitive(false);
				lblouterRadius.set_sensitive(false);
			}

			if (lowPass.get_active() || highPass.get_active()) {
				sigma.set_sensitive(true);
				lblsigma.set_sensitive(true);

				innerRadius.set_sensitive(false);
				lblinnerRadius.set_sensitive(false);

				outerRadius.set_sensitive(true);
				lblouterRadius.set_sensitive(true);
			}

			if (bandPass.get_active() || bandStop.get_active()) {
				sigma.set_sensitive(true);
				lblsigma.set_sensitive(true);

				innerRadius.set_sensitive(true);
				lblinnerRadius.set_sensitive(true);

				outerRadius.set_sensitive(true);
				lblouterRadius.set_sensitive(true);
			}
		}

		void updateSlidersRange() {

			double maxsize = sqrt(pow(Matrices::complex.cols / 2, 2) + pow(Matrices::complex.rows / 2, 2));

			innerRadiusAjustments.get()->set_upper(maxsize);
			outerRadiusAjustments.get()->set_upper(maxsize);

			innerRadius.queue_draw();
			outerRadius.queue_draw();
		}

		void processImage() {

			double sigmaValue = sigma.get_value() <= 1 ? 1 : this->sigma.get_value();
			double outerRadiusValue = outerRadius.get_value() <= 0 ? 0 : outerRadius.get_value();
			double innerRadiusValue = innerRadius.get_value() <= 0 ? 0 : innerRadius.get_value();

			updateMask(sigmaValue, outerRadiusValue, innerRadiusValue);
			extractSpectrumAndIDFT();
			convertForVisualization();

			maskImageArea->queue_draw();
			spectrumImageArea->queue_draw();
			originalImageArea->queue_draw();
			processedImageArea->queue_draw();
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
			delete processedImageArea;
			delete spectrumImageArea;
			delete maskImageArea;
		}

		void chooseImage() {
			Gtk::FileChooserDialog dialog("Please choose a image file", Gtk::FILE_CHOOSER_ACTION_OPEN);
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

					Matrices::init(filename.c_str());
					originalImageArea->set_tooltip_text(filename);
					updateSlidersRange();
					processImage();
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

	private:
		void updateMask(double sigmaValue, double outerRadiusValue, double innerRadiusValue) {
			if (none.get_active()) {
				Matrices::maskImage = createHighLowPassFilter(Matrices::complex, 0, true, sigmaValue);
			}
			if (lowPass.get_active()) {
				Matrices::maskImage = createHighLowPassFilter(Matrices::complex, outerRadiusValue, false, sigmaValue);
			}
			if (highPass.get_active()) {
				Matrices::maskImage = createHighLowPassFilter(Matrices::complex, outerRadiusValue, true, sigmaValue);
			}
			if (bandPass.get_active()) {
				Matrices::maskImage = createBandStopPassFilter(Matrices::complex, innerRadiusValue, outerRadiusValue, true, sigmaValue);
			}
			if (bandStop.get_active()) {
				Matrices::maskImage = createBandStopPassFilter(Matrices::complex, innerRadiusValue, outerRadiusValue, false, sigmaValue);
			}
			// maskImage.convertTo(maskImage, CV_32F, 1);
		}

		void extractSpectrumAndIDFT() {
//			cv::cvtColor(Matrices::originalImage, Matrices::processedImage, CV_BGR2GRAY);

			Matrices::originalImage.convertTo(Matrices::processedImage, CV_32F);

			Matrices::complex = dft2(Matrices::processedImage);
			if (isMaskApplied()) {
				Matrices::complex = combineDFTComplexAndMask(Matrices::complex, Matrices::maskImage);
			}
			Matrices::spectrumImage = genSpectrumImage(Matrices::complex);
			Matrices::processedImage = idft2(Matrices::complex);
		}

		void convertForVisualization() {

			maskImageArea->image = Matrices::maskImage.clone();
			originalImageArea->image = Matrices::originalImage.clone();
			spectrumImageArea->image = Matrices::spectrumImage.clone();
			processedImageArea->image = Matrices::processedImage.clone();

			maskImageArea->image.convertTo(maskImageArea->image, CV_8U, 255);
			originalImageArea->image.convertTo(originalImageArea->image, CV_8U);
			spectrumImageArea->image.convertTo(spectrumImageArea->image, CV_8U, 255);
			processedImageArea->image.convertTo(processedImageArea->image, CV_8U, 255);
		}

		bool isMaskApplied() {
			if (highPass.get_active() && outerRadius.get_value() > 0) return true;
			if (lowPass.get_active() && outerRadius.get_value() > 0) return true;
			if (bandPass.get_active() && (outerRadius.get_value() > 0 || innerRadius.get_value() > 0)) return true;
			if (bandStop.get_active() && (outerRadius.get_value() > 0 || innerRadius.get_value() > 0)) return true;
			return false;
		}

};
#endif /* SRC_MAINWINDOW_CPP_ */

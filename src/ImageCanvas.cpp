/**
 * @author André Furlan
 * @email ensismoebius@gmail.com
 * This whole project are under GPLv3, for
 * more information read the license file
 *
 * 29 de ago de 2019
 *
 */
#ifndef SRC_IMAGECANVAS_CPP_
#define SRC_IMAGECANVAS_CPP_

#include <gtkmm-3.0/gtkmm.h>
#include <opencv2/opencv.hpp>

class ImageCanvas: public Gtk::DrawingArea {
	public:
		inline static const unsigned char TYPE_IMAGE = 0;
		inline static const unsigned char TYPE_VIDEO = 1;

	protected:
		cv::Mat inputImage;
		cv::Mat outputImage;

		cv::VideoCapture cameraCapturer;

		unsigned char mediaType;
		bool videoCapturingActive;

		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cairoContextPtr) {

			if (this->mediaType == TYPE_VIDEO) {
				if (!videoCapturingActive) return false;
				cameraCapturer.read(inputImage);
			}

			if (inputImage.empty()) return false;

			cv::cvtColor(inputImage, outputImage, CV_BGR2RGB);

			Gdk::Cairo::set_source_pixbuf(cairoContextPtr, Gdk::Pixbuf::create_from_data(outputImage.data, Gdk::COLORSPACE_RGB, false, 8, outputImage.cols, outputImage.rows, outputImage.step));

			cairoContextPtr->paint();

			return true;
		}
		bool on_timeout() {
			Glib::RefPtr<Gdk::Window> win = get_window();
			if (win) {
				Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
				win->invalidate_rect(r, false);
			}
			return true;
		}
	public:

		ImageCanvas(cv::Mat& image, const unsigned char mediaType = TYPE_IMAGE) {

			this->inputImage = image;
			this->mediaType = mediaType;

			if (mediaType == TYPE_VIDEO) {
				cameraCapturer.open(0);
				if (cameraCapturer.isOpened() == true) {
					videoCapturingActive = true;
					Glib::signal_timeout().connect(sigc::mem_fun(*this, &ImageCanvas::on_timeout), 50);
				} else {
					videoCapturingActive = false;
				}
			}
		}
};

#endif /* SRC_IMAGECANVAS_CPP_ */

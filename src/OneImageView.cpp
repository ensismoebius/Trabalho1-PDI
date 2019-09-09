//#ifndef SRC_ONEIMAGEVIEW_CPP_
//#define SRC_ONEIMAGEVIEW_CPP_
//
//#include <gtkmm-3.0/gtkmm.h>
//#include <opencv2/opencv.hpp>
//
//#include "Matrices.cpp"
//
//class OneImageView: public Gtk::Window {
//	protected:
//
//		Gtk::ScrolledWindow originalFrameScrool;
//		Gtk::Frame originalFrame;
//		ImageCanvas* originalImageArea;
//
//	public:
//		OneImageView(cv::Mat& image) {
//
//			set_title("Visualization");
//			set_border_width(10);
//
//			originalImageArea = new ImageCanvas(image, ImageCanvas::TYPE_IMAGE);
//
//			originalFrameScrool.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
//			originalFrameScrool.set_hexpand(true);
//			originalFrameScrool.set_vexpand(true);
//			originalFrameScrool.add(*originalImageArea);
//
//			originalFrame.set_label("Image");
//			originalFrame.set_label_align(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
//			originalFrame.set_shadow_type(Gtk::SHADOW_OUT);
//			originalFrame.set_hexpand(true);
//			originalFrame.set_vexpand(true);
//			originalFrame.add(originalFrameScrool);
//
//			originalFrameScrool.show();
//			add(originalFrameScrool);
//			show_all();
//		}
//
//		void setImage(cv::Mat& image) {
//			originalImageArea->image = image.clone();
//			originalImageArea->queue_draw();
//			originalFrameScrool.queue_draw();
//		}
//
//		~OneImageView() {
//			delete originalImageArea;
//		}
//};
//#endif /* SRC_ONEIMAGEVIEW_CPP_ */

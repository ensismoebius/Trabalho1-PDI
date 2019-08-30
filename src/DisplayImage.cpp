///**
// * @author André Furlan
// * @email ensismoebius@gmail.com
// * This whole project are under GPLv3, for
// * more information read the license file
// *
// * 19 de ago de 2019
// *
// */
//#include <opencv2/opencv.hpp>
//
//int main(int argc, char** argv) {
//	cv::Mat image(480, 640, CV_8U);
//	image = cv::imread(argv[1], 1);
//
//	if (argc != 2 || !image.data) {
//		printf("No image data \n");
//		return -1;
//	}
//
//	cv::Vec3b color;
//	color.val[0] = 0;
//	color.val[1] = 255;
//	color.val[2] = 0;
//
//	for (int row = 0; row < image.rows; row++) {
//		for (int col = 0; col < image.cols; col++) {
//			//cv::Vec3b intensity = image.at<cv::Vec3b>(col, row);
//			image.at<cv::Vec3b>(row, col) = color;
//		}
//	}
//
//	//cv::putText(image, "Hello World!", cv::Point(0, 100), cv::FONT_HERSHEY_PLAIN | cv::FONT_ITALIC, .0, cv::Scalar(255, 255, 0));
//
//	cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
//	cv::imshow("Display Image", image);
//	cv::waitKey(0);
//
//	return 0;
//}

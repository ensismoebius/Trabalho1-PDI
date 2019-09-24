#include <opencv/cv.hpp>

int main(int argc, char **argv) {
	std::string file = "/home/ensismoebius/workspaces/c-workspace/opencv/img/LF.jpg";

	cv::Mat src = cv::imread(file, 0);
	cv::Mat dst = cv::Mat();
	cv::Mat gray = cv::Mat();
}


#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

typedef struct lparam {
	cv::Scalar col;
	int thk;
	cv::Point pos;
} lanepar;

typedef struct linenf {
	int idline;
}linf;

enum ltypes {
	STRAIGHT_LINE, LINE_AND_DOT
};

class _Mdraw {
protected:
	cv::Mat img;	// default image
	std::vector<lparam> vimg;
public:
	_Mdraw(const cv::Mat& srs);
	linf addlane(cv::Scalar col, int thk, cv::Point fpos);
	cv::Mat drawline(linf line, cv::Point npos, int type);
};

class MapDrawer : private _Mdraw {
	cv::Point2f tlpos, brpos;
	float xdelc, ydelc;
public:
	MapDrawer(cv::Mat& src, cv::Point2f toplpos, cv::Point2f botrpos);
	linf addline(cv::Scalar col, int thk, cv::Point2f fpos);
	cv::Mat drawrealline(linf line, float xc, float yc, int type);
};

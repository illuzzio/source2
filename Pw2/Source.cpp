#include "MapDrawer.h"
#include <fstream>

using namespace cv;
using namespace std;

_Mdraw::_Mdraw(const cv::Mat& srs) {
	img = srs.clone();
}

linf _Mdraw::addlane(cv::Scalar col, int thk, cv::Point fpos)
{
	linf t;
	t.idline = vimg.size();
	lparam l;
	l.col = col;
	l.pos = fpos;
	l.thk = thk;
	vimg.push_back(l);
	return t;
}

cv::Mat  _Mdraw::drawline(linf line, cv::Point npos, int type)
{
	cv::line(img, vimg[line.idline].pos, npos, vimg[line.idline].col, vimg[line.idline].thk);
	vimg[line.idline].pos = npos;
	if (type = ltypes::LINE_AND_DOT) cv::circle(img, npos, 5, cv::Scalar(0, 0, 255), -1);
	return img.clone();
}

MapDrawer::MapDrawer(cv::Mat & src, cv::Point2f toplpos, cv::Point2f botrpos) : _Mdraw(src) {
	tlpos = toplpos;
	brpos = botrpos;
	xdelc = (brpos.x - tlpos.x) / src.cols;
	ydelc = (tlpos.y - brpos.y) / src.rows;
}

linf MapDrawer::addline(cv::Scalar col, int thk, cv::Point2f _fpos)
{
	cv::Point fpos((_fpos.x - tlpos.x) / xdelc, (tlpos.y - _fpos.y) / ydelc);
	return addlane(col, thk, fpos);
}

cv::Mat MapDrawer::drawrealline(linf line, float xc, float yc, int type)
{
	int x = (int)((xc - tlpos.x) / xdelc);
	int y = (int)((tlpos.y - yc) / ydelc);
	return drawline(line, cv::Point(x, y), type);
}

int main() {
	Mat image = imread("mapp.jpg");
	MapDrawer m(image, cv::Point2f(37.513499, 55.875643), cv::Point2f(37.542553, 55.865122));
	ifstream f("text.txt");
	double x, y; unsigned long long t1, t;
	f >> x >> y >> t;
	linf line = m.addline(Scalar(255, 0, 0), 2, cv::Point2f(y, x));
	while (!f.eof()) {
		f >> x >> y >> t1;
		imshow("maps", m.drawrealline(line, y, x, ltypes::LINE_AND_DOT));
		waitKey(t1 - t);
		t = t1;
	}
	return(0);
	
}
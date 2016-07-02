#ifndef LINEDETECTION_H
#define LINEDETECTION_H
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
class LineDetection
{
public:
	LineDetection();
	~LineDetection();

	//Funció que detecta la linea vertical dreta
	void detectRoadLines(Mat& frame, pair<Point, Point>& v1);

	//Selecciona el mètode a utilitzar
	void setMethod(int m);

private:
	//Kernels dels filtres
	Mat rightKernel, leftKernel, centralKernel;
	Point anchorLR, anchorC;
	int method = 2;
	//Binaritza la imatge per resaltar les linies
	void binarizeRoadLines(Mat& frame, Mat& output);
	//Localitza la linia mitjançant la Localització 1
	void localizeRightRoadLine(Mat& bIm, double& maxX);
	//Localitza la linia mitjançant la Localització 2 (Hough)
	void localizeRightRoadLineHough(Mat& bIm, double& maxX, double& maxTheta);

};
#endif

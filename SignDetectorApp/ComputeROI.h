#ifndef COMPUTEROI_H
#define COMPUTEROI_H
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Reduce2ROI.h"
#include "IPM.h"
#include "LineDetection.h"
#include "reduce2Road.h"
using namespace cv;
using namespace std;
class ComputeROI
{
public:
	ComputeROI();
	ComputeROI(Mat& ini);
	~ComputeROI();
	//Computa la ´ROI
	void compute(Mat& input, Mat&output,Rect& r);
	// Selecciona el metode desitjat
	void setMethod(int m);
	//Obte el metode actual
	int getMethod();
private:
	int method = 1;
	Reduce2ROI r2ROI;
	reduce2Road r2r;
	IPM ipm;
	LineDetection lDet;
};

#endif 
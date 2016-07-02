#ifndef SIGNDETECTOR_H
#define SIGNDETECTOR_H
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "QTTerminal.h"
using namespace cv;
using namespace std;
class SignDetector
{
public:
	SignDetector();
	~SignDetector();
	//Funció que detecta els senyals de la imatge input
	void detect(Mat& input, vector<vector<Point>>& detectedContourns, vector<Rect>& boundingBoxes,vector<int>& color);
	//Estableix la mida el frame
	void setSizeFrame(int h, int w);
private:
	bool showIm;
	//Troba els possibles senyals de input (binaritzada)
	void findContourns(Mat& input, vector<vector<Point> >& contours2, vector<Rect>& boundingBox);
	//Si dues senyals estan apilades, troba el divisor horitzontal entre elles.
	void findDivisor(vector<Point>& vec, Rect& r, Point& ini, Point& fi);
	//Mida del frame
	int height = 100;
	int width = 100;
};
#endif

#ifndef REDUCE2ROAD_H
#define REDUCE2ROAD_H
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
class reduce2Road
{
public:
	reduce2Road();
	reduce2Road(const Size& size);
	~reduce2Road();
	/*
	* Donat un frame el redueix a la part de la carretera (output)
	*/
	void getRoadImage(const Mat& input, Mat& output);
	/*
	* Donat un punt de la carretera et retorna el punt corresponent al frame
	*/
	void getOriginPosition(Point& p1, Point& output);

private:
	double wIni;
	double wSize;
	double hIni;
	double hSize;
};
#endif


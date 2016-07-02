#ifndef REDUCE2ROI_H
#define REDUCE2ROI_H
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
class Reduce2ROI
{
public:
	//Constructors
	Reduce2ROI();
	Reduce2ROI(Size& size);
	~Reduce2ROI();
	/** 
	 * Funció que donada una imatge i un punt ini i un punt fi
	 * Retalla la imatge per tal de que la linea que passa per ini i fi aparegui a ella 
	 * i retorna el rect utilitzat
	*/
	void Reduce(Mat& im, Mat& output, Rect& r, Point& ini, Point& fi);

private:
	int limitX = 0;
};

#endif
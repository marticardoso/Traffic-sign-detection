#ifndef IPM_H
#define IPM_H
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
class IPM
{
public:
	IPM();
	IPM(Size original);
	~IPM();
	//Mida de la imatge que s'entrarà
	int m = 480;
	int n = 620;
	

	//Posició de la camara
	int cx = 0;
	int cy = -10;
	int cz = 5;

	//Angle desviació
	double gamma = 0;

	//Angle cap al terre
	double theta = 3.1415 / 6;

	//Obertura de la camara
	double alpha = 30 / 2 * 3.1415 / 180;

	//Obte una imatge amb vistes d'ocell
	void InversePerspectiveMapping(Mat& frame, Mat& output);
	//Transforma un punt de IPM a coordenades de pixel
	void PerspectiveMapping(Point p, Point& p2);

private:
	Mat map_x, map_y;
	double minValX, maxValX;
	double minValY, maxValY;
	//Transforma unes coordenades de IPM a coordenades de pixel
	void PerspectiveMapping(double x, double y, double& x2, double& y2);
	//Transforma unes coordenades de pixel a coordenades de IPM
	void InversePerspectiveMapping(double x, double y, double& x2, double& y2);
	
};
#endif

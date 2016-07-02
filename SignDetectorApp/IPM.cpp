#include "IPM.h"
#include <cmath>
#include <iostream>
using namespace std;
const double pi = 3.1415;
IPM::IPM(){

}
IPM::IPM(Size original)
{
	int hImage = original.height; 
	int wImage = original.width;


	/*
	* PARAMETERS de IPM
	*/
	//Angle d'obertura
	alpha = 30 / 2 * pi / 180;

	//Posició de la camara
	cx = 0;
	cy = 0;
	cz = 5;

	//Angle desviació
	gamma = -pi/180*1;

	//Angle cap al terre
	theta = pi / 6;


	/*
	* Obté la matriu que mapeja la Image original al IPM space
	*/
	Mat map_im2ipm_x, map_im2ipm_y;
	map_im2ipm_x.create(Size(wImage, hImage), CV_32FC1);
	map_im2ipm_y.create(Size(wImage, hImage), CV_32FC1);
	for (int u = 0; u < wImage; ++u){
		double cotStuff = 1.0 / tan(theta - alpha + u*(2.0 * alpha) / (wImage - 1.0));
		for (int v = 0; v < hImage; ++v){
			double otherArg = gamma - alpha + v*(2.0 * alpha) / (hImage - 1.0);
			map_im2ipm_x.at<float>(v, u) = cz*cotStuff*cos(otherArg) + cy;
			map_im2ipm_y.at<float>(v, u) = cz*cotStuff*sin(otherArg) + cx;
		}
	}
	//Obte el valor maxim i mínim de X
	minMaxLoc(map_im2ipm_x, &minValX, &maxValX);

	//Obte el valor maxim i mínim de Y
	minMaxLoc(map_im2ipm_y, &minValY, &maxValY);

	
	minValX = minValX + (maxValX - minValX)*0.1;
	maxValX = maxValX - (maxValX - minValX)*0.1;

	/*
	* General la matriu que mapeja els pixels de la imatge resultant a l'IPM a la imatge original
	*/
	n = original.width / 2;
	m = n;

	map_x.create(Size(n, m), CV_32FC1);
	map_y.create(Size(n, m), CV_32FC1);
	double valX, valY;
	double originalImX, originalImY;
	for (int i = 0; i < n; i++){
		valX = double(i) / n * (maxValX - minValX) + minValX;
		for (int j = 0; j < m; j++){
			valY = double(j) / m * (maxValY - minValY) + minValY;
			PerspectiveMapping(valX, valY, originalImX, originalImY);
			map_x.at<float>(n-1-i, j) = originalImY*wImage;
			map_y.at<float>(n-1-i, j) = originalImX*hImage;
		}
	}
}


IPM::~IPM()
{

}
/**
* Transforma una imatge de la carretera en perspectiva a una amb la vista d'ocell d'aquesta
*/
void IPM::InversePerspectiveMapping(Mat& frame, Mat& output){

	//Transforma a escala de grisos
	Mat gray;
	cvtColor(frame, gray, CV_BGR2GRAY);
	
	//Genera la imatge amb vistes d'ocell
	output.create(gray.size(), gray.type());
	remap(gray, output, map_x, map_y, CV_INTER_LINEAR);

}

/* 
* Funció que aplica l'Inverse Persepctive Mapping dels punts (u,v) i obte (x,y) de l'IPM space
*/
void IPM::InversePerspectiveMapping(double u, double v, double& x, double& y){

	double cotStuff = 1.0 / tan(theta - alpha + u*(2.0 * alpha) / (n - 1.0));
	double otherArg = gamma - alpha + v*(2.0 * alpha) / (n - 1.0);
	x = cz*cotStuff*cos(otherArg) + cy;
	y = cz*cotStuff*sin(otherArg) + cx;

}

/*
* Funció que aplica Persepctive Mapping dels punts (x,y) de l'IPM space i obte (u,v) de la imatge original
*/
void IPM::PerspectiveMapping(double x, double y, double& u, double& v){

	double numeradorX = atan(cz*sin(atan((y - cx) / (x - cy))) / (y - cx)) - (theta - alpha);
	double denominadorX = 2 * alpha;
	u = numeradorX / denominadorX;

	double numeradorY = atan2((y - cx), (x - cy)) - (gamma - alpha);
	double denominadorY = 2 * alpha;
	v = numeradorY / denominadorY;
}

/**
*  Funció que donat un punt en IPM space et retorna el punt en la imatge original.
*/
void IPM::PerspectiveMapping(Point p, Point& p2){
	double x = map_x.at<float>(p.y, p.x);
	double y = map_y.at<float>(p.y, p.x);
	p2 = Point(x, y);
}
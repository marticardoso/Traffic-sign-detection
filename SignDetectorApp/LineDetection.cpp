#include "LineDetection.h"



LineDetection::LineDetection()
{
	//Inicialitza parametres
	method = 2;
	//Kernel central
	centralKernel = cv::getGaussianKernel(3, 3);
	int size = 3;
	cv::Mat gaussianKernel = cv::getGaussianKernel(size, 1);
	cv::mulTransposed(gaussianKernel, gaussianKernel, false);

	//Kernel Left
	vector<Mat> matrices = {
		gaussianKernel,
		Mat(3, 3, CV_64F, Scalar(0)),
		Mat(3, 3, CV_64F, Scalar(0)),

	};
	hconcat(matrices, leftKernel);

	//Kernel Right
	matrices = {
		Mat(3, 3, CV_64F, Scalar(0)),
		Mat(3, 3, CV_64F, Scalar(0)),
		gaussianKernel,

	};
	hconcat(matrices, rightKernel);
	anchorLR = Point(4, 1);
	anchorC = Point(0, 1);
}


LineDetection::~LineDetection()
{
}
/**
 * Funció que detecta la linea vertical dreta
 */
void LineDetection::detectRoadLines(Mat& frame, pair<Point, Point>& v1){
	//Aplica una binarització personalitzada
	Mat output;
	binarizeRoadLines(frame, output);

	Size size = frame.size();

	Mat subIm;
	int hIni = 0;
	int hSize = (size.height - 1);
	subIm = output(cv::Rect(0, hIni, size.width, hSize));

	//Localitza la linea segons el metode realitza
	double posX; 
	double theta = 0;
	if(method==1) localizeRightRoadLine(subIm,posX);
	if(method==2) localizeRightRoadLineHough(subIm, posX, theta);
	v1 = pair<Point, Point>(Point(posX, hIni), Point(posX - hSize*sin(theta), hIni + hSize*cos(theta)));
	
}

/*
* Localitza la linea dreta mitjançant Hough
*/
void LineDetection::localizeRightRoadLineHough(Mat& bIm,double& maxRho, double& maxTheta){

	//Aplica hough lines de la imatge binaritzada
	vector<Vec2f> lines;
	Mat m;
	Canny(bIm, bIm, 0, 30, 3);
	HoughLines(bIm, lines, 1, CV_PI / 180, 100, 0, 0);
	maxRho = -1;
	maxTheta = 0;
	//Troba la linea 'vertical' que està més a la dreta.
	for (size_t i = 0; i < lines.size(); i++)
	{
		int interval = 25;
		
		float rho = lines[i][0], theta = lines[i][1];
		if (rho < 0) {
			rho = -rho;
			theta = CV_PI - theta;
			if(theta < CV_PI / 180 * 5){
				double prov = rho;
				if (prov > maxRho+interval){
					maxRho = prov;
					maxTheta = -theta;
				}
			}

		}
		else{
			if (theta < CV_PI / 180 * 5){
				double prov = rho;
				if (prov > maxRho+interval){
					maxRho = prov;
					maxTheta = theta;
				}
			}
		}
	}
	//Si no troba cap linia utilitza la predefinida
	if (maxRho == -1){
		maxRho = bIm.size().width*0.55;
		maxTheta = 0;
	}
	maxRho = max(bIm.size().width*0.55, maxRho);

}

/*
* Localitza la linea dreta mitjançant la suma de columnes
*/
void LineDetection::localizeRightRoadLine(Mat& bIm, double& maxR){
	//Per cada columna computa la mitja
	Mat some;
	cv::reduce(bIm, some, 0, CV_REDUCE_AVG, CV_32FC1);
		
	double w = some.size().width;
	bool trobat = false;

	//Busca la primera columna dreta que sobrepassa el threshold
	double threshold = 255 * 0.35;
	for (int i = w - 1; !trobat && i >= w/2; i--){
		if (some.at<float>(0,i) > threshold){
			maxR = i;

			return;
		}
	}

	//Si no troba cap linia utilitza la predefinida
	maxR = some.size().width*0.55;

}
/**
* Binaritza la imatge per tal de potenciar els pixels de la linea de la carretera
*/
void LineDetection::binarizeRoadLines(Mat& frame, Mat& output){
	//Es nega els pixels
	Mat negFrame = 256 - frame;

	//S'aplica un filtre als dos costats ('intencio': trobar les regions que tenen els dos costats negres')
	Mat filtC, filtR, filtL;
	cv::filter2D(negFrame, filtL, -1, leftKernel, anchorLR, 0, BORDER_REPLICATE);
	cv::filter2D(negFrame, filtR, -1, rightKernel, anchorLR, 0, BORDER_REPLICATE);

	//Fa la mitja entre els dos filtres i penalitza si son diferents
	output = (filtL + filtR) / 2 - abs(filtL - filtR);

	//Filtre que aplica una gausiana amb alpha a leix y.
	cv::filter2D(frame, filtC, -1, centralKernel, anchorC, 0, BORDER_REPLICATE);

	//Fa el producte per tal d'obtenir les regions que tenen zones blanques i costats foscos 'semblants'
	output = output.mul(filtC / 256);

	//Aplica un threshold a la imatge resultant
	double minValX, maxValX;
	minMaxLoc(output, &minValX, &maxValX);

	double thVal = maxValX*0.8;
	thVal = 70;
	cv::threshold(output, output, thVal, 255, CV_THRESH_BINARY);

}
/**
 * Selecciona el mètode a utilitzar: 
 *   - 1: Histograma
 *   - 2: Hough
 */
void LineDetection::setMethod(int m){
	if (m==1 ||m==2) 
		method = m;
}

#include "ComputeROI.h"
#include <time.h> 

ComputeROI::ComputeROI()
{
	method = 1;
}

ComputeROI::ComputeROI(Mat& ini)
{
	
	method = 3;
	
	//Inicialize all clases needed by ComputeROI
	r2r = reduce2Road(ini.size());

	Mat ini2;
	r2r.getRoadImage(ini, ini2);

	ipm = IPM(ini2.size());

	lDet = LineDetection();
	lDet.setMethod(method-2);
	r2ROI = Reduce2ROI(ini.size());
}


ComputeROI::~ComputeROI()
{
}

/**
 * Calcula la regió d'interès d'un frame
 */
void ComputeROI::compute(Mat& frame, Mat&ImROI,Rect& r){
	//Cas no IPM
	if (method == 1||method==2){
		ImROI = frame.clone();
		Size s = frame.size();
		if (method == 2){
			double fX = 1.0 / 2.0;
			double topY = 1.0 / 4.0;
			double botY = 3.0 / 4.0;
			r = cv::Rect(fX*s.width, topY * s.height, (1.0 - fX)*s.width, (botY - topY)*s.height);
			ImROI = ImROI(r);
		}
		else{
			r = cv::Rect(0, 0, s.width, s.height);
		}
		rectangle(frame, r, Scalar(0, 0, 255),2);
	}
	//Cas IPM
	else if (method == 3 || method == 4){
		//Obte la carretera
		Mat roadFrame;
		r2r.getRoadImage(frame, roadFrame);

		//Transforma la carretera a l'espai IPM
		Mat IPMFrame;
		ipm.InversePerspectiveMapping(roadFrame, IPMFrame);

		//Troba la linea dreta de la carretera
		
		pair<Point, Point> points;
		lDet.detectRoadLines(IPMFrame, points);
		
		Point pIni = points.first;
		Point pFi = points.second;
		//Torna de IPM a imatge de la carretera
		Point pIni2, pFi2;
		ipm.PerspectiveMapping(pIni, pIni2);
		ipm.PerspectiveMapping(pFi, pFi2);

		//Dibuixa una linea
		Scalar col(0, 255, 0);
		line(roadFrame, pIni2, pFi2, col);
		line(IPMFrame, pIni, pFi, col);

		Point pIni3, pFi3;
		r2r.getOriginPosition(pIni2, pIni3);
		r2r.getOriginPosition(pFi2, pFi3);

		//line(frame, pIni3, pFi3, col);

		//Obte la ROI
		r2ROI.Reduce(frame, ImROI, r, pIni3, pFi3);
		

	}

}


/**
*  Method num:
*		1- All image is ROI;
*       2- Subregion is ROI;
*       3- Line Detection with histogram
*       4- Line Detection with Hough
*/
void ComputeROI::setMethod(int m){
	if (method <= 4 && method > 0){
		method = m;
		if (method>2)
			lDet.setMethod(method - 2);
	}
}
/**
*  Obte el metode actual
*/
int ComputeROI::getMethod(){
	return method;
}
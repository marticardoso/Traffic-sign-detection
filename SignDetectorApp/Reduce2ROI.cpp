#include "Reduce2ROI.h"

Reduce2ROI::Reduce2ROI()
{
	limitX = 0;
}

Reduce2ROI::Reduce2ROI(Size& size)
{
	//Limit dret de x de la imatge
	limitX = size.width / 3;
}


Reduce2ROI::~Reduce2ROI()
{
}
/**
* Funció que donada una imatge i un punt ini i un punt fi
* Retalla la imatge per tal de que la linea que passa per ini i fi aparegui a ella
* i retorna el rect utilitzat
*/
void Reduce2ROI::Reduce(Mat& im, Mat& output, Rect& r, Point& ini, Point& fi){
	//Considerem sempre que fi te x major
	fi.y = min(fi.y, im.rows);
	fi.x = min(fi.x, im.cols);
	if (fi.x < ini.x) {
		Point p = fi;
		fi = ini;
		ini = p;
	}
	//Calcula la intersecció amb el contorn de la imatge
	double posX = limitX;
	double slope = double(fi.x - ini.x) / (fi.y - ini.y);
	double posY = fi.y - double(fi.x - posX) / slope;
	if (posY < 0){
		posY = 0;
		posX = fi.x - slope* (fi.y - posY);
	}


	/** Elimina la regió inferior a la linea */
	Point rook_points[1][3];
	rook_points[0][0] = fi;
	rook_points[0][1] = Point(posX, posY);
	rook_points[0][2] = Point(posX, fi.y);

	const Point* ppt[1] = { rook_points[0] };
	int npt[] = { 3 };
	output = im.clone();
	fillPoly(output, ppt, npt, 1, Scalar(0, 0, 0), 8);


	r = cv::Rect(posX, 0, output.size().width - posX, fi.y);
	output = output(r);
	
	//Dibuixa la ROI al frame
	bool plotLine = true;
	if (plotLine){
		Point rook_points2[1][6];
		rook_points2[0][0] = Point(posX, posY);
		rook_points2[0][1] = fi;

		if (fi.x < im.cols - 1)
			rook_points2[0][2] = Point(im.cols - 2, fi.y);
		else
			rook_points2[0][2] = fi;

		rook_points2[0][3] = Point(im.cols - 2, 1);
		int sX = im.cols;
		int sY = im.rows;
		rook_points2[0][4] = Point(posX, 1);
		rook_points2[0][5] = Point(posX, posY);
		const Point* ppt2[1] = { rook_points2[0] };
		int npt2[] = { 1};
		for (int i = 0; i < 5;++i)
			line(im, rook_points2[0][i], rook_points2[0][i+1], Scalar(0, 0, 255));
		line(im, rook_points2[0][5], rook_points2[0][0], Scalar(0, 0, 255));
	}
}
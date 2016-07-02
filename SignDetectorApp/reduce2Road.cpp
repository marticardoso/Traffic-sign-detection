#include "reduce2Road.h"
reduce2Road::reduce2Road()
{

}


reduce2Road::reduce2Road(const Size& size)
{
	//Inicialitza els parametres segons la mida que tingui la imatge
	wIni = 0;
	wSize = size.width;
	hIni = size.height * 3 / 4;
	hSize = (size.height - hIni) * 5 / 5;
}


reduce2Road::~reduce2Road()
{
}

/**
* Obté la imatge corresponent a la carretera de input
*/
void reduce2Road::getRoadImage(const Mat& input, Mat& output){
	output = input(cv::Rect(wIni, hIni, wSize, hSize));
}

/*
 * Donat un punt de la carretera et retorna el punt corresponent al frame
 */
void reduce2Road::getOriginPosition(Point& p1, Point& output){
	double x = wIni + p1.x;
	double y = hIni + p1.y; 
	output = Point(x, y);
}
#include "SignDetector.h"



SignDetector::SignDetector()
{
	showIm = true;
	if (showIm) namedWindow("DetectFrame1", 6);
}


SignDetector::~SignDetector()
{
}

/**
* Funció que detecta els senyals de la imatge input
*/
void SignDetector::detect(Mat& input, vector<vector<Point>>& detectedContourns, vector<Rect>& boundingBoxes, vector<int>& color){

	//Passa a l'espai HLS
	Mat HLSP;
	cvtColor(input, HLSP, CV_BGR2HLS);

	//Red range
	cv::Mat lower_red_hue_range;
	cv::Mat upper_red_hue_range;
	cv::inRange(HLSP, cv::Scalar(0, 30, 40), cv::Scalar(15, 120, 255), lower_red_hue_range);
	cv::inRange(HLSP, cv::Scalar(165, 30, 40), cv::Scalar(180, 120, 255), upper_red_hue_range);
	Mat redRange = upper_red_hue_range + lower_red_hue_range;
	

	//Blue range
	Mat blue_range;
	cv::inRange(HLSP, cv::Scalar(100, 20, 50), cv::Scalar(130, 150, 255), blue_range);


	//Aplica un tancament morphologic
	Mat SE = getStructuringElement(MORPH_ELLIPSE, Size(height / 80, height / 80));
	dilate(redRange, redRange, SE);
	erode(redRange, redRange, SE);
	SE = getStructuringElement(MORPH_ELLIPSE, Size(height / 50, height / 50));
	dilate(blue_range, blue_range, SE);
	erode(blue_range, blue_range, SE);

	//Detecta els contorns i bounding boxes que podrien ser senyals
	detectedContourns = vector<vector<Point> >(0);
	boundingBoxes = vector<Rect>(0);
	findContourns(redRange, detectedContourns, boundingBoxes);
	int sizeRed = detectedContourns.size();
	findContourns(blue_range, detectedContourns, boundingBoxes);

	//Actualitza el color de cada contorn ( 0-> vermell, 1->blau)
	color = vector<int>(detectedContourns.size(),0);
	for (int i = sizeRed; i < color.size(); ++i)
		color[i] = 1;
	

	//Dibuixa els contorns a la binarització
	if(showIm){
		Mat drawing = redRange + blue_range;
		cvtColor(drawing, drawing, CV_GRAY2RGB);
		RNG rng(12345);
		for (int i = 0; i< detectedContourns.size(); i++)
		{
			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			vector<Vec4i> hierarchy;
			drawContours(drawing, detectedContourns, i, color, 2, 8, hierarchy, 0, Point());
		}

		imshow("DetectFrame1", drawing);
	}
}


/**
* Troba els possibles senyals de input
*/
void SignDetector::findContourns(Mat& input, vector<vector<Point> >& contours2, vector<Rect>& boundingBox){

	//Crida a findCountours de opencv
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Mat inputC = input.clone();
	findContours(inputC, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	//Per cada possible contorn:
	for (int i = 0; i< contours.size(); i++)
	{
		//Area
		double area = contourArea(Mat(contours[i]));
		//BB
		Rect r = boundingRect(Mat(contours[i]));
		//Area convex hull
		vector<Point> convex;
		convexHull(Mat(contours[i]), convex);
		double aConvex = contourArea(Mat(convex));

		double solidity = area / aConvex;
		double ratio = double(r.height) / r.width;

		//Si compleixen les 5 condicions pot ser un senyal
		bool cond1 = ratio<1.3 && ratio>0.7;
		bool cond2 = r.area() > double(height)*0.025*double(width)*0.025 || true;
		bool cond3 = solidity > 0.8;
		bool cond4 = r.height >= double(min(height,width))*0.05;
		bool cond5 = r.width >= double(min(height, width))*0.05;

		if (cond1 && cond2 && cond3 && cond4 &&cond5){
			contours2.push_back(contours[i]);
			boundingBox.push_back(r);
		}


		bool apilado = ratio<2.3 && ratio>1.6 && cond2 && cond4 && cond5;

		//Cas pot ser un apilament de dos senyals
		if (apilado){

			Mat subIm = input(r).clone();

			//Troba la linea que separa els dos senyals
			Point iniP;
			Point fiP;
			findDivisor(contours[i], r, iniP, fiP);
			line(subIm, iniP, fiP, Scalar(0, 0, 0), 1, 4);

			//Troba els contorns de la nova imatge
			vector<vector<Point> > apCont;
			findContours(subIm, apCont, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);


			for (int j = 0; j < apCont.size(); j++)
			{
				

				//Area
				double area = contourArea(Mat(apCont[j]));

				//BB
				Rect r2 = boundingRect(Mat(apCont[j]));

				//Area convex hull
				vector<Point> convex;
				convexHull(Mat(apCont[j]), convex);
				double aConvex = contourArea(Mat(convex));

				double solidity = area / aConvex;
				double ratio = double(r2.height) / r2.width;

				bool cond1 = ratio<1.3 && ratio>0.7;
				bool cond2 = r2.area() > double(height)*0.025*double(width)*0.025 || true;
				bool cond3 = solidity > 0.8;
				bool cond4 = r2.height >= double(min(height,width))*0.05;
				bool cond5 = r2.width >= double(min(height, width))*0.05;

				r2.x += r.x;
				r2.y += r.y;
				for (int k = 0; k < apCont[j].size(); ++k){
					apCont[j][k].x += r.x;
					apCont[j][k].y += r.y;
				}
				//Si compleix les 5 condicions pot ser un senyal
				if (cond1 && cond2 && cond3 && cond4 &&cond5){
					contours2.push_back(apCont[j]);
					boundingBox.push_back(r2);
				}
			}


		}

	}
}

/*
* Si dues senyals estan apilades, troba el divisor horitzontal entre elles.
*/
void SignDetector::findDivisor(vector<Point>& vec, Rect& r, Point& xLmax, Point& xRmin){

	xLmax = Point(r.x, r.y + r.height / 2);
	xRmin = Point(r.x + r.width - 1, r.y + r.height / 2);

	int contaL = 0;
	int contaR = 0;

	bool contiguoL = true;
	bool contiguoR = true;

	Point ix = Point(0, r.height / 2);
	Point ix23 = Point(r.width - 1, r.height / 2);

	int topY = r.y + r.height / 3.0*2.0;
	int botY = r.y + r.height / 3.0;

	for (int i = 0; i < vec.size(); ++i){
		if (vec[i].y < topY && vec[i].y >= botY){
			if (vec[i].x > r.x + r.width / 2){
				if (vec[i].x < xRmin.x){
					xRmin = vec[i];
					contaR = 0;
					contiguoR = true;
				}
				else if (contiguoR && vec[i].x == xRmin.x){
					++contaR;
				}
				else{
					contiguoR = false;
				}
			}
			else if (vec[i].x < r.x + r.width / 2){
				if (vec[i].x>xLmax.x){
					xLmax = vec[i];
					contaL = 0;
					contiguoL = true;
				}
				if (contiguoL && vec[i].x == xRmin.x){
					++contaL;
				}
				else{
					contiguoL = false;
				}
			}
		}
	}

	if (contaR > 0){
		xRmin.y -= contaR / 2;
	}
	if (contaL > 0){
		xLmax.y += contaL / 2;
	}

	bool t = true;
	if (xLmax.y >= topY - 1 || xLmax.y <= botY + 1) {
		t = false;
	}
	if (xRmin.y >= topY - 1 || xRmin.y <= botY + 1) {
		t = false;
	}

	if (!t){
		xLmax = Point(r.x, r.y + r.height / 2);
		xRmin = Point(r.x + r.width - 1, r.y + r.height / 2);
	}

	xRmin.x -= r.x;
	xLmax.x -= r.x;
	xRmin.y -= r.y;
	xLmax.y -= r.y;
}


/**
* Estableix la mida el frame
*/
void SignDetector::setSizeFrame(int h, int w){
	height = h;
	width = w;
}

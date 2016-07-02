#ifndef FEATURESFINDER_H
#define FEATURESFINDER_H
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
class FeaturesFinder
{
public:
	FeaturesFinder();
	~FeaturesFinder();
	//Obte caracterisitques de HOG
	static void getHOGFeature(Mat& m, vector<float> & descriptors);
	//Obte caracteristiques de la slope Density Function
	static void getSlopeDens(vector<Point>& m, vector<float>& descriptors,int k);
	//Obté la mida del vector de HOG
	static int getNumAttributes();
private:

	static Mat get_hogdescriptor_visual_image(Mat& origImg,
		vector<float>& descriptorValues,
		Size winSize,
		Size cellSize,
		int scaleFactor,
		double viz_factor);
};

#endif
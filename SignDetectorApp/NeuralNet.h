#ifndef NEURALNET_H
#define NEURALNET_H
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
class NeuralNet
{
public:
	NeuralNet();
	~NeuralNet();
	//Entrena la xarxa neuronal
	void train(Mat& trainData, Mat& trainLabels,int nIn, int nOut);
	//Realitza la predicció de la xarxa
	void predict(Mat& sample, Mat& response);
	//Estableix el nombre de capes ocultes
	void setNumLayers(int l);
	//Estableix el numero de neurones de les capes ocultes
	void setNumNeurons(int n);
	//Estableix el maxim d'iteracions de l'entrenament
	void setMaxIt(float mI);
	//Estableix el parametre epsilon de l'entrenament
	void setEpsilon(float e);
	//Estableix els parametres d'entrenament
	void setTrainParameters(float p1, float p2);
	//Estableix els parametres de la sigmoide
	void setSigmoideParams(float p1, float a);
private:
	//Xarxa neuronal
	CvANN_MLP mlp;
	//Parametres per defecta de la xarxa
	CvANN_MLP_TrainParams params;
	int numLayers = 1;
	int numNeurons = 70;
	float maxIt = 10;
	float epsilon = 0.00001f;
	float dw_scale = 0.1f;
	float moment_scale = 0.1f;
	float b = 0.6;
	float alpha = 1;
	
};

#endif
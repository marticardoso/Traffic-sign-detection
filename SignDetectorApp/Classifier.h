#ifndef CLASSIFIER_H
#define CLASSIFIER_H


#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "TrainingData.h"
#include "NeuralNet.h"
using namespace cv;
using namespace std;
class Classifier
{
public:
	Classifier();
	~Classifier();
	
	//Classifica un conjunt de regions de im en senyals de la base de dades
	void classify(Mat& im, vector<Rect>& BB, vector<vector<Point> >& contourn, vector<int>& color, vector<pair<pair<Rect, Mat>, double> >& result);
	//Establir nou directori de base de dades
	void setNewDirectory(String dir);
	//Genera de nou totes les xarxes neuronals
	void newNet();

private:
	//Una base de dades per cada tipus de senyal
	vector<TrainingData*> dataset = vector<TrainingData*>(4, NULL);
	//Una xarxa neuronal per cada tipus de senyal
	vector<NeuralNet*> net = vector<NeuralNet*>(5, NULL);

	//Directori de la base de dades
	String defaultPath = "E:\\dataset\\";

	//Retorna el nom de la carpeta on hi ha el tipus de senyal i
	String getStringSign(int i);
	//Obte la forma del contorn d'una regió
	int getForm(vector<Point>& contourn,int color);
	//Classifica els diferents senyals segons el tipus de forma
	void divide(vector<Rect>& BB, vector<vector<Point> >& contourn, vector<int>& color, vector<vector<Rect> >& BBO, vector<vector<vector<Point> > >& contournO);
	//Retorna cert si el contorn és semblant a un cercle i fals altrament.
	bool isCircle(vector<Point>& p);

	//Caracteristiques per defecte de les xarxes
	vector<int> numNeurons; 
	vector<double> alphaVec;
	vector<double> bettaVec;

		
};




#endif 


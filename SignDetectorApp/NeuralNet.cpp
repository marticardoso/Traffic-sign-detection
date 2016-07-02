#include "NeuralNet.h"
#include "FeaturesFinder.h"


NeuralNet::NeuralNet()
{

}


NeuralNet::~NeuralNet()
{
}

/**
* Entrena la xarxa neuronal amb les dades que s'entren. 
*/
void NeuralNet::train(Mat& trainData, Mat& trainLabels, int nInputs, int nOutputs){
	
	
	//Genera una nova xarxa
	mlp = CvANN_MLP();

	//Estableix els parametres de la xarxa
	//Parametres d'entrenament
	CvTermCriteria criteria;
	criteria.max_iter = maxIt;
	criteria.epsilon = epsilon;
	criteria.type = CV_TERMCRIT_ITER | CV_TERMCRIT_EPS;

	params = CvANN_MLP_TrainParams();
	params.train_method = CvANN_MLP_TrainParams::BACKPROP;
	params.bp_dw_scale = dw_scale;
	params.bp_moment_scale = moment_scale;
	params.term_crit = criteria;

	//Estructura de la xarxa
	Mat layers = Mat(1, numLayers + 2, CV_32SC1);
	layers.at<int>(0, 0) = nInputs;
	for (int i = 1; i <= numLayers; ++i){
		layers.at<int>(0, i) = numNeurons;
	}
	layers.at<int>(0, numLayers + 1) = nOutputs;

	//Crea la xarxa amb els parametres establerts
	mlp.create(layers, CvANN_MLP::SIGMOID_SYM, alpha, b);

	//Entrena la xarxa amb les dades d'entrada
	int x = mlp.train(trainData, trainLabels, Mat(), Mat(), params);

}
/**
* Obte la resposta que dona la xarxa a una entrada (predicció)
*/
void NeuralNet::predict(Mat& sample, Mat& response){
	mlp.predict(sample, response);
}
/**
* Estableix el nombre de capes ocultes
*/
void NeuralNet::setNumLayers(int l){
	numLayers = l;
}
/**
* Estableix el numero de neurones de les capes ocultes
*/
void NeuralNet::setNumNeurons(int n){
	numNeurons = n;
}
/**
* Estableix el maxim d'iteracions de l'entrenament
*/
void NeuralNet::setMaxIt(float mI){
	maxIt = mI;
}
/**
* Estableix el parametre epsilon de l'entrenament
*/
void NeuralNet::setEpsilon(float e){
	epsilon = e;
}
/**
* Estableix els parametres d'entrenament
*/
void NeuralNet::setTrainParameters(float dw, float moment){
	dw_scale = dw;
	moment_scale = moment;
}

/**
* Estableix els parametres de la sigmoide
*/
void NeuralNet::setSigmoideParams(float a, float p1){
	b = p1;
	alpha = a;
}
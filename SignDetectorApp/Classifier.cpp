#include "Classifier.h"
#include "FeaturesFinder.h"
using namespace std;

Classifier::Classifier()
{
	//Inicialitza els parametres de les diferents xarxes neuronals
	numNeurons = vector<int>(4);
	numNeurons[0] = 45;	numNeurons[1] = 35;
	numNeurons[2] = 25;	numNeurons[3] = 35;

	alphaVec = vector<double>(4);
	alphaVec[0] = 0.5;
	alphaVec[1] = 0.9;
	alphaVec[2] = 0.6;
	alphaVec[3] = 0.6;

	bettaVec = vector<double>(4);
	bettaVec[0] = 1.0;
	bettaVec[1] = 1.0;
	bettaVec[2] = 1.3;
	bettaVec[3] = 1.0;

}


Classifier::~Classifier()
{
}



/**
* Establir nou directori de base de dades
*/
void Classifier::setNewDirectory(String dir){
	//Crea cada xarxa amb la nova base de dades.
	for (int i = 0; i < dataset.size(); ++i){
		dataset[i] = new TrainingData();
		dataset[i]->setDirectory(dir + getStringSign(i));
		dataset[i]->OpenFiles();

		//Obté vectors de caracteristiques i target
		Mat targets;
		dataset[i]->getTarget(targets);
		Mat features;
		dataset[i]->getFeaturesVector(features);

		//Crea xarxa neuronal corresponent
		net[i] = new NeuralNet();
		net[i]->setNumNeurons(numNeurons[i]);
		net[i]->setNumLayers(1);
		net[i]->setSigmoideParams(alphaVec[i], bettaVec[i]);
		net[i]->setEpsilon(0.001);
		net[i]->setMaxIt(100);

		//Entrena la xarxa amb la base de dades
		int nOut = dataset[i]->getNumClasses();
		int nIn = features.cols;
		net[i]->train(features, targets, nIn, nOut);
	}
}

/**
* Classifica un conjunt de regions de im en senyals de la base de dades
*/
void Classifier::classify(Mat& im, vector<Rect>& BB, vector<vector<Point> >& contourn, vector<int>& color, vector<pair<pair<Rect, Mat>, double> >& result){
	assert(BB.size() == contourn.size());

	//Si no existeix la base de dades, la crea
	if (dataset[0] == NULL){
		setNewDirectory(defaultPath);
	}

	//Classifica les deteccions segons la forma
	vector<vector<Rect> > BBO;
	vector<vector<vector<Point> > > contournO;
	divide(BB, contourn, color, BBO, contournO);

	//Per cada tipus realitza una classificació a la seva xarxa
	for (int signType = 0; signType < contournO.size(); ++signType){

		if (contournO[signType].size() > 0){
			
			//Genera el vector de caracterisitques de tots els senyals
			int nSigns = BBO[signType].size();
			int nFeat = FeaturesFinder::getNumAttributes();

			Mat features(nSigns, nFeat, CV_32F, Scalar(0));

			vector<float> feat;
			for (int i = 0; i < nSigns; ++i){
				FeaturesFinder::getHOGFeature(im(BBO[signType][i]), feat);
				for (int j = 0; j < feat.size(); ++j)
					features.at<float>(i, j) = feat[j];
			}

			//Realitza la predicció
			Mat answer;
			net[signType]->predict(features, answer);

			//Computa el resultat més alt de la xarxa i es posa a resultats
			double min, max;
			Point min_loc, max_loc;
			for (int i = 0; i < answer.rows; ++i){
				minMaxLoc(answer.row(i), &min, &max, &min_loc, &max_loc);

				if (!dataset[signType]->isRejectClass(max_loc.x)){
					Mat imMax;
					dataset[signType]->getImage(max_loc.x, imMax);

					pair<Rect,Mat> p;
					p.second = imMax;
					p.first = BBO[signType][i];
					
					result.push_back(pair<pair<Rect,Mat> , double>(p, max));
				}
			}

		}
	}


}

/**
* Genera de nou totes les xarxes neuronals
*/
void Classifier::newNet(){
	for (int i = 0; i < dataset.size(); ++i){
		//Si no existeix la base de dades la crea
		if (dataset[i] == NULL){
			dataset[i] = new TrainingData();
			dataset[i]->setDirectory(defaultPath + getStringSign(i));
			dataset[i]->OpenFiles();
		}
		//Obté vectors de caracteristiques i target
		Mat targets;
		dataset[i]->getTarget(targets);
		Mat features;
		dataset[i]->getFeaturesVector(features);

		//Crea xarxa neuronal corresponent
		net[i] = new NeuralNet();
		net[i]->setNumNeurons(numNeurons[i]);
		net[i]->setNumLayers(1);
		net[i]->setSigmoideParams(alphaVec[i], bettaVec[i]);
		net[i]->setEpsilon(0.001);
		net[i]->setMaxIt(100);

		//Entrena la xarxa amb la base de dades
		int nOut = dataset[i]->getNumClasses();
		int nIn = features.cols;
		net[i]->train(features, targets, nIn, nOut);
	}
}


/**
* Retorna el nom de la carpeta on hi ha el tipus de senyal i
*/
String Classifier::getStringSign(int i){
	if (i == 0) return "RedCircle\\";
	if (i == 1) return "RedTriangle\\";
	if (i == 2) return "BlueCircle\\";
	if (i == 3) return "BlueQuad\\";
}

/**
* Classifica els diferents senyals segons el tipus de forma
*/
void Classifier::divide(vector<Rect>& BB, vector<vector<Point> >& contourn, vector<int>& color, vector<vector<Rect> >& BBO, vector<vector<vector<Point> > >& contournO){
	BBO = vector<vector<Rect> >(4, vector<Rect>(0));
	contournO = vector<vector<vector<Point> > >(4, vector<vector<Point> >(0));
	
	for (int i = 0; i < BB.size();++i){
		
		int form = getForm(contourn[i],color[i]);

		BBO[form].push_back(BB[i]);
		contournO[form].push_back(contourn[i]);
	}
}
/**
* Obte la forma del contorn d'una regió
*/
int Classifier::getForm(vector<Point>& contourn, int color){
	bool b = isCircle(contourn);
	//Senyal vermell
	if (color == 0){
		if (b) 	return 0;
		else   	return 1;
	}
	//Senyal blau
	if (color == 1){
		if (b) 	return 2;
		else   	return 3;
	}
	return 0;
}

/**
* Retorna cert si el contorn és semblant a un cercle i fals altrament.
*/
bool Classifier::isCircle(vector<Point>& p){
	vector<float> descriptor;
	int k = descriptor.size() / 30;
	if (k < 1) k = 1;
	FeaturesFinder::getSlopeDens(p, descriptor, k);
	Scalar mean, stddev;
	meanStdDev(descriptor, mean, stddev);
	return stddev[0]<0.060;
}
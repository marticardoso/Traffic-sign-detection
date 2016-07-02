#include "TrainingData.h"
#include "FeaturesFinder.h"
#include "SignDetector.h"
#include <Windows.h>
#include <fstream>
#include <iostream>


TrainingData::TrainingData()
{
	directory = "";
}


TrainingData::~TrainingData()
{
}

/**
* Estableix el directori de la base de dades
*/
void TrainingData::setDirectory(String dir){
	directory = dir; //THIS
}

/**
* Obrir els fitxers de la base de dades
*/
void TrainingData::OpenFiles(){
	if (!dirExists(directory)) return;
	if (directory != ""){
		differentsFileName = vector<pair<String,Mat> >(0);

		vector<cv::String> fn;
		String prov = directory + "*.jpg";

		glob(directory, fn, false);

		size_t count = fn.size(); //number of png files in images folder
		for (size_t i = 0; i < count; i++){

			Mat im = imread(fn[i]);
			
			vector<float> feat;
			FeaturesFinder::getHOGFeature(im, feat);

			features.push_back(feat);

			String name = getFileName(fn[i]);
			int t = getTargetValue(name, im);
			target.push_back(t);

			//Aplica diferents filtres a la imatge (avatars)
			vector<Mat> vecIm;
			applyDifferentsFilters(im, vecIm);
			for (int i = 0; i < vecIm.size(); ++i){
				Mat imFilt = vecIm[i];
				FeaturesFinder::getHOGFeature(imFilt, feat);
				features.push_back(feat);
				target.push_back(t);
			}

			//Si existeix un directori amb el nom del senyal-> computar els fitxers interns

			String folder = directory + name + "//";
			checkInsideFolderData(folder,t);

		}
	}

}
/**
*  Obté el nom del fitxer de la path
*/
String TrainingData::getFileName(String path){
	int i = path.size();
	String nameFile = "";
	bool trobat = false; 
	//Erase the path and get the name file only
	while (i >= 0 && !trobat){
		if (path[i] == '\\'){
			nameFile = path.substr(i + 1, path.size() - i - 1);
			trobat = true;
		}
		--i;
	}
	//Erase .jpg and the behind of '-' and '_'
	for (int j = 0; j < nameFile.size(); ++j){
		if (nameFile[j] == '.' || nameFile[j] == '-' || nameFile[j] == '_')
			return nameFile.substr(0, j);
	}
	
	return nameFile;
}

/**
* Retorna el valor tarjet d'una imatge (si no existeix el crea)
*/
int TrainingData::getTargetValue(String name,Mat im){
	for (int i = 0; i < differentsFileName.size(); ++i){
		if (differentsFileName[i].first == name) return i;
	}
	differentsFileName.push_back(pair<String,Mat>(name,im));
	return differentsFileName.size() - 1;	
}
/**
* Obte el vector de caracteristiques
*/
void TrainingData::getFeaturesVector(Mat& feat){
	int h = features.size();
	int w = 0;
	
	if (h>0) w = features[0].size();
	feat = Mat(h, w, CV_32F, Scalar(0));
	for (int i = 0; i < h; ++i){
		for (int j = 0; j < w; ++j){
			feat.at<float>(i,j) = features[i][j];
		}
	}
}

/**
* Obte el vector de tarjets
*/
void TrainingData::getTarget(Mat& t){

	t = Mat(getNumFiles(), getNumClasses(), CV_32F, Scalar(0));
	
	for (int i = 0; i < target.size(); ++i){
		t.at<float>(i, target[i]) = 1;
	}
}


/**
* Obte el numero de fitxers de la base de dades
*/ 
int TrainingData::getNumFiles(){
	return target.size();
};
/**
* Obte el numero de senyals diferents que hi ha
*/
int TrainingData::getNumClasses(){
	return differentsFileName.size();
}


/**
* Obte la imatge amb tarjet i
*/
void TrainingData::getImage(int i,Mat& im){
	im = differentsFileName[i].second;
}

/**
* Retorna cert si es la classe de rebuig 
*/
bool TrainingData::isRejectClass(int i){
	return differentsFileName[i].first == "xxx";
}

/**
* Aplica diferents filtres a una imatge
*/
void TrainingData::applyDifferentsFilters(Mat& im, vector<Mat>& filt){
	filt = vector<Mat>(0);
	double MAX_KERNEL_LENGTH = im.size().height*1.0/20.0;
	for (int i = 0; i < 2; ++i)
	{
		int kerI = MAX_KERNEL_LENGTH*(1.0 + i) / 2.0;
		for (int j = 0; j < 2; j++){
			Mat blurIm;
			int kerJ = MAX_KERNEL_LENGTH*(1.0 + i) / 2.0;
			blur(im, blurIm, Size(kerI, kerJ), Point(-1, -1));
			filt.push_back(blurIm);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		int kerI = MAX_KERNEL_LENGTH*(1.0 + i) / 2.0;
		if (kerI % 2 == 0) ++kerI;
		for (int j = 0; j < 2; j++){
			Mat Gaus;
			int kerJ = MAX_KERNEL_LENGTH*(1.0 + j) / 2.0;
			if (kerJ % 2 == 0) ++kerJ;
			GaussianBlur(im, Gaus, Size(kerI, kerJ), kerI / 4.0, kerJ / 4.0);
			filt.push_back(Gaus);
		}
	}

}
/**
* Si a dins de dirName hi ha imatges, les computa com a tarjet t.
*/
void TrainingData::checkInsideFolderData(String dirName,int t){
	if (!dirExists(dirName)) return;
	
	vector<cv::String> fn;
	String prov = dirName + "*.jpg";
	glob(prov, fn, false);

	size_t count = fn.size(); //number of jpg files in images folder
	for (size_t i = 0; i < count; i++){
		Mat im = imread(fn[i]);
		
		vector<float> feat;
		FeaturesFinder::getHOGFeature(im, feat);

		features.push_back(feat);
		target.push_back(t);
	}
}

/**
* Indica si el fitxer existeix
*/
bool TrainingData::dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}




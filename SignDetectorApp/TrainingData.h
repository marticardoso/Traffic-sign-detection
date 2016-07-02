#ifndef TRAININGDATA_H
#define TRAININGDATA_H
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
class TrainingData
{
public:
	TrainingData();
	~TrainingData();
	//Obrir els fitxers de la base de dades
	void OpenFiles();
	//Estableix el directori de la base de dades
	void setDirectory(String dir);
	//Obte el vector de tarjets
	void getTarget(Mat& targets);
	//Obte el vector de caracteristiques
	void getFeaturesVector(Mat& feat);
	//Obte el numero de fitxers de la base de dades
	int getNumFiles();
	//Obte el numero de senyals diferents que hi ha
	int getNumClasses();
	//Obte la imatge amb tarjet i
	void getImage(int i, Mat& im);
	//Retorna cert si es la classe de rebuig 
	bool isRejectClass(int i);

private:
	//directory de la base de dades
	String directory;
	//vector de parell senyal-avatar diferents
	vector<pair<String, Mat> > differentsFileName;
	//Vector de caracteristiques
	vector<vector<float> > features;
	//Vector de caracteristiques
	vector<int> target;


	//Obté el nom del fitxer de la path
	static String getFileName(String p);
	//Retorna el valor tarjet d'una imatge (si no existeix el crea)
	int getTargetValue(String name,Mat im);
	//Aplica diferents filtres a una imatge
	static void applyDifferentsFilters(Mat& im, vector<Mat>& filt);
	//Indica si el fitxer existeix
	bool dirExists(const std::string& dirName_in);
	//Si a dins de dirName hi ha imatges, les computa com a tarjet t.
	void checkInsideFolderData(String dirName, int t);
};
#endif

#include "MainClass.h"


MainClass::MainClass()
{
}


MainClass::~MainClass()
{
}

/**
* Executa el detector amb el video del path
*/
void MainClass::visualitzaVideo(String v){
	//Obre el video
	VideoCapture cap(v); 
	if (!cap.isOpened()){  // check if we succeeded
		if (terminal != NULL)
			terminal->setText2("No s'ha pogut obrir el fitxer");
		return;
	}

	//Llegeix el primer frame;
	Mat ini;
	cap >> ini;
	//Si supera 720 d'amplada s'aplica un resize;
	if (ini.size().width>720)
		resize(ini, ini, Size(720, 720 * ini.size().height / ini.size().width));
	
	//Crea la classe que genera la ROI
	int method = cROI.getMethod();
	cROI = ComputeROI(ini);
	cROI.setMethod(method);

	//Actualitza el tamany del frame del detector de senyals.
	signDet.setSizeFrame(ini.size().height, ini.size().width);

	
	isRunning = true;

	for (numFrames = 0, clocIni = clock(); isRunning; numFrames++)
	{
		//Llegeix el seguent frame
		Mat frame;
		cap >> frame;
		if (frame.empty())	return;
		cap >> frame;
		if (frame.empty())	return;
		//Si te mida major a 720 en x aplicar resize
		if (frame.size().width>720)
			resize(frame, frame, Size(720, 720 * frame.size().height / frame.size().width));
		//Tract el frame
		tractarFrame(frame);
		
		//Mostrar els fps al terminal
		if (terminal != NULL){
			ostringstream convert;
			convert << "FPS: " << double(numFrames) / (clock() - clocIni) * 1000;
			terminal->setText2(convert.str().c_str());
		}

		if (isRunning && waitKey(30) >= 0) break;
	}
	isRunning = false;
}

/**
* Executa el detector amb la imatge del path
*/
void MainClass::visualitzaImatge(String v){

	//Llegeix la imatge
	Mat frame;
	frame = imread(v);
	if (!frame.data){  // Check for invalid input
		if (terminal != NULL)
			terminal->setText2("No s'ha pogut obrir el fitxer");
		return;
	}
	//Si supera 720 d'amplada s'aplica un resize;
	if (frame.size().width>720)
		resize(frame, frame, Size(720, 720 * frame.size().height / frame.size().width));

	//Crea la classe que genera la ROI
	int method = cROI.getMethod();
	cROI = ComputeROI(frame);
	cROI.setMethod(method);

	//Actualitza el tamany del frame del detector de senyals.
	signDet.setSizeFrame(frame.size().height, frame.size().width);

	//Tractar imatge
	tractarFrame(frame);
}

/**
* Finalitza execució del video 
*/
void MainClass::finishExec(){
	isRunning = false;
}

/**
* Genera un nou classificador
*/
void MainClass::generateNewClassifier(){
	classifier = Classifier();
}

/**
* Estableix un nou metode de ROI
*/
void MainClass::setRoiMethod(int m){
	cROI.setMethod(m);
	numFrames = 1;
	clocIni = clock();
}

/**
* Genera una nova xarxa neuronal
*/
void MainClass::newClassifier(){
	
	classifier.newNet();
}

/**
* Estableix un nou directori de base de dades
*/
void MainClass::setNewDirectoryDataset(String path){
	classifier.setNewDirectory(path);
}

/**
* Estableix el terminal
*/
void MainClass::setTerminal(QTTerminal* t){
	terminal = t;
}

/**
* Estableix la finestra opengl on mostrar els resultats
*/
void MainClass::setOpenGl(QOpenGLWCustom* ogl){
	openGl = ogl;
}

/**
* Dibuixa un frame a la finestra opengl
*/
void MainClass::drawFrame(Mat& frame, vector<pair<Rect, Mat> >& detSigns){
	if (openGl != NULL){
		openGl->setFrame(frame);
		openGl->setDetectedSigns(detSigns);
		openGl->update();
	}
}


/**
* Funció que detecta i classifica els senyals de la imatge frame.
*/
void MainClass::tractarFrame(Mat& frame){
	//Computa la regió d'interés
	Mat ImROI;	Rect ROI;
	cROI.compute(frame, ImROI, ROI);

	//Detecta els senyals de la ROI
	vector<vector<Point>> detectedContourns;
	vector<Rect> boundingB;
	vector<int> color;
	signDet.detect(ImROI, detectedContourns, boundingB,color);
	//Passa el boundingB de ROI a frame
	for (int i = 0; i < boundingB.size(); ++i){
		boundingB[i].x += ROI.x;
		boundingB[i].y += ROI.y;
		//rectangle(prov, boundingB[i], Scalar(0, 0, 255), 4);
	}

	//Classifica cadascun dels senyals trobats
	vector<pair<pair<Rect,Mat>, double> > result;
	if (detectedContourns.size()>0)
		classifier.classify(frame, boundingB, detectedContourns, color,result);

		vector<pair<Rect, Mat> > rightResults(0);
	for (int i = 0; i < result.size(); ++i){
		//Es mostra el resultat
		if (result[i].second > 0.5){
			rectangle(frame, result[i].first.first, Scalar(0, 0, 255), 4);
			rightResults.push_back(result[i].first);
		}
	}
	
	if (openGl != NULL) 
		drawFrame(frame, rightResults);
}
#include "signdetectorapp.h"
#include <fstream>




SignDetectorApp::SignDetectorApp(QWidget *parent)
	: QMainWindow(parent)
{
	//Inicialització de la GUI
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()),
		this, SLOT(run()));
	connect(ui.pauseButton, SIGNAL(clicked()),
		this, SLOT(finishExec()));
	connect(ui.typeROISelector, SIGNAL(currentIndexChanged(int)),
		this, SLOT(ChangeROIMethod(int)));
	connect(ui.generaClassificador, SIGNAL(clicked()),
		this, SLOT(newClassifier()));

	connect(ui.datasetPath, SIGNAL(returnPressed()),
		this, SLOT(changeDataSetDir()));
	
	ui.videoPath->setText(defaultPathVideo);
	ui.datasetPath->setText(defaultPathDataSet);
	ui.pauseButton->hide();
	mainClass.setTerminal(ui.text2show);
	mainClass.setOpenGl(ui.openGLWidget);
	//Estableix el directori de la dada de base
	mainClass.setNewDirectoryDataset(defaultPathDataSet.toStdString());

}

SignDetectorApp::~SignDetectorApp()
{
	mainClass.finishExec();
}
/**
* Passar video/imatge al detector
*/
void SignDetectorApp::run(){
	QString path2 = ui.videoPath->text();
	if (!fexists(path2.toStdString())){
		String s = "-El fitxer " + path2.toStdString() + " no existeix!";
		ui.text2show->setText2(s);
		return;
	}
	ui.pushButton->hide();
	ui.pauseButton->show();
	ui.videoPath->setDisabled(true);
	ui.datasetPath->setDisabled(true);
	ui.videoImage->setDisabled(true);
	ui.generaClassificador->setDisabled(true);

	if (path2.contains(".jpg")){
		ui.videoImage->setCurrentIndex(1);
	}
	if (path2.contains(".mp4")){
		ui.videoImage->setCurrentIndex(0);
	}
	
	if (path2.contains(".jpg") || path2.contains(".mp4")){
		if (ui.videoImage->currentIndex() == 0)
			mainClass.visualitzaVideo(path2.toStdString());
		else
			mainClass.visualitzaImatge(path2.toStdString());
		finishExec();
	}
	ui.datasetPath->setDisabled(false);
	ui.videoPath->setDisabled(false);
	ui.videoImage->setDisabled(false);
	ui.generaClassificador->setDisabled(false);
	ui.pauseButton->hide();
	ui.pushButton->show();
}

/**
* Finalitza l'execució del detector
*/
void SignDetectorApp::finishExec(){
	mainClass.finishExec();
}
/**
* Retorna cert si existeix el fitxer
*/
bool SignDetectorApp::fexists(String filename) {
	std::ifstream ifile(filename);
	return (bool)ifile;
}

/**
* Canvia el metode de ROI
*/
void SignDetectorApp::ChangeROIMethod(int i){
	
	mainClass.setRoiMethod(i+1);
}

/**
* Genera un nou classificador
*/
void SignDetectorApp::newClassifier(){
	setCursor(Qt::WaitCursor);
	mainClass.newClassifier();
	ui.text2show->setText("-S'ha generat una nova xarxa neuronal!");
	setCursor(Qt::ArrowCursor);
}

/**
* S'ha canviat el directori del dataset
*/
void SignDetectorApp::changeDataSetDir(){
	setCursor(Qt::WaitCursor);
	QString p = ui.datasetPath->text();
	mainClass.setNewDirectoryDataset(p.toStdString());
	ui.text2show->setText("-S'ha modificat el directori de la base de dades a: " + p);
	setCursor(Qt::ArrowCursor);
}


/**
* Afegeix text
*/
void SignDetectorApp::addText(String s){
	QString str = ui.text2show->text();
	QString str2 = QString::fromUtf8(s.c_str());
	ui.text2show->setText(str + "\n"+str2);
}
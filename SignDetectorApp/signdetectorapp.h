#ifndef SIGNDETECTORAPP_H
#define SIGNDETECTORAPP_H

#include <QtWidgets/QMainWindow>
#include "ui_signdetectorapp.h"
#include "MainClass.h"

class SignDetectorApp : public QMainWindow
{
	Q_OBJECT

public:
	SignDetectorApp(QWidget *parent = 0);
	~SignDetectorApp();
	void addText(String s);
public slots:
	//Passar video/imatge al detector
	void run();
	//Acaba l'execució
	void finishExec();
	//Modifica el mètode de ROI
	void ChangeROIMethod(int i);
	//Crea unes noves xarxes neuronals
	void newClassifier();
	//S'ha modificat la direcció de la base de dades
	void changeDataSetDir();
signals:

private:
	Ui::SignDetectorAppClass ui;
	MainClass mainClass;
	//Comprova si existeix un fitxer
	static bool fexists(String filename);
	//Direcció del vídeo per defecte
	QString defaultPathVideo = "E:\\Usuario\\nuovo\\Documents\\videoX.mp4";
	//Direcció de la base de dades
	QString defaultPathDataSet = "E:\\dataset\\";


};

#endif // SIGNDETECTORAPP_H

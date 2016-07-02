#ifndef QOPENGLCUSTOM_H
#define QOPENGLCUSTOM_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "C:\Qt\5.6\msvc2013_64\include\QtWidgets\qopenglwidget.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;
class QOpenGLWCustom :
	public QOpenGLWidget
{
public:
	QOpenGLWCustom(QObject *parent);
	~QOpenGLWCustom();
	//Estableix el frame a mostrar
	void setFrame(Mat& frame);
	//Estableix les senyals detectades al frame que es mostra
	void setDetectedSigns(vector<pair<Rect, Mat> >& detSigns);

protected:
	//Funció que pinta l'escena
	void paintGL();
private:
	//Mostra una imatge en una posició concreta de la finestra
	void drawImage(Mat& m, double& vRecMinX, double& vRecMaxX, double& vRecMinY, double& vRecMaxY);
	//Genera una textura a partir d'una imatge
	GLuint matToTexture(cv::Mat &mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter);
	//Calculs necessaris per conservar el ratio d'una imatge
	void conserveRatio(double ratioIm, double& vRecMinX, double& vRecMaxX, double& vRecMinY, double& vRecMaxY);
	//Frame actual
	Mat frame;
	//Senyals detectats
	vector<pair<Rect, Mat> > signsDet;
};

#endif

#ifndef QTTERMINAL_H
#define QTTERMINAL_H
#include "C:\Qt\5.6\msvc2013_64\include\QtWidgets\qlabel.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
class QTTerminal :
	public QLabel
{
public:
	QTTerminal(QObject *parent = 0);
	~QTTerminal();
	//Afegeix text al final
	void addText(String s);
	//Substitueix text
	void setText2(String s);
	//Neteja terminal
	void clearText();
};
#endif


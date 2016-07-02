#include "QTTerminal.h"


QTTerminal::QTTerminal(QObject *parent2)
{
}


QTTerminal::~QTTerminal()
{
}

//Afegeix text al final
void QTTerminal::addText(String s){
	QString str = this->text();
	QString str2 = QString::fromUtf8(s.c_str());
	this->setText(str + "\n" + str2);
}

//Substitueix text
void QTTerminal::setText2(String s){
	QString str2 = QString::fromUtf8(s.c_str());
	this->setText(str2);
}

//Neteja terminal
void QTTerminal::clearText(){
	this->setText("");
}
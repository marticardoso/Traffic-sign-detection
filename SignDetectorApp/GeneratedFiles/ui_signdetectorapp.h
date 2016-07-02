/********************************************************************************
** Form generated from reading UI file 'signdetectorapp.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNDETECTORAPP_H
#define UI_SIGNDETECTORAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QOpenGLWCustom.h"
#include "QTTerminal.h"

QT_BEGIN_NAMESPACE

class Ui_SignDetectorAppClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QComboBox *videoImage;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *videoPath;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *ROILayout;
    QLabel *label_2;
    QComboBox *typeROISelector;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *datasetPath;
    QPushButton *generaClassificador;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pauseButton;
    QSpacerItem *horizontalSpacer_2;
    QOpenGLWCustom *openGLWidget;
    QTTerminal *text2show;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SignDetectorAppClass)
    {
        if (SignDetectorAppClass->objectName().isEmpty())
            SignDetectorAppClass->setObjectName(QStringLiteral("SignDetectorAppClass"));
        SignDetectorAppClass->resize(704, 873);
        SignDetectorAppClass->setMinimumSize(QSize(564, 527));
        centralWidget = new QWidget(SignDetectorAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_5 = new QVBoxLayout(groupBox_4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, -1, -1, -1);
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_4->addWidget(label_5);

        videoImage = new QComboBox(groupBox_4);
        videoImage->setObjectName(QStringLiteral("videoImage"));

        horizontalLayout_4->addWidget(videoImage);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, -1, -1, -1);
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        videoPath = new QLineEdit(groupBox_4);
        videoPath->setObjectName(QStringLiteral("videoPath"));

        horizontalLayout_2->addWidget(videoPath);


        verticalLayout_5->addLayout(horizontalLayout_2);


        verticalLayout_4->addWidget(groupBox_4);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        ROILayout = new QHBoxLayout();
        ROILayout->setSpacing(6);
        ROILayout->setObjectName(QStringLiteral("ROILayout"));
        ROILayout->setContentsMargins(0, -1, 0, -1);
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        ROILayout->addWidget(label_2);

        typeROISelector = new QComboBox(groupBox_3);
        typeROISelector->setObjectName(QStringLiteral("typeROISelector"));

        ROILayout->addWidget(typeROISelector);


        verticalLayout_2->addLayout(ROILayout);


        verticalLayout_4->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, -1, -1, -1);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        datasetPath = new QLineEdit(groupBox_2);
        datasetPath->setObjectName(QStringLiteral("datasetPath"));

        horizontalLayout_3->addWidget(datasetPath);


        verticalLayout_3->addLayout(horizontalLayout_3);

        generaClassificador = new QPushButton(groupBox_2);
        generaClassificador->setObjectName(QStringLiteral("generaClassificador"));

        verticalLayout_3->addWidget(generaClassificador);


        verticalLayout_4->addWidget(groupBox_2);


        verticalLayout->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pauseButton = new QPushButton(centralWidget);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));

        horizontalLayout->addWidget(pauseButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        openGLWidget = new QOpenGLWCustom(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setMinimumSize(QSize(200, 400));

        verticalLayout->addWidget(openGLWidget);

        text2show = new QTTerminal(centralWidget);
        text2show->setObjectName(QStringLiteral("text2show"));

        verticalLayout->addWidget(text2show);

        SignDetectorAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SignDetectorAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 704, 21));
        SignDetectorAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SignDetectorAppClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SignDetectorAppClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SignDetectorAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SignDetectorAppClass->setStatusBar(statusBar);

        retranslateUi(SignDetectorAppClass);

        QMetaObject::connectSlotsByName(SignDetectorAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *SignDetectorAppClass)
    {
        SignDetectorAppClass->setWindowTitle(QApplication::translate("SignDetectorAppClass", "SignDetectorApp", 0));
        groupBox->setTitle(QApplication::translate("SignDetectorAppClass", "Opcions", 0));
        groupBox_4->setTitle(QApplication::translate("SignDetectorAppClass", "Fitxer a executar", 0));
        label_5->setText(QApplication::translate("SignDetectorAppClass", "Tipus de fitxer:", 0));
        videoImage->clear();
        videoImage->insertItems(0, QStringList()
         << QApplication::translate("SignDetectorAppClass", "Video", 0)
         << QApplication::translate("SignDetectorAppClass", "Imatge", 0)
        );
        label_3->setText(QApplication::translate("SignDetectorAppClass", "Path del fitxer a executar", 0));
        groupBox_3->setTitle(QApplication::translate("SignDetectorAppClass", "Detector", 0));
        label_2->setText(QApplication::translate("SignDetectorAppClass", "M\303\250tode de ROI:", 0));
        typeROISelector->clear();
        typeROISelector->insertItems(0, QStringList()
         << QApplication::translate("SignDetectorAppClass", "1. Tota la imatge", 0)
         << QApplication::translate("SignDetectorAppClass", "2. Part central dreta de la imatge", 0)
         << QApplication::translate("SignDetectorAppClass", "3. Utilitzant detecci\303\263 de linees mitjan\303\247ant Localitzaci\303\263 1", 0)
         << QApplication::translate("SignDetectorAppClass", "4. Utilitzant detecci\303\263 de linees mitjan\303\247ant Hough", 0)
        );
        groupBox_2->setTitle(QApplication::translate("SignDetectorAppClass", "Classificador", 0));
        label_4->setText(QApplication::translate("SignDetectorAppClass", "Path de la base de dades de senyals:", 0));
        generaClassificador->setText(QApplication::translate("SignDetectorAppClass", "Genera una nova xarxa neuronal", 0));
        pushButton->setText(QApplication::translate("SignDetectorAppClass", "Executa detector", 0));
        pauseButton->setText(QApplication::translate("SignDetectorAppClass", "Acaba execuci\303\263", 0));
        text2show->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SignDetectorAppClass: public Ui_SignDetectorAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNDETECTORAPP_H

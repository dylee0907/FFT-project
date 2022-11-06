/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad;
    QAction *actionSave;
    QWidget *centralwidget;
    QGridLayout *gridLayout_7;
    QFormLayout *formLayout;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QPushButton *pb_run;
    QPushButton *pb_sr;
    QPushButton *pb_length;
    QPushButton *pb_point;
    QPushButton *pb_hope;
    QTextBrowser *brow_text;
    QGridLayout *gridLayout_4;
    QGroupBox *gb_ori;
    QGridLayout *gridLayout_2;
    QCustomPlot *qw_ori;
    QGroupBox *gb_pow;
    QGridLayout *gridLayout_3;
    QCustomPlot *qw_pow;
    QGroupBox *gb_den;
    QGridLayout *gridLayout;
    QCustomPlot *qw_den;
    QLineEdit *edit;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(966, 777);
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_7 = new QGridLayout(centralwidget);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pb_run = new QPushButton(centralwidget);
        pb_run->setObjectName(QString::fromUtf8("pb_run"));
        QFont font;
        font.setFamily(QString::fromUtf8("\353\247\221\354\235\200 \352\263\240\353\224\225"));
        pb_run->setFont(font);

        gridLayout_5->addWidget(pb_run, 0, 0, 1, 1);

        pb_sr = new QPushButton(centralwidget);
        pb_sr->setObjectName(QString::fromUtf8("pb_sr"));
        pb_sr->setFont(font);

        gridLayout_5->addWidget(pb_sr, 1, 0, 1, 1);

        pb_length = new QPushButton(centralwidget);
        pb_length->setObjectName(QString::fromUtf8("pb_length"));
        pb_length->setFont(font);

        gridLayout_5->addWidget(pb_length, 2, 0, 1, 1);

        pb_point = new QPushButton(centralwidget);
        pb_point->setObjectName(QString::fromUtf8("pb_point"));
        pb_point->setFont(font);

        gridLayout_5->addWidget(pb_point, 3, 0, 1, 1);

        pb_hope = new QPushButton(centralwidget);
        pb_hope->setObjectName(QString::fromUtf8("pb_hope"));
        pb_hope->setFont(font);

        gridLayout_5->addWidget(pb_hope, 4, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);

        brow_text = new QTextBrowser(centralwidget);
        brow_text->setObjectName(QString::fromUtf8("brow_text"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\353\247\221\354\235\200 \352\263\240\353\224\225"));
        font1.setPointSize(11);
        brow_text->setFont(font1);

        gridLayout_6->addWidget(brow_text, 1, 0, 1, 1);


        formLayout->setLayout(0, QFormLayout::LabelRole, gridLayout_6);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gb_ori = new QGroupBox(centralwidget);
        gb_ori->setObjectName(QString::fromUtf8("gb_ori"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\353\247\221\354\235\200 \352\263\240\353\224\225"));
        font2.setBold(false);
        font2.setWeight(50);
        gb_ori->setFont(font2);
        gridLayout_2 = new QGridLayout(gb_ori);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        qw_ori = new QCustomPlot(gb_ori);
        qw_ori->setObjectName(QString::fromUtf8("qw_ori"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Times New Roman"));
        font3.setBold(false);
        font3.setWeight(50);
        qw_ori->setFont(font3);

        gridLayout_2->addWidget(qw_ori, 0, 0, 1, 1);


        gridLayout_4->addWidget(gb_ori, 0, 0, 1, 1);

        gb_pow = new QGroupBox(centralwidget);
        gb_pow->setObjectName(QString::fromUtf8("gb_pow"));
        gb_pow->setFont(font2);
        gridLayout_3 = new QGridLayout(gb_pow);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        qw_pow = new QCustomPlot(gb_pow);
        qw_pow->setObjectName(QString::fromUtf8("qw_pow"));
        qw_pow->setFont(font3);

        gridLayout_3->addWidget(qw_pow, 0, 0, 1, 1);


        gridLayout_4->addWidget(gb_pow, 1, 0, 1, 1);

        gb_den = new QGroupBox(centralwidget);
        gb_den->setObjectName(QString::fromUtf8("gb_den"));
        gb_den->setFont(font2);
        gridLayout = new QGridLayout(gb_den);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        qw_den = new QCustomPlot(gb_den);
        qw_den->setObjectName(QString::fromUtf8("qw_den"));
        qw_den->setFont(font3);

        gridLayout->addWidget(qw_den, 0, 0, 1, 1);


        gridLayout_4->addWidget(gb_den, 2, 0, 1, 1);


        formLayout->setLayout(0, QFormLayout::FieldRole, gridLayout_4);


        gridLayout_7->addLayout(formLayout, 0, 0, 1, 1);

        edit = new QLineEdit(centralwidget);
        edit->setObjectName(QString::fromUtf8("edit"));
        edit->setFont(font);

        gridLayout_7->addWidget(edit, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 966, 21));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Times New Roman"));
        menubar->setFont(font4);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\353\247\221\354\235\200 \352\263\240\353\224\225"));
        font5.setBold(true);
        font5.setWeight(75);
        menuFile->setFont(font5);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLoad->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
#if QT_CONFIG(shortcut)
        actionLoad->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F2", nullptr));
#endif // QT_CONFIG(shortcut)
        pb_run->setText(QCoreApplication::translate("MainWindow", "RUN", nullptr));
        pb_sr->setText(QCoreApplication::translate("MainWindow", "Sample Rate (Hz)", nullptr));
        pb_length->setText(QCoreApplication::translate("MainWindow", "Sample Length(#)", nullptr));
        pb_point->setText(QCoreApplication::translate("MainWindow", "FFT point (#)", nullptr));
        pb_hope->setText(QCoreApplication::translate("MainWindow", "Hope size (#)", nullptr));
        gb_ori->setTitle(QCoreApplication::translate("MainWindow", "Original Data", nullptr));
        gb_pow->setTitle(QCoreApplication::translate("MainWindow", "Power(dB)", nullptr));
#if QT_CONFIG(tooltip)
        qw_pow->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        gb_den->setTitle(QCoreApplication::translate("MainWindow", "Density(%)", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

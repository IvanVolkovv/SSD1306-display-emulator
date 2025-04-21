#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFrame>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include "qcustomplot.h"

// #include <iostream>



class MainWindow : public QMainWindow {
	
    Q_OBJECT
	
	/* --------- */

	QMenuBar *MenuBar = nullptr; 							// Создаю объект класса для работы с QMenuBar
	QMenu *FileMenu = nullptr; 
	QCustomPlot *plot = nullptr; 

	QCPColorMap *ColorMap = nullptr; 
	
	QCPColorScale *ColorScale = nullptr; 

public:
    explicit MainWindow(QWidget *parent = nullptr);
	void createFormCentralWidget(void); 
	void createMenus(void); 
	void settingPlot(void); 

signals:

};

#endif // MAINWINDOW_H

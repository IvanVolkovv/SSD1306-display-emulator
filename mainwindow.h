#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QFont>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDir>                    
#include <QFile>
#include <QFileDialog>
#include "DisplayOLEDEmulator.h"

#include <QMargins>
#include <QTimer>


class MainWindow : public QMainWindow {
	
    Q_OBJECT	
	/* --------- */

	QMenuBar *MenuBar = nullptr; 							// Создаю объект класса для работы с QMenuBar
	QMenu *FileMenu = nullptr; 

	ColumnPixels *pixel = nullptr; 
	DisplayEmulator *Rows = nullptr;
		
	QTimer *timer = nullptr;
	
	QString NameOpenFile; 
	
	// Buttons
	QPushButton *ButtonOpenFile; 
	QPushButton *ButtonUpdateFile; 
	

public:
    explicit MainWindow(QWidget *parent = nullptr);
	void createFormCentralWidget(void); 
	void createMenus(void); 

signals:


private slots: 
	void slotTimerAlarm(void);
	
	// for Buttons
	void buttonClickHandler_OpenFile(void); 
	void buttonClickHandler_UpdateFile(void); 
	
	
	
	
	


};

#endif // MAINWINDOW_H

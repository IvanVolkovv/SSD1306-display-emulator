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
	QMenu *SetSizeDisplayMenu = nullptr; 
	QMenu *SetSizePixelMenu = nullptr; 

	QWidget *wgt = nullptr; 
	QVBoxLayout *layout = nullptr; 

	ColumnPixels *pixel = nullptr; 
	DisplayEmulator *Rows = nullptr;
		
	QTimer *timer = nullptr;
	
	QString NameOpenFile; 
	
	QLabel *NameDisplayEmulator = nullptr;
	
	
	
	// Buttons
	QPushButton *ButtonOpenFile; 
	QPushButton *ButtonUpdateFile; 
	
	// var
	int size_pixel = 10; 
	int number_pages = 4; 
	

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
	
	// for Actions
	void triggeredHandler_SetSize128x32(void); 
	void triggeredHandler_SetSize128x64(void); 
	
	void triggeredHandler_SetSizePixl_2x2Act(void);
	void triggeredHandler_SetSizePixl_4x4Act(void);
	void triggeredHandler_SetSizePixl_8x8Act(void);
	void triggeredHandler_SetSizePixl_10x10Act(void);


};

#endif // MAINWINDOW_H

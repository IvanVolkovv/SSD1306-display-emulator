#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QFont>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDir>                    
#include <QFile>
#include <QFileDialog>
#include <QMargins>
#include <QPixmap>
#include "DisplayOLEDEmulator.h"


class MainWindow : public QMainWindow {
	
    Q_OBJECT	
	
	QMenuBar *MenuBar = nullptr; 							
	QMenu *FileMenu = nullptr; 
	QMenu *SetSizeDisplayMenu = nullptr; 
	QMenu *SetSizePixelMenu = nullptr; 
	
	QWidget *wgt = nullptr; 
	QVBoxLayout *layout = nullptr; 
	QLabel *NameDisplayEmulator = nullptr;
 
	QString NameOpenFile; 
	
	DisplayEmulator *Rows = nullptr;
	
	// Buttons
	QPushButton *ButtonOpenFile; 
	QPushButton *ButtonUpdateFile; 
	QPushButton *SaveImgDisplay; 
	
	// variables
	int size_pixel = 10; 
	int number_pages = 4; 
	
	// methods of the class
	void createFormCentralWidget(void); 
	void createMenus(void); 
	void rebuildMainWindow(int, int); 
	

public:
    explicit MainWindow(QWidget *parent = nullptr);
	
signals:
	/* --- */ 

private slots: 
	
	// for Buttons
	void buttonClickHandler_OpenFile(void); 
	void buttonClickHandler_UpdateFile(void);
	void buttonClickHandler_SaveImgDisplay(void); 	
	
	// for Actions
	void triggeredHandler_SetSize128x32(void); 
	void triggeredHandler_SetSize128x64(void); 
	void triggeredHandler_SetSizePixl_2x2Act(void);
	void triggeredHandler_SetSizePixl_4x4Act(void);
	void triggeredHandler_SetSizePixl_8x8Act(void);
	void triggeredHandler_SetSizePixl_10x10Act(void);


};

#endif // MAINWINDOW_H

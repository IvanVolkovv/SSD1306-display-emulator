#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
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

public:
    explicit MainWindow(QWidget *parent = nullptr);
	void createFormCentralWidget(void); 
	void createMenus(void); 

signals:


private slots: 
	void slotTimerAlarm(void);


};

#endif // MAINWINDOW_H

#ifndef DISPLAY_SEGMENT_H
#define DISPLAY_SEGMENT_H

#include <QWidget>



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

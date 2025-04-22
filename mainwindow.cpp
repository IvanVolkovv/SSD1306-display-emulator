#include "mainwindow.h"

MainWindow::
MainWindow(QWidget *parent) : QMainWindow(parent){

    this->setWindowTitle("OLED Display Emulator 0.1.0");
    this->setMinimumHeight(500);
    this->setMinimumWidth(500);
	
	// вызывю ф-ю для создания меню
	createMenus(); 
	// тут вызываю ф-ю, которая создаёт и компанует все элементы центрального виджета главного окна
	createFormCentralWidget(); 
	
	
	/* TIMER ------------------------------------------------------------ */ 
	timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
	timer->start(50); 
		
}

/*!
 * @brief:	Функция создаёт и компонует все элементы центрального виджета главного окна
*/
void MainWindow::
createFormCentralWidget(void){

	QWidget *wgt = new QWidget(this);
	QVBoxLayout *layout = new QVBoxLayout(wgt);
	
	Rows = new DisplayEmulator(wgt); 
	layout->addWidget(Rows);
	
	/* DEBUG ------------------------------------- */ 
	// ColumnPixels *pixel = new ColumnPixels(wgt); 
	// pixel = new ColumnPixels(wgt); 
	// layout->addWidget(pixel);
	/*-------------------------------------------- */ 
	
	setCentralWidget(wgt);
	
}

/*!
 * @brief:	Функция создаёт и компонует меню
*/
void MainWindow::
createMenus(void){
	
	MenuBar = new QMenuBar(this); 
	this->setMenuBar(MenuBar); 	
	FileMenu = this->menuBar()->addMenu(tr("&File"));
	
}


/* SLOTS --------------------------------------------------------------------------------------------- */ 
 
/*!
 * @brief:	Слот для обработки timeout() таймера
*/
void MainWindow::
slotTimerAlarm(void){
	
  	// qDebug() << " Timer ";
	
	static short int i = 0; 
	++i; 
	
	for(int j = 0; j < 512; ++j)
		Rows->setData(i, j); 
	
}



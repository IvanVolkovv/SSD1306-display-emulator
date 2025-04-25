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
	// timer->start(50); 
		
}

/*!
 * @brief:	Функция создаёт и компонует все элементы центрального виджета главного окна
*/
void MainWindow::
createFormCentralWidget(void){

	// QWidget *wgt = new QWidget(this);
	wgt = new QWidget(this);
	
	// QVBoxLayout *layout = new QVBoxLayout(wgt);
	layout = new QVBoxLayout(wgt);
	
	QLabel *NameDisplayEmulator = new QLabel(wgt); 
	
	NameDisplayEmulator->setText("Display 128 x 32 pixels"); 
	NameDisplayEmulator->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	NameDisplayEmulator->setScaledContents(true); 
	
	QFont Font;
	Font.setBold(true); 
	Font.setPixelSize(30); 
	NameDisplayEmulator->setFont(Font); 
	
	layout->addWidget(NameDisplayEmulator, 0);
	
	Rows = new DisplayEmulator(wgt, 4, 10); 
	layout->addWidget(Rows, 1);
	
	/* DEBUG ------------------------------------- */ 
	// ColumnPixels *pixel = new ColumnPixels(wgt); 
	// pixel = new ColumnPixels(wgt); 
	// layout->addWidget(pixel);
	/*-------------------------------------------- */ 
	
	
	ButtonOpenFile = new QPushButton("&Open file", wgt);
	layout->addWidget(ButtonOpenFile, 2);
	connect(ButtonOpenFile, SIGNAL(clicked()), this, SLOT(buttonClickHandler_OpenFile()));
	
	ButtonUpdateFile = new QPushButton("&Update file", wgt);
	layout->addWidget(ButtonUpdateFile, 3);
	connect(ButtonUpdateFile, SIGNAL(clicked()), this, SLOT(buttonClickHandler_UpdateFile()));
	
	setCentralWidget(wgt);
	
}

/*!
 * @brief:	Функция создаёт и компонует меню
*/
void MainWindow::
createMenus(void){
	
	MenuBar = new QMenuBar(this); 
	this->setMenuBar(MenuBar); 

 	/* MENU: File ----------------------------------------------------------------------------------- */ 
	FileMenu = this->menuBar()->addMenu(tr("&File"));
	
	/* MENU: Size display --------------------------------------------------------------------------- */ 
	SetSizeDisplayMenu = this->menuBar()->addMenu(tr("&Size display"));
	QAction *SetSize128x32Act = new QAction("128 x 32", this);
	QAction *SetSize128x64Act = new QAction("128 x 64", this);
	
	SetSizeDisplayMenu->addAction(SetSize128x32Act); 
	SetSizeDisplayMenu->addAction(SetSize128x64Act);

	connect(SetSize128x32Act, SIGNAL(triggered()), this, SLOT(triggeredHandler_SetSize128x32()));
	connect(SetSize128x64Act, SIGNAL(triggered()), this, SLOT(triggeredHandler_SetSize128x64()));	
	
	
	
	
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

/*!
 * @brief:	Слот для обработки нажатия на кнопку для выбора файла с данными на загрузку для отображения на эмуляторе дисплея
*/
void MainWindow::
buttonClickHandler_OpenFile(void){
	
	NameOpenFile = QFileDialog::getOpenFileName(this, "Open the file", "");                            
                                                                               
	// checking file is open
	if( NameOpenFile == "" )
		return; 
	
	QFile file(NameOpenFile); 
	
	if( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
		return;
		
	QByteArray data;
	data.clear(); 
	data = file.readAll(); 
	
	// close file
	file.close(); 
	
	// Adding data for display on the display emulator
	for(int i = 0; i < 512; ++i){
		Rows->setData(data[i], i); 
	}
	
}

/*!
 * @brief:	Слот для обработки нажатия на кнопку для обновления данных выбранного файла
*/
void MainWindow::
buttonClickHandler_UpdateFile(void){
	
	QFile file(NameOpenFile); 
	
	// checking file is open
	if( NameOpenFile == "" )
		return; 
	
	if( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
		return;
		
	QByteArray data;
	data.clear(); 
	data = file.readAll(); 
	
	// close file
	file.close(); 
	
	// Adding data for display on the display emulator
	for(int i = 0; i < 512; ++i){
		Rows->setData(data[i], i); 
	}
		
}

/*!
 * @brief:	Слот для обработки пункта меню установки размера дисплея - 128х32 пикселя
*/
void MainWindow::
triggeredHandler_SetSize128x32(void){
	
	// qDebug() << "triggeredHandler_SetSize128x32"; 
	
	
	delete Rows; 
	// Rows = nullptr; 
	
	Rows = new DisplayEmulator(wgt, 4, 10); 
	layout->insertWidget(1, Rows); 
	
	
}

/*!
 * @brief:	Слот для обработки пункта меню установки размера дисплея - 128х64 пикселя
*/
void MainWindow::
triggeredHandler_SetSize128x64(void){
	
	
	
	delete Rows; 
	// Rows = nullptr; 
	
	Rows = new DisplayEmulator(wgt, 8, 10); 
	layout->insertWidget(1, Rows); 
	
	
	
	
}






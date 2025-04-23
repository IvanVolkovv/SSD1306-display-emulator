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

	QWidget *wgt = new QWidget(this);
	QVBoxLayout *layout = new QVBoxLayout(wgt);
	
	QLabel *NameDisplayEmulator = new QLabel(wgt); 
	
	NameDisplayEmulator->setText("Display 128 x 32 pixels"); 
	NameDisplayEmulator->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	NameDisplayEmulator->setScaledContents(true); 
	
	QFont Font;
	Font.setBold(true); 
	Font.setPixelSize(30); 
	NameDisplayEmulator->setFont(Font); 
	
	layout->addWidget(NameDisplayEmulator);
	
	Rows = new DisplayEmulator(wgt); 
	layout->addWidget(Rows);
	
	/* DEBUG ------------------------------------- */ 
	// ColumnPixels *pixel = new ColumnPixels(wgt); 
	// pixel = new ColumnPixels(wgt); 
	// layout->addWidget(pixel);
	/*-------------------------------------------- */ 
	
	
	ButtonOpenFile = new QPushButton("&Open file", wgt);
	layout->addWidget(ButtonOpenFile);
	connect(ButtonOpenFile, SIGNAL(clicked()), this, SLOT(buttonClickHandler_OpenFile()));
	
	
	
	ButtonUpdateFile = new QPushButton("&Update file", wgt);
	layout->addWidget(ButtonUpdateFile);
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

/*!
 * @brief:	Слот для обработки нажатия на кнопку для выбора файла с данными на загрузку для отображения на эмуляторе дисплея
*/
void MainWindow::
buttonClickHandler_OpenFile(void){

	qDebug() << "buttonClickHandler_OpenFile"; 
	
	NameOpenFile = QFileDialog::getOpenFileName(this, "Open the file", "");                            
                                                                               
	qDebug() << NameOpenFile; 
	
	if( NameOpenFile == "" )
		return; 
	
	QFile file(NameOpenFile); 
	
	if( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
		return;
		
	QByteArray data;
	
	// data = file.readAll(); 
	
	
	qint64 bufSize = 2;
	char buf[100];
	
	// while (!file.atEnd()) {
		file.read(buf, bufSize);
	// }
	
	
	file.close(); 
	
	qDebug() << buf[0];
	qDebug() << buf[1];
	qDebug() << buf[2];	
	
	
	
	Rows->setData(buf[0], 0); 
	Rows->setData(buf[1], 1); 
	Rows->setData(buf[2], 2); 
	
	
	
	
	
	
	
	
	
}

/*!
 * @brief:	Слот для обработки нажатия на кнопку для обновления данных выбранного файла
*/
void MainWindow::
buttonClickHandler_UpdateFile(void){
	
	qDebug() << "buttonClickHandler_UpdateFile"; 
	
}











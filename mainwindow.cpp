#include "mainwindow.h"

MainWindow::
MainWindow(QWidget *parent) : QMainWindow(parent){

	// Oled Display Emulator
    this->setWindowTitle("ODE 0.1.3");
	
	createMenus(); 
	createFormCentralWidget(); 
		
}

/*!
 * @brief:	Функция создаёт и компонует все элементы центрального виджета главного окна
*/
void MainWindow::
createFormCentralWidget(void){

	wgt = new QWidget(this);
	layout = new QVBoxLayout(wgt);
	
	NameDisplayEmulator = new QLabel(wgt); 	
	NameDisplayEmulator->setText("Display 128 x 32 pixels"); 
	NameDisplayEmulator->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	NameDisplayEmulator->setScaledContents(true); 
	
	QFont Font;
	Font.setBold(true); 
	Font.setPixelSize(15); 
	NameDisplayEmulator->setFont(Font); 
	
	layout->addWidget(NameDisplayEmulator, 0);
	
	QHBoxLayout *LayoutButton = new QHBoxLayout(wgt); 
	
	ButtonOpenFile = new QPushButton("&Open file", wgt);
	ButtonOpenFile->setMaximumSize(100, 50); 
	ButtonOpenFile->setMinimumSize(50, 25); 
	// layout->addWidget(ButtonOpenFile);
	LayoutButton->addWidget(ButtonOpenFile);
	connect(ButtonOpenFile, SIGNAL(clicked()), this, SLOT(buttonClickHandler_OpenFile()));
	
	ButtonUpdateFile = new QPushButton("&Update file", wgt);
	ButtonUpdateFile->setMaximumSize(100, 50); 
	ButtonUpdateFile->setMinimumSize(50, 25); 
	// layout->addWidget(ButtonUpdateFile);
	LayoutButton->addWidget(ButtonUpdateFile);
	connect(ButtonUpdateFile, SIGNAL(clicked()), this, SLOT(buttonClickHandler_UpdateFile()));
	
	SaveImgDisplay = new QPushButton("&Save Display", wgt);
	SaveImgDisplay->setMaximumSize(100, 50); 
	SaveImgDisplay->setMinimumSize(50, 25); 
	// layout->addWidget(ButtonUpdateFile);
	LayoutButton->addWidget(SaveImgDisplay);
	connect(SaveImgDisplay, SIGNAL(clicked()), this, SLOT(buttonClickHandler_SaveImgDisplay()));
	
	LayoutButton->addStretch(1); 
	
	layout->addLayout(LayoutButton, 0);
	
	setCentralWidget(wgt);
	
	rebuildMainWindow(number_pages, size_pixel); 
	
}

/*!
 * @brief:	Функция создаёт и компонует меню
*/
void MainWindow::
createMenus(void){
	
	MenuBar = new QMenuBar(this); 
	this->setMenuBar(MenuBar); 

 	/* MENU: File ----------------------------------------------------------------------------------- */ 
	// FileMenu = this->menuBar()->addMenu(tr("&File"));
	
	/* MENU: Size display --------------------------------------------------------------------------- */ 
	SetSizeDisplayMenu = this->menuBar()->addMenu(tr("&Size display"));
	QAction *SetSize128x32Act = new QAction("128 x 32", this);
	QAction *SetSize128x64Act = new QAction("128 x 64", this);
	
	SetSizeDisplayMenu->addAction(SetSize128x32Act); 
	SetSizeDisplayMenu->addAction(SetSize128x64Act);

	connect(SetSize128x32Act, SIGNAL(triggered()), this, SLOT(triggeredHandler_SetSize128x32()));
	connect(SetSize128x64Act, SIGNAL(triggered()), this, SLOT(triggeredHandler_SetSize128x64()));	
	
	/* MENU: Size pixel ----------------------------------------------------------------------------- */ 
	SetSizePixelMenu = this->menuBar()->addMenu(tr("&Size pixel"));
	QAction *SetSizePixl_2x2Act = new QAction("2 x 2", this);
	QAction *SetSizePixl_4x4Act = new QAction("4 x 4", this);
	QAction *SetSizePixl_8x8Act = new QAction("8 x 8", this);
	QAction *SetSizePixl_10x10Act = new QAction("10 x 10", this);
	SetSizePixelMenu->addAction(SetSizePixl_2x2Act); 
	SetSizePixelMenu->addAction(SetSizePixl_4x4Act);
	SetSizePixelMenu->addAction(SetSizePixl_8x8Act); 
	SetSizePixelMenu->addAction(SetSizePixl_10x10Act);
	connect(SetSizePixl_2x2Act, SIGNAL(triggered()), this, SLOT(triggeredHandler_SetSizePixl_2x2Act()));
	connect(SetSizePixl_4x4Act, SIGNAL(triggered()), this, SLOT(triggeredHandler_SetSizePixl_4x4Act()));
	connect(SetSizePixl_8x8Act, SIGNAL(triggered()), this, SLOT(triggeredHandler_SetSizePixl_8x8Act()));
	connect(SetSizePixl_10x10Act, SIGNAL(triggered()), this, SLOT(triggeredHandler_SetSizePixl_10x10Act()));
		
}

/*!
 * @brief:	Функция для перерисовки главного окна. 
 * @param:	number_pages - кол-во страниц дисплея; 
 * 			pixel_size - размер пикселя. 
 * @note: 	Размер главного окна зависит от размера виджета OLED дисплея. 
*/
void MainWindow::
rebuildMainWindow(int number_pages, int pixel_size){
	
	delete Rows; 
	// Rows = nullptr; 
	Rows = new DisplayEmulator(wgt, number_pages, pixel_size); 
	layout->insertWidget(1, Rows); 	
	
	int height_mainwindow = number_pages * 8 * pixel_size; 
	height_mainwindow += 150; 
	
	int width_mainwindow = 128 * pixel_size + 6; 
	width_mainwindow += 20; 
	
	this->setFixedSize(width_mainwindow, height_mainwindow); 
	
}

/* SLOTS --------------------------------------------------------------------------------------------- */ 

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
 * @brief:	Слот для обработки нажатия на кнопку для сохранения изображения на дисплее
*/
void MainWindow::
buttonClickHandler_SaveImgDisplay(void){

	QString Format;
	QString DirLocation = QFileDialog::getSaveFileName(this, tr("Save Image"), "DisplayImag", ".png", &Format);

	if( !DirLocation.isEmpty() ){                 
		if( Format.contains("png") ){     
			QPixmap pixmap(Rows->size());
			Rows->render(&pixmap);
			pixmap.save(DirLocation + Format, nullptr, 0); 			                                                      
		}
	}
}	

/*!
 * @brief:	Слот для обработки пункта меню установки размера дисплея - 128х32 пикселя
*/
void MainWindow::
triggeredHandler_SetSize128x32(void){
	number_pages = 4; 
	NameDisplayEmulator->setText("Display 128 x 32 pixels"); 
	rebuildMainWindow(number_pages, size_pixel); 
}

/*!
 * @brief:	Слот для обработки пункта меню установки размера дисплея - 128х64 пикселя
*/
void MainWindow::
triggeredHandler_SetSize128x64(void){
	number_pages = 8; 
	NameDisplayEmulator->setText("Display 128 x 64 pixels"); 
	rebuildMainWindow(number_pages, size_pixel); 
}

/*!
 * @brief:	Слот для обработки пункта меню установки размера пикселя - 2 х 2 пикселя
*/
void MainWindow::
triggeredHandler_SetSizePixl_2x2Act(void){
	size_pixel = 2; 
	rebuildMainWindow(number_pages, size_pixel); 
}

/*!
 * @brief:	Слот для обработки пункта меню установки размера пикселя - 4 х 4 пикселя
*/
void MainWindow::
triggeredHandler_SetSizePixl_4x4Act(void){
	size_pixel = 4; 
	rebuildMainWindow(number_pages, size_pixel); 
}

/*!
 * @brief:	Слот для обработки пункта меню установки размера пикселя - 8 х 8 пикселя
*/
void MainWindow::
triggeredHandler_SetSizePixl_8x8Act(void){
	size_pixel = 8; 
	rebuildMainWindow(number_pages, size_pixel); 
}

/*!
 * @brief:	Слот для обработки пункта меню установки размера пикселя - 10 х 10 пикселя
*/
void MainWindow::
triggeredHandler_SetSizePixl_10x10Act(void){
	size_pixel = 10; 
	rebuildMainWindow(number_pages, size_pixel); 
}
	
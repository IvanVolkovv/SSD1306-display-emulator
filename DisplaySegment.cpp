#include "mainwindow.h"

MainWindow::
MainWindow(QWidget *parent) : QMainWindow(parent){

    this->setWindowTitle("Display Emulator 0.0.1");
    this->setMinimumHeight(500);
    this->setMinimumWidth(500);

	// вызывю ф-ю для создания меню
	createMenus(); 
	// тут вызываю ф-ю, которая создаёт и компанует все элементы центрального виджета главного окна
	createFormCentralWidget(); 
	
	settingPlot(); 
	
}

/*!
 * @brief:	Функция создаёт и компонует все элементы центрального виджета главного окна
*/
void MainWindow::
createFormCentralWidget(void){

	QWidget *wgt = new QWidget(this);
	QVBoxLayout *layout = new QVBoxLayout(wgt);
	plot = new QCustomPlot(wgt);  
	layout->addWidget(plot); 
	setCentralWidget(wgt);
	
}

/*!
 * @brief:	Функция настраивает график
*/
void MainWindow::
settingPlot(void){
	
	// настройка параметров линии отрисовки графика
    plot->addGraph();                                                                 	// добавляем линию графика на полотно (рисуем график)
    plot->graph(0)->setPen(QPen(Qt::black, 1));                                      	// устанавливаем цвет линии графика и толщину пера

	plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("z");
    plot->yAxis->setRangeReversed(true);
	
	ColorMap = new QCPColorMap(plot->xAxis, plot->yAxis);

	int N = 1; 
    int nx = 4*N;                                                                     	// устанавливаем кол-во точек на диапазон значений графика Х
    int ny = 3*N;                                                                      	// устанавливаем кол-во точек на диапазон значений графика Y

    ColorMap->data()->setSize(nx, ny);                                                	// устанавливаем размер цветовая карты nx * ny точек данных
    ColorMap->data()->setRange(QCPRange(0, 4), QCPRange(0, 3));                     	// и охватывать диапазон координат 0..4 как по ключевым (x), так и по значению (y) измерениям

    ColorMap->data()->fill(0.0);
	
	// установка и настройка цветовой шкалы
    ColorScale = new QCPColorScale(plot);
    // plot->plotLayout()->addElement(0, 1, ColorScale);                                                           // добавляю цветовую шкалу справа от прямоугольника главной оси
    // ColorScale->setType(QCPAxis::atRight);                                                                      // шкала должна быть вертикальной полосой с метками осей справа (на самом деле atRight уже по умолчанию)
    ColorMap->setColorScale(ColorScale);                                                                        // связываю цветовую шкалу с 2D картой
    ColorScale->axis()->setLabel("Magnetic Field Strength");
    ColorScale->setDataRange(QCPRange(0, 1));
    // colorScale->setDataScaleType(QCPAxis :: stLogarithmic);  
	
	
	
	
	
	// установика для 2D карты цветового градиента
    QCPColorGradient *grad = new QCPColorGradient(QCPColorGradient::gpIon);           	// объект для управления градиентом цветов карты
    grad->setLevelCount(10);                                                          	// устанавливаю количество уровней цветов для отображения карты цветов
    ColorMap->setGradient(*grad);                                                     	// устанавливаю объект класса QCPColorGradient *grad
    ColorMap->setInterpolate(false);                                                 	// выключаю интерполяцию отображаемых цветовых данных
	
	// измените масштаб осей ключа (x) и значения (y), чтобы была видна вся цветовая карта:
    plot->rescaleAxes();
	
	
	
	ColorMap->data()->setCell(1, 1, 1); 
	plot->replot();
	
	
	
	
}





/*!
 * @brief:	Функция создаёт и компонует меню
*/
void MainWindow::
createMenus(void){
	
	MenuBar = new QMenuBar(this); 
	this->setMenuBar(MenuBar); 	
	
	// MenuBar->addMenu(tr("&File"));
	
	// this->menuBar()->addMenu(tr("&File"));
	// this->menuBar()->addMenu(tr("&Help"));
	
	FileMenu = this->menuBar()->addMenu(tr("&File"));
	
}
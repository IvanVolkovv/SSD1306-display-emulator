
#include "DisplayOLEDEmulator.h"

/* ColumnPixels class ------------------------------------------------------------------------------------------------------------------------- */ 

/*!
 * @brief:	Конструктор класса
*/
ColumnPixels::
ColumnPixels(QWidget *parent) : QWidget(parent){
	/* Тут может быть твой код */ 
}

/*!
 * @brief:	Конструктор класса для установки размера пикселя
*/
ColumnPixels::
ColumnPixels(QWidget *parent, double pixel_size) : QWidget(parent){
	this->pixel_size = pixel_size; 
}

/*!
 * @brief:	Переопределяю виртуальный метод для рисования виджета. 
 * @note: 	Виджет имеет вид столбца из восьми пикселей. 
*/
void ColumnPixels::
paintEvent(QPaintEvent*){
	
	QPainter painter(this);
	
	for(int i = 0; i < 8; ++i){
		
		if( (byte >> i) & 0x01 )
			painter.setBrush(Qt::white);
		else
			painter.setBrush(Qt::black);	
		
		Rect[i].setLeft(0.0); 
		Rect[i].setTop(pixel_size*i); 
		Rect[i].setHeight(pixel_size); 
		Rect[i].setHeight(pixel_size); 	
		Rect[i].setWidth(pixel_size); 
		painter.drawRoundedRect(Rect[i], 2.0, 2.0);
	}
	
	// qDebug() << " ColumnPixels::paintEvent ";
		
}

/*!
 * @brief:	Метод класса для отображения байта в виджете. 
 * @param: 	byte - байт, каждый бит которого отображается на соответствующий "пиксель" виджета. 
*/
void ColumnPixels::
setByte(short int byte){
		
	this->byte = byte; 
	this->update(); 
	
}

/* DisplayEmulator class ------------------------------------------------------------------------------------------------------------------------- */ 

DisplayEmulator::
DisplayEmulator(QWidget *parent) : QWidget(parent){

	this->setFixedSize(1286, 326); 	// setFixedSize(int w, int h) 
	
	QGridLayout *layout = new QGridLayout(this);
	layout->setSpacing(0); 	
	QMargins marg(3, 3, 3, 3); 					// QMargins(int left, int top, int right, int bottom)
	layout->setContentsMargins(marg); 
	 
	for(int i = 0; i < 512; ++i)
		ColumnP.push_back( new ColumnPixels(this) ); 
	
	for(int i = 0; i < 4; ++i){
		
		for(int j = i * 128, k = 0; j < (i+1) * 128, k < 128; ++j, ++k)
			layout->addWidget(ColumnP[j], i, k);
		
	}
	
}

DisplayEmulator::
DisplayEmulator(QWidget *parent, int num_pages, int size_pixel) : QWidget(parent){

	this->number_pages = num_pages; 

	int width_widget_base = 128 * size_pixel; 
	int height_widget_base = number_pages * 8 * size_pixel; 
	this->setFixedSize(width_widget_base + 6, height_widget_base + 6); 
	
	QGridLayout *layout = new QGridLayout(this);
	layout->setSpacing(0); 	
	QMargins marg(3, 3, 3, 3); 					// QMargins(int left, int top, int right, int bottom)
	layout->setContentsMargins(marg); 
	 
	int number_segments = number_pages * 128; 
	 
	for(int i = 0; i < number_segments; ++i)
		ColumnP.push_back( new ColumnPixels(this, size_pixel) ); 
	
	for(int i = 0; i < number_pages; ++i){
		
		for(int j = i * 128, k = 0; j < (i+1) * 128, k < 128; ++j, ++k)
			layout->addWidget(ColumnP[j], i, k);
		
	}
	
}

void DisplayEmulator::
paintEvent(QPaintEvent*){

	QPainter painter(this);
	
	QPen pen;
	pen.setColor(Qt::red);
	pen.setWidth(3);
	painter.setPen(pen);
	painter.setBrush(Qt::blue);
	
	QRectF rectangle_1(0.0, 0.0, width(), height());
	painter.drawRoundedRect(rectangle_1, 1.0, 1.0);
	
}

void DisplayEmulator::
setData(short int data, int number){
	
	ColumnP[number]->setByte(data); 
	
}










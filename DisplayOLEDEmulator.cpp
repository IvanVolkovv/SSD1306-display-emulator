
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
		Rect[i].setTop(0.0 + 10.0*i); 
		Rect[i].setHeight(10.0); 
		Rect[i].setHeight(10.0); 	
		Rect[i].setWidth(10.0); 
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

	// this->setFixedSize(1280, 166); 	// setFixedSize(int w, int h) 
	
	// QVBoxLayout *layout = new QVBoxLayout(this);
	// layout->setSpacing(0); 
	// QMargins marg(3, 3, 0, 3); 					// QMargins(int left, int top, int right, int bottom)
	// layout->setContentsMargins(marg); 
	
	// ColumnPixels *rows_segment = new ColumnPixels(this); 
	// ColumnPixels *rows_segment_2 = new ColumnPixels(this); 
	// layout->addWidget(rows_segment);
	// layout->addWidget(rows_segment_2);	
	
	this->setFixedSize(1286, 326); 	// setFixedSize(int w, int h) 
	
	QGridLayout *layout = new QGridLayout(this);
	layout->setSpacing(0); 	
	QMargins marg(3, 3, 3, 3); 					// QMargins(int left, int top, int right, int bottom)
	layout->setContentsMargins(marg); 
	 
	/* 
	ColumnPixels *rows_segment = new ColumnPixels(this); 
	ColumnPixels *rows_segment_2 = new ColumnPixels(this); 
	layout->addWidget(rows_segment, 0, 0);
	layout->addWidget(rows_segment_2, 0, 1);	
	 */
	
	// ColumnPixels *ColumnP[8] = {	new ColumnPixels(this), new ColumnPixels(this), new ColumnPixels(this), new ColumnPixels(this), new ColumnPixels(this) };  
	
	
	// QVector <ColumnPixels*> ColumnP;
	
	for(int i = 0; i < 512; ++i)
		ColumnP.push_back( new ColumnPixels(this) ); 
	
	
	// layout->addWidget(ColumnP[0], 0, 0);
	
	for(int i = 0; i < 4; ++i){
		
		for(int j = i * 128, k = 0; j < (i+1) * 128, k < 128; ++j, ++k)
			layout->addWidget(ColumnP[j], i, k);
		
	}
	
	
	
	// ColumnP[5]->setByte(1); 
	
	
	  
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










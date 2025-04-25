#ifndef DISPLAY_SEGMENT_H
#define DISPLAY_SEGMENT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QVector>
#include <QPainter>
#include <QDebug>


class ColumnPixels : public QWidget {
	
    Q_OBJECT
	/* --------- */
	
	short int byte = 0; 
	
	QRectF Rect[8]; 
	
	double pixel_size = 5.0; 
	

public:
    explicit ColumnPixels(QWidget *parent = nullptr);
	explicit ColumnPixels(QWidget*, double);
	
	void setByte(short int); 
	
protected: 
	virtual void paintEvent(QPaintEvent *);
	

signals:
	/*  */ 

};


class DisplayEmulator : public QWidget {
	
    Q_OBJECT
	/* --------- */

	QVector <ColumnPixels*> ColumnP;
	
	// кол-во страниц дисплея
	int number_pages = 4; 
	
	
	
	
	/* 
		высота виджета должна быть привязана к кол-ву страниц: 
		4 страницы для 128 х 32
		8 страниц для 128 х 64
		ширина у всех одинаковая - 128 пикселей 
	*/ 
	
	
	
	
	

public:
    explicit DisplayEmulator(QWidget *parent = nullptr);
	explicit DisplayEmulator(QWidget*, int, int);
	
	void setData(short int, int); 
	
	
protected: 
	virtual void paintEvent(QPaintEvent *);

signals:
	/*  */ 
};












#endif // DISPLAY_SEGMENT_H

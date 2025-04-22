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
	

public:
    explicit ColumnPixels(QWidget *parent = nullptr);
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

public:
    explicit DisplayEmulator(QWidget *parent = nullptr);
	void setData(short int, int); 
	
	
protected: 
	virtual void paintEvent(QPaintEvent *);

signals:
	/*  */ 
};












#endif // DISPLAY_SEGMENT_H

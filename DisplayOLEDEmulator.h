#ifndef DISPLAY_SEGMENT_H
#define DISPLAY_SEGMENT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QVector>
#include <QPainter>
#include <QDebug>

#define DISPLAY_COLUMNS		128U
#define SEGMENT_SIZE		8U

class ColumnPixels : public QWidget {
	
    Q_OBJECT
	
	short int byte = 0; 
	double pixel_size = 5.0; 
	QRectF Rect[SEGMENT_SIZE]; 
	
public:
    explicit ColumnPixels(QWidget *parent = nullptr);
	explicit ColumnPixels(QWidget*, double);
	void setByte(short int); 
	
protected: 
	virtual void paintEvent(QPaintEvent*);
	
signals:
	/* --- */ 
};

class DisplayEmulator : public QWidget {
	
    Q_OBJECT

	QVector <ColumnPixels*> ColumnP;
	int number_pages = 4; 										// кол-во страниц дисплея
	
public:
    explicit DisplayEmulator(QWidget *parent = nullptr);
	explicit DisplayEmulator(QWidget*, int, int);
	void setData(short int, int); 
	
protected: 
	virtual void paintEvent(QPaintEvent*);

signals:
	/* --- */ 
};


#endif // DISPLAY_SEGMENT_H

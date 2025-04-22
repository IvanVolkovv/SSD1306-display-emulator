
#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[]){

    QApplication app(argc, argv);               
	MainWindow GeneralWindow;
    GeneralWindow.show();
    return app.exec();                        

}

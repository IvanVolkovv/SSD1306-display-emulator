
QT += widgets printsupport

CONFIG += c++17 
# CONFIG += c++17 console

SOURCES += \
        main.cpp \
        mainwindow.cpp \
		DisplayOLEDEmulator.cpp 

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    mainwindow.h \
	DisplayOLEDEmulator.h 

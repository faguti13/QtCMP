QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    circularlist.cpp \
    doublylinkedlist.cpp \
    jsonhandler.cpp \
    main.cpp \
    mainwindow.cpp \
    pagedarray.cpp \
    principallist.cpp \
    serverconnection.cpp

HEADERS += \
    Node.h \
    circularlist.h \
    doublylinkedlist.h \
    jsonhandler.h \
    mainwindow.h \
    pagedarray.h \
    principallist.h \
    serverconnection.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Configuración de inclusión y enlace de TagLib
INCLUDEPATH += /usr/include/taglib
LIBS += /usr/lib/x86_64-linux-gnu/libtag.so


QT       += core gui webenginewidgets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LottieViewer
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    jsbridge.cpp

HEADERS += \
        mainwindow.h \
    jsbridge.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    app.js \
    bodymovin.js

RESOURCES += \
    appresources.qrc

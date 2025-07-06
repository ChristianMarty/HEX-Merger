QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QuCLib/source/hexFileParser.cpp \
    logic/fileItem.cpp \
    logic/fileMerger.cpp \
    logic/settings.cpp \
    logic/xmlReader.cpp \
    ui/fileItemWidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    QuCLib/source/hexFileParser.h \
    logic/fileItem.h \
    logic/fileMerger.h \
    logic/settings.h \
    logic/xmlReader.h \
    main.h \
    ui/fileItemWidget.h \
    mainwindow.h

FORMS += \
    ui/fileItemWidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
